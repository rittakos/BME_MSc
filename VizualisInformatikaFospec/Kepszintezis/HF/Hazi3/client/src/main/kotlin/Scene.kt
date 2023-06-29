import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.SamplerCube
import vision.gears.webglmath.Sampler3D
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext) : UniformProvider("scene"){

  val vsQuad = Shader(gl, GL.VERTEX_SHADER, "quad-vs.glsl")
  val fsTrace = Shader(gl, GL.FRAGMENT_SHADER, "trace-fs.glsl")  
  val traceProgram = Program(gl, vsQuad, fsTrace, Program.PNT)
  val quadGeometry = TexturedQuadGeometry(gl)  

  val timeAtFirstFrame  = Date().getTime()
  var timeAtLastFrame   = timeAtFirstFrame
  var lastModeChange    = timeAtFirstFrame;

  val camera = PerspectiveCamera(*Program.all)

  val lights = ArrayList<Light>()

  val env by SamplerCube()

  val volumeTexture = Texture3D(gl, "media/brain-at_4096.jpg")
  val volume = Sampler3D()

  var mode = Vec3();


  init {
    env.set(TextureCube(gl, "media/posx512.jpg", "media/negx512.jpg"
      , "media/posy512.jpg", "media/negy512.jpg", "media/posz512.jpg", "media/negz512.jpg"))
    addComponentsAndGatherUniforms(*Program.all)
    lights.add(Light(0))
    lights[0].position.set(1f, 1f, 1f, 0f).normalize()
    lights[0].powerDensity.set(10.951f, 10.951f, 10.951f, 1f)    
    lights.add(Light(1))    
    lights[1].position.set(2.5f, -2.0f, 0f, 1f)
    lights[1].powerDensity.set(13f, 13f, 13f, 1f)
    register("volume", volume)
    volume.glTextures[0] = volumeTexture.glTexture
    mode.x = 0.0f
    register("mode", mode)
    addComponentsAndGatherUniforms(*Program.all)

  }

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {

    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t  = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    val dtMode = (timeAtThisFrame - lastModeChange).toFloat() / 1000.0f
    timeAtLastFrame = timeAtThisFrame
    
    camera.move(dt, keysPressed)

    if("N" in keysPressed && dtMode > 0.1f)
    {
      ++mode.x;
      mode.x = mode.x % 3
      lastModeChange = timeAtThisFrame
    }

    // clear the screen
    gl.clearColor(0.0f, 0.0f, 0.3f, 1.0f)
    gl.clearDepth(1.0f)
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)
    
    traceProgram.draw(this, *lights.toTypedArray(), camera)
    quadGeometry.draw()    
  }
}
