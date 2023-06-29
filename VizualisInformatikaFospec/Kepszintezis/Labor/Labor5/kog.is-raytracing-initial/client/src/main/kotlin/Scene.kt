import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext) : UniformProvider("scene") {

  val vsQuad = Shader(gl, GL.VERTEX_SHADER, "quad-vs.glsl")
  val fstrace = Shader(gl, GL.FRAGMENT_SHADER, "trace-fs.glsl")
  val traceProgram = Program(gl, vsQuad, fstrace)
  val skyCubeTexture = TextureCube(gl,
      "media/posx512.jpg", "media/negx512.jpg",
      "media/posy512.jpg", "media/negy512.jpg",
      "media/posz512.jpg", "media/negz512.jpg"
    )
  val traceMaterial = Material(traceProgram).apply{
    this["envTexture"]?.set( skyCubeTexture )
  }
  val quadGeometry = TexturedQuadGeometry(gl)
  val traceMesh = Mesh(traceMaterial, quadGeometry)

  val camera = PerspectiveCamera()

  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  init{
    gl.enable(GL.DEPTH_TEST)
    addComponentsAndGatherUniforms(*Program.all)
  }

  val quadrics = Array<Quadric>(2) { Quadric(it) }
  init{
    quadrics[0].surface.set(Quadric.unitSphere)
    quadrics[0].surface.transform(Mat4 ().scale(10.0f, 10.0f, 10.0f).translate(0.3f, 0.1f, 0.6f))
    quadrics[0].clipper.set(Quadric.unitSlab)
    quadrics[0].clipper.transform(Mat4 ().scale(30.0f, 30.0f, 30.0f))

    quadrics[1].surface.set(Quadric.unitSphere)
    quadrics[1].surface.transform(Mat4 ().scale(10.0f, 10.0f, 10.0f).translate(20f, 20f, 20f))
    quadrics[1].clipper.set(Quadric.unitSlab)
    quadrics[1].clipper.transform(Mat4 ().scale(30.0f, 30.0f, 30.0f))
  }

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {

    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t  = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    timeAtLastFrame = timeAtThisFrame

    camera.move(dt, keysPressed)

    // clear the screen
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)
    gl.clearDepth(1.0f)
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)

    //traceMesh.draw(camera)
    traceMesh.draw(camera, *quadrics)
  }
}
