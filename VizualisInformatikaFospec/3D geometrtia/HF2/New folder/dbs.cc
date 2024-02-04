#include "dbs.hh"
#include "geometry.hh"

#include <fstream>


double DBS::fullness = 0.5;

DBS::DBS(std::string filename) : Object(filename)
{
  reload();
}

void DBS::draw(const Visualization &vis) const {
  if(vis.fullness != DBS::fullness)
  {
      DBS::fullness = vis.fullness;
      const_cast<DBS*>(this)->updateBaseMesh();
  }

  Object::draw(vis);
  if (vis.show_control_points) {
      glDisable(GL_LIGHTING);
      glLineWidth(3.0);
      glColor3d(0.3, 0.3, 1.0);

      for(size_t i = 0; i < num[0] - 1; ++i) // u
      {
          for(size_t j = 0; j < num[1] - 1; ++j) // v
          {
              glBegin(GL_LINE_LOOP);
              const auto &p1 = control_points_matrix[i][j];
              glVertex3dv(p1.data());
              const auto &p2 = control_points_matrix[i + 1][j];
              glVertex3dv(p2.data());
              const auto &p3 = control_points_matrix[i + 1][j + 1];
              glVertex3dv(p3.data());
              const auto &p4 = control_points_matrix[i][j + 1];
              glVertex3dv(p4.data());
              glEnd();
          }
      }

      glLineWidth(1.0);
      glPointSize(8.0);
      glColor3d(1.0, 0.0, 1.0);
      glBegin(GL_POINTS);

      for(size_t idx = 0; idx < control_points.size(); ++idx)
      {
          if(innerPoint.at(idx))
              continue;

          const auto &p = control_points[idx];
          glVertex3dv(p.data());
      }
      glEnd();
      glPointSize(1.0);
      glEnable(GL_LIGHTING);
  }
}

void DBS::drawWithNames(const Visualization &vis) const {
  if (!vis.show_control_points)
      return;
  for (size_t i = 0; i < control_points.size(); ++i) {
      const auto &p = control_points[i];
      glPushName(i);
      glRasterPos3dv(p.data());
      glPopName();
  }
}

Vector DBS::postSelection(int selected) {
  return control_points[selected];
}

void DBS::movement(int selected, const Vector &pos) {
  if(innerPoint[selected])
      return;

  size_t i = selected % num[0];
  size_t j = selected / num[0];
  control_points_matrix[i][j] = pos;
  updateBaseMesh();
}


void DBS::updateBaseMesh() {
  size_t resolution = 50;

  calcControlPoints();

  mesh.clear();
  std::vector<BaseMesh::VertexHandle> handles, tri;
  size_t d_0 = degree[0], d_1 = degree[1];

  Geometry::BSSurface bSSurface (d_0, d_1, knots_u, knots_v, DBS::toPoint3DVec(control_points));

  minU = control_points[0][0];
  minV = control_points[0][1];

  std::vector<double> coeff_u, coeff_v;
  for (size_t i = 0; i < resolution; ++i)
  {
      double u = (double)i / (double)(resolution - 1);
      for (size_t j = 0; j < resolution; ++j) {
          double v = (double)j / (double)(resolution - 1);
          Vector p = DBS::toVec3D(bSSurface.eval(u, v));

          if(p[0] > maxU)
              maxU = p[0];

          if(p[1] > maxV)
              maxV = p[1];

          if(p[0] < minU)
              minU = p[0];

          if(p[1] < minV)
              minV = p[1];

          handles.push_back(mesh.add_vertex(p));
      }
  }
  for (size_t i = 0; i < resolution - 1; ++i)
  {
      for (size_t j = 0; j < resolution - 1; ++j) {
          tri.clear();
          tri.push_back(handles[i * resolution + j]);
          tri.push_back(handles[i * resolution + j + 1]);
          tri.push_back(handles[(i + 1) * resolution + j]);
          mesh.add_face(tri);
          tri.clear();
          tri.push_back(handles[(i + 1) * resolution + j]);
          tri.push_back(handles[i * resolution + j + 1]);
          tri.push_back(handles[(i + 1) * resolution + j + 1]);
          mesh.add_face(tri);
        }
  }

  Object::updateBaseMesh(false, false);
}

bool DBS::reload() {
  size_t nu, nv;
  size_t du, dv;
  try {
      std::ifstream f(filename);
      f.exceptions(std::ios::failbit | std::ios::badbit);
      f >> du >> dv;
      f >> nu >> nv;
      degree[0] = du; degree[1] = dv;
      num[0] = nu; num[1] = nv;

      knots_u.resize(nu + du + 1);
      for(size_t idx = 0; idx <= du + nu; ++idx)
          f >> knots_u[idx];

      knots_v.resize(nv + dv + 1);
      for(size_t idx = 0; idx <= dv + nv; ++idx)
          f >> knots_v[idx];

      //control_points.resize(n * m);
      control_points_matrix.resize(nu);
      for (size_t i = 0; i < nu; ++i)
      {
          control_points_matrix[i].resize(nv);
      }

      for (size_t u = 0; u < nu; ++u)
        f >> control_points_matrix[u][0][0] >> control_points_matrix[u][0][1] >> control_points_matrix[u][0][2];

      for (size_t v = 1; v < nv; ++v)
        f >> control_points_matrix[nu - 1][v][0] >> control_points_matrix[nu - 1][v][1] >> control_points_matrix[nu - 1][v][2];

      for (int u = nu - 2; u >= 0; --u)
        f >> control_points_matrix[u][nv - 1][0] >> control_points_matrix[u][nv - 1][1] >> control_points_matrix[u][nv - 1][2];

      for (size_t v = nv - 2; v >= 1; --v)
        f >> control_points_matrix[0][v][0] >> control_points_matrix[0][v][1] >> control_points_matrix[0][v][2];

  } catch(std::ifstream::failure &) {
      return false;
  }
  updateBaseMesh();
  return true;
}

Vector DBS::normal(BaseMesh::VertexHandle vh) const
{
  size_t d_0 = degree[0], d_1 = degree[1];

  Geometry::BSSurface bSSurface (d_0, d_1, knots_u, knots_v, DBS::toPoint3DVec(control_points));

  double u = (mesh.point(vh)[0] - minU) / (maxU - minU);
  double v = (mesh.point(vh)[1] - minV) / (maxV - minV);

  size_t dn = 9;
  Geometry::VectorMatrix der;
  bSSurface.eval(u, v, dn, der);

  Vector n = toVec3D(der[0][1]) % toVec3D(der[1][0]);

  return n / n.length();
}

double DBS::meanCurvature(BaseMesh::VertexHandle vh) const
{
  //return Object::meanCurvature(vh);
  size_t d_0 = degree[0], d_1 = degree[1];

  Geometry::BSSurface bSSurface (d_0, d_1, knots_u, knots_v, DBS::toPoint3DVec(control_points));

  float u = (mesh.point(vh)[0] - minU) / (maxU - minU);
  float v = (mesh.point(vh)[1] - minV) / (maxV - minV);

  size_t dn = 9;
  Geometry::VectorMatrix der;
  bSSurface.eval(u, v, dn, der);

  float E = dot(toVec3D(der[1][0]), toVec3D(der[1][0]));
  float F = dot(toVec3D(der[1][0]), toVec3D(der[0][1]));
  float G = dot(toVec3D(der[0][1]), toVec3D(der[0][1]));

  Vector n = this->normal(vh);

  float L = dot(toVec3D(der[2][0]), n);
  float M = dot(toVec3D(der[1][1]), n);
  float N = dot(toVec3D(der[0][2]), n);

  return (N * E - 2.0 * M * F + L * G) / (2.0 * (E * G - F * F));
}

DBS::~DBS()
{
  knots_u.resize(0);
  knots_v.resize(0);
}

void DBS::calcControlPoints()
{
  // step 1.
  for(size_t i = 1; i < num[0] - 1; ++i) // u
  {
      for(size_t j = 1; j < num[1] - 1; ++j) // v
      {
        double gamma_i_u = 0.0;
        double gamma_j_v = 0.0;

        for(int k = 1; k <= degree[0]; ++k)
        {
              gamma_i_u += knots_u[i + k];
        }

        for(int k = 1; k <= degree[1]; ++k)
        {
              gamma_j_v += knots_v[j + k];
        }


        gamma_i_u /= degree[0];
        gamma_j_v /= degree[1];

        Vector p = 0.5 * ((
                       (1.0 - gamma_i_u) * control_points_matrix[0][j]) +
                       ((gamma_i_u) * control_points_matrix[num[0] - 1][j]) +
                       ((1.0 - gamma_j_v) * control_points_matrix[i][0]) +
                       ((gamma_j_v) * control_points_matrix[i][num[1] - 1]));


        control_points_matrix[i][j] = p;
      }
  }

  //step 2.

  const size_t maxIter = 100;
  size_t iter = 0;

  const double minDelta = 0.0001;
  bool done = false;

  while(!done && iter < maxIter)
  {
      for(size_t i = 1; i < num[0] - 1; ++i) // u
      {
        for(size_t j = 1; j < num[1] - 1; ++j) // v
        {
              double gamma_i_u = 0.0;
              double gamma_j_v = 0.0;
              double gamma_im1_u = 0.0;
              double gamma_jm1_v = 0.0;
              double gamma_ip1_u = 0.0;
              double gamma_jp1_v = 0.0;

              for(int k = 1; k <= degree[0]; ++k)
              {
                  gamma_i_u += knots_u[i + k];
              }

              for(int k = 1; k <= degree[1]; ++k)
              {
                  gamma_j_v += knots_v[j + k];
              }

              for(int k = 1; k <= degree[0]; ++k)
              {
                  gamma_im1_u += knots_u[i - 1 + k];
              }

              for(int k = 1; k <= degree[1]; ++k)
              {
                  gamma_jm1_v += knots_v[j - 1 + k];
              }

              for(int k = 1; k <= degree[0]; ++k)
              {
                  gamma_ip1_u += knots_u[i + 1 + k];
              }

              for(int k = 1; k <= degree[1]; ++k)
              {
                  gamma_jp1_v += knots_v[j + 1 + k];
              }


            double delta_minus_u    = (gamma_i_u - gamma_im1_u) / (gamma_ip1_u - gamma_im1_u);
            double delta_plus_u     = (gamma_ip1_u - gamma_i_u) / (gamma_ip1_u - gamma_im1_u);
            double delta_minus_v    = (gamma_j_v - gamma_jm1_v) / (gamma_jp1_v - gamma_jm1_v);
            double delta_plus_v     = (gamma_jp1_v - gamma_j_v) / (gamma_jp1_v - gamma_jm1_v);


            Vector P_1 =    delta_plus_u * control_points_matrix[i - 1][j] +
                            delta_minus_u * control_points_matrix[i + 1][j] +
                            delta_plus_v * control_points_matrix[i][j - 1] +
                            delta_minus_v * control_points_matrix[i][j + 1];

            Vector P_2 =    delta_plus_u * delta_plus_v * control_points_matrix[i - 1][j - 1] +
                            delta_plus_u * delta_minus_v * control_points_matrix[i - 1][j + 1] +
                            delta_minus_u * delta_plus_v * control_points_matrix[i + 1][j - 1] +
                            delta_minus_u * delta_minus_v * control_points_matrix[i + 1][j + 1];


            Vector P = fullness * P_1 + (1.0 - 2.0 * fullness) * P_2;

            control_points_matrix[i][j] = P;

            if(delta_minus_u < minDelta && delta_plus_u < minDelta && delta_plus_v < minDelta && delta_minus_v < minDelta)
                  done = true;
            else
                  done = false;

        }
      }
      ++iter;
  }


  control_points.clear();
  innerPoint.clear();
  int idx = 0;

  for(size_t i = 0; i < num[0]; ++i)
  {
      for(size_t j = 0; j < num[1]; ++j)
      {
        control_points.push_back(control_points_matrix[i][j]);
        if(i != 0 && i != num[0] - 1 && j != 0 && j != num[1] - 1)
              innerPoint[idx] = true;
        else
              innerPoint[idx] = false;
        ++idx;
      }
  }
}

std::vector<Geometry::Point3D> DBS::toPoint3DVec(const std::vector<Vector> &in)
{
  std::vector<Geometry::Point3D> result;
  for(const Vector& v : in)
      result.push_back(DBS::toPoint3D(v));
  return result;
}

std::vector<Vector> DBS::toVec3DVec (const std::vector<Geometry::Point3D>& in)
{
  std::vector<Vector> result;
  for(const Geometry::Point3D& p : in)
      result.push_back(DBS::toVec3D(p));
  return result;
}

Geometry::Point3D DBS::toPoint3D (const Vector& in)
{
  Geometry::Point3D result(in[0], in[1], in[2]);
  return result;
}

Vector DBS::toVec3D (const Geometry::Point3D& in)
{
  Vector result(in[0], in[1], in[2]);
  return result;
}
