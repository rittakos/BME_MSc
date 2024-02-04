#include <QtGui/QKeyEvent>

#include "bezier.hh"
#include "mesh.hh"
#include "dbs.hh"
#include "viewer.hh"
#include "dbs.hh"

Viewer::Viewer(QWidget *parent) : QGLViewer(parent) {
  setSelectRegionWidth(10);
  setSelectRegionHeight(10);
  axes.shown = false;
}

Viewer::~Viewer() {
  glDeleteTextures(1, &vis.isophote_texture);
  glDeleteTextures(1, &vis.environment_texture);
  glDeleteTextures(1, &vis.slicing_texture);
}

double Viewer::getCutoffRatio() const {
  return vis.cutoff_ratio;
}

void Viewer::setCutoffRatio(double ratio) {
  vis.cutoff_ratio = ratio;
  updateMeanMinMax();
}

double Viewer::getMeanMin() const {
  return vis.mean_min;
}

void Viewer::setMeanMin(double min) {
  vis.mean_min = min;
}

double Viewer::getMeanMax() const {
  return vis.mean_max;
}

void Viewer::setMeanMax(double max) {
  vis.mean_max = max;
}

const double *Viewer::getSlicingDir() const {
  return vis.slicing_dir.data();
}

void Viewer::setSlicingDir(double x, double y, double z) {
  vis.slicing_dir = Vector(x, y, z).normalized();
}

double Viewer::getSlicingScaling() const {
  return vis.slicing_scaling;
}

void Viewer::setSlicingScaling(double scaling) {
  vis.slicing_scaling = scaling;
}

double Viewer::getFullness() const
{
  return vis.fullness;
}

void Viewer::setFullness(double fullness)
{
  vis.fullness = fullness;
  //DBS::fullness = fullness;
  update();
}

void Viewer::deleteObjects() {
  objects.clear();
}

bool Viewer::open(std::string filename) {
  std::shared_ptr<Object> surface;
  if (filename.ends_with(".bzr"))
    surface = std::make_shared<Bezier>(filename);
  else if (filename.ends_with(".dbs"))
      surface = std::make_shared<DBS>(filename);
  else
    surface = std::make_shared<Mesh>(filename);
  if (!surface->valid())
    return false;
  objects.push_back(surface);
  updateMeanMinMax();
  setupCamera();
  return true;
}

void Viewer::init() {
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

  QImage img(":/isophotes.png");
  glGenTextures(1, &vis.isophote_texture);
  glBindTexture(GL_TEXTURE_2D, vis.isophote_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.width(), img.height(), 0, GL_BGRA,
               GL_UNSIGNED_BYTE, img.convertToFormat(QImage::Format_ARGB32).bits());

  QImage img2(":/environment.png");
  glGenTextures(1, &vis.environment_texture);
  glBindTexture(GL_TEXTURE_2D, vis.environment_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img2.width(), img2.height(), 0, GL_BGRA,
               GL_UNSIGNED_BYTE, img2.convertToFormat(QImage::Format_ARGB32).bits());

  glGenTextures(1, &vis.slicing_texture);
  glBindTexture(GL_TEXTURE_1D, vis.slicing_texture);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  static const unsigned char slicing_img[] = { 0b11111111, 0b00011100 };
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 2, 0, GL_RGB, GL_UNSIGNED_BYTE_3_3_2, &slicing_img);
}

void Viewer::draw() {
  for (auto o : objects)
    o->draw(vis);

  if (axes.shown) {
    using qglviewer::Vec;
    const auto &p = Vec(axes.position);
    glColor3d(1.0, 0.0, 0.0);
    drawArrow(p, p + Vec(axes.size, 0.0, 0.0), axes.size / 50.0);
    glColor3d(0.0, 1.0, 0.0);
    drawArrow(p, p + Vec(0.0, axes.size, 0.0), axes.size / 50.0);
    glColor3d(0.0, 0.0, 1.0);
    drawArrow(p, p + Vec(0.0, 0.0, axes.size), axes.size / 50.0);
  }
}

void Viewer::drawWithNames() {
  if (axes.shown) {
    using qglviewer::Vec;
    const auto &p = Vec(axes.position);
    glPushName(0);
    drawArrow(p, p + Vec(axes.size, 0.0, 0.0), axes.size / 50.0);
    glPopName();
    glPushName(1);
    drawArrow(p, p + Vec(0.0, axes.size, 0.0), axes.size / 50.0);
    glPopName();
    glPushName(2);
    drawArrow(p, p + Vec(0.0, 0.0, axes.size), axes.size / 50.0);
    glPopName();
  } else {
    for (size_t i = 0; i < objects.size(); ++i) {
      glPushName(i);
      objects[i]->drawWithNames(vis);
      glPopName();
    }
  }
}

// Same as the default implementation,
// but when there are 2 names for a hit,
// the first is treated as the selected object id.
void Viewer::endSelection(const QPoint &) {
  glFlush();
  GLint nbHits = glRenderMode(GL_RENDER);
  if (nbHits <= 0)
    setSelectedName(-1);
  else {
    const GLuint *ptr = selectBuffer();
    GLuint zMin = std::numeric_limits<GLuint>::max();
    for (int i = 0; i < nbHits; ++i, ptr += 4) {
      GLuint names = ptr[0];
      if (ptr[1] < zMin) {
        zMin = ptr[1];
        if (names == 2) {
          selected_object = ptr[3];
          ptr++;
        }
        setSelectedName(ptr[3]);
      } else if (names == 2)
        ptr++;
    }
  }
}

static inline Vector toVector(const qglviewer::Vec &v) {
  return Vector(static_cast<const qreal *>(v));
}

void Viewer::postSelection(const QPoint &p) {
  int sel = selectedName();
  if (sel == -1) {
    axes.shown = false;
    return;
  }

  if (axes.shown) {
    axes.selected_axis = sel;
    bool found;
    axes.grabbed_pos = toVector(camera()->pointUnderPixel(p, found));
    axes.original_pos = axes.position;
    if (!found)
      axes.shown = false;
    return;
  }

  using qglviewer::Vec;
  selected_vertex = sel;
  axes.position = objects[selected_object]->postSelection(sel);
  double depth = camera()->projectedCoordinatesOf(Vec(axes.position))[2];
  Vec q1 = camera()->unprojectedCoordinatesOf(Vec(0.0, 0.0, depth));
  Vec q2 = camera()->unprojectedCoordinatesOf(Vec(width(), height(), depth));
  axes.size = (q1 - q2).norm() / 10.0;
  axes.shown = true;
  axes.selected_axis = -1;
}

void Viewer::keyPressEvent(QKeyEvent *e) {
  if (e->modifiers() == Qt::NoModifier)
    switch (e->key()) {
    case Qt::Key_R:
      for (auto o : objects)
        o->reload();
      update();
      break;
    case Qt::Key_O:
      if (camera()->type() == qglviewer::Camera::PERSPECTIVE)
        camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
      else
        camera()->setType(qglviewer::Camera::PERSPECTIVE);
      update();
      break;
    case Qt::Key_P:
      vis.type = VisType::PLAIN;
      update();
      break;
    case Qt::Key_M:
      vis.type = VisType::MEAN;
      update();
      break;
    case Qt::Key_L:
      vis.type = VisType::SLICING;
      update();
      break;
    case Qt::Key_I:
      vis.type = VisType::ISOPHOTES;
      vis.current_isophote_texture = vis.isophote_texture;
      update();
      break;
    case Qt::Key_E:
      vis.type = VisType::ISOPHOTES;
      vis.current_isophote_texture = vis.environment_texture;
      update();
      break;
    case Qt::Key_C:
      vis.show_control_points = !vis.show_control_points;
      update();
      break;
    case Qt::Key_S:
      vis.show_solid = !vis.show_solid;
      update();
      break;
    case Qt::Key_W:
      vis.show_wireframe = !vis.show_wireframe;
      update();
      break;
    case Qt::Key_X:
      camera()->setViewDirection(qglviewer::Vec(1.0, 0.0, 0.0));
      camera()->setUpVector(qglviewer::Vec(0.0, 1.0, 0.0));
      camera()->showEntireScene();
      update();
      break;
    case Qt::Key_Y:
      camera()->setViewDirection(qglviewer::Vec(0.0, 1.0, 0.0));
      camera()->setUpVector(qglviewer::Vec(0.0, 0.0, 1.0));
      camera()->showEntireScene();
      update();
      break;
    case Qt::Key_Z:
      camera()->setViewDirection(qglviewer::Vec(0.0, 0.0, 1.0));
      camera()->setUpVector(qglviewer::Vec(1.0, 0.0, 0.0));
      camera()->showEntireScene();
      update();
      break;
    default:
      QGLViewer::keyPressEvent(e);
    }
  else if (e->modifiers() == Qt::KeypadModifier)
    switch (e->key()) {
    case Qt::Key_Plus:
      vis.slicing_scaling *= 2;
      update();
      break;
    case Qt::Key_Minus:
      vis.slicing_scaling /= 2;
      update();
      break;
    case Qt::Key_Asterisk:
      vis.slicing_dir = Vector(static_cast<double *>(camera()->viewDirection()));
      update();
      break;
    } else
    QGLViewer::keyPressEvent(e);
}

static Vector intersectLines(const Vector &ap, const Vector &ad,
                             const Vector &bp, const Vector &bd) {
  // always returns a point on the (ap, ad) line
  double a = ad.sqrnorm(), b = ad | bd, c = bd.sqrnorm();
  double d = ad | (ap - bp), e = bd | (ap - bp);
  if (a * c - b * b < 1.0e-7)
    return ap;
  double s = (b * e - c * d) / (a * c - b * b);
  return ap + s * ad;
}

void Viewer::mouseMoveEvent(QMouseEvent *e) {
  if (!axes.shown ||
      (axes.selected_axis < 0 && !(e->modifiers() & Qt::ControlModifier)) ||
      !(e->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier)) ||
      !(e->buttons() & Qt::LeftButton))
    return QGLViewer::mouseMoveEvent(e);

  using qglviewer::Vec;
  if (e->modifiers() & Qt::ControlModifier) {
    // move in screen plane
    double depth = camera()->projectedCoordinatesOf(Vec(axes.position))[2];
    auto pos = camera()->unprojectedCoordinatesOf(Vec(e->pos().x(), e->pos().y(), depth));
    axes.position = toVector(pos);
  } else {
    Vec from, dir, axis(axes.selected_axis == 0, axes.selected_axis == 1, axes.selected_axis == 2);
    camera()->convertClickToLine(e->pos(), from, dir);
    auto p = intersectLines(axes.grabbed_pos, toVector(axis), toVector(from), toVector(dir));
    float d = (p - axes.grabbed_pos) | toVector(axis);
    axes.position[axes.selected_axis] = axes.original_pos[axes.selected_axis] + d;
  }

  objects[selected_object]->movement(selected_vertex, axes.position);
  objects[selected_object]->updateBaseMesh();
  updateMeanMinMax();
  update();
}

QString Viewer::helpString() const {
  QString text("<h2>Geometry Framework</h2>"
               "<p>This is a minimal framework for 3D mesh manipulation, which can be "
               "extended and used as a base for various geometry-relatedprojects.</p>"
               "<p>The following hotkeys are available:</p>"
               "<ul>"
               "<li>&nbsp;R: Reload model</li>"
               "<li>&nbsp;O: Toggle orthographic projection</li>"
               "<li>&nbsp;P: Set plain map (no coloring)</li>"
               "<li>&nbsp;M: Set mean curvature map</li>"
               "<li>&nbsp;L: Set slicing map<ul>"
               "<li>&nbsp;+: Increase slicing density</li>"
               "<li>&nbsp;-: Decrease slicing density</li>"
               "<li>&nbsp;*: Set slicing direction to view</li></ul></li>"
               "<li>&nbsp;I: Set isophote line map</li>"
               "<li>&nbsp;E: Set environment texture</li>"
               "<li>&nbsp;C: Toggle control polygon visualization</li>"
               "<li>&nbsp;S: Toggle solid (filled polygon) visualization</li>"
               "<li>&nbsp;W: Toggle wireframe visualization</li>"
               "<li>&nbsp;X/Y/Z: Set standard view direction</li>"
               "</ul>"
               "<p>There is also a simple selection and movement interface, enabled "
               "only when the wireframe/controlnet is displayed: a mesh vertex can be selected "
               "by shift-clicking, and it can be moved by shift-dragging one of the "
               "displayed axes. Pressing ctrl enables movement in the screen plane.</p>"
               "<p>Note that libQGLViewer is furnished with a lot of useful features, "
               "such as storing/loading view positions, or saving screenshots. "
               "OpenMesh also has a nice collection of tools for mesh manipulation: "
               "decimation, subdivision, smoothing, etc. These can provide "
               "good comparisons to the methods you implement.</p>"
               "<p>This software can be used as a sample GUI base for handling "
               "parametric or procedural surfaces, as well. The power of "
               "Qt and libQGLViewer makes it easy to set up a prototype application. "
               "Feel free to modify and explore!</p>"
               "<p align=\"right\">Peter Salvi</p>");
  return text;
}

void Viewer::updateMeanMinMax() {
  std::vector<double> mean;
  for (auto o : objects) {
    const auto &mesh = o->baseMesh();
    for (auto v : mesh.vertices())
      mean.push_back(mesh.data(v).mean);
  }

  size_t n = mean.size();
  if (n < 3)
    return;

  std::sort(mean.begin(), mean.end());
  size_t k = (double)n * vis.cutoff_ratio;
  vis.mean_min = std::min(mean[k ? k-1 : 0], 0.0);
  vis.mean_max = std::max(mean[k ? n-k : n-1], 0.0);
}

void Viewer::setupCamera() {
  double large = std::numeric_limits<double>::max();
  Vector box_min(large, large, large), box_max(-large, -large, -large);
  for (auto o : objects) {
    const auto &mesh = o->baseMesh();
    for (auto v : mesh.vertices()) {
      box_min.minimize(mesh.point(v));
      box_max.maximize(mesh.point(v));
    }
  }
  using qglviewer::Vec;
  camera()->setSceneBoundingBox(Vec(box_min.data()), Vec(box_max.data()));
  camera()->showEntireScene();

  vis.slicing_scaling = 20 / (box_max - box_min).max();

  setSelectedName(-1);
  axes.shown = false;

  update();
}
