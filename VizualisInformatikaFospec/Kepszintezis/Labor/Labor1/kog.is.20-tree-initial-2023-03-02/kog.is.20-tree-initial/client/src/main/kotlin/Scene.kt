import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL //# GL# we need this for the constants declared ˙HUN˙ a constansok miatt kell
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext){
  
  val vsQuad = Shader(gl, GL.VERTEX_SHADER, "quad-vs.glsl")
  val fsBackground = Shader(gl, GL.FRAGMENT_SHADER, "background-fs.glsl")

  val vsTree = Shader(gl, GL.VERTEX_SHADER, "tree-vs.glsl")
  val fsDiffuse = Shader(gl, GL.FRAGMENT_SHADER, "diffuse-fs.glsl")   
 
  val quadGeometry = TexturedQuadGeometry(gl)

  val backgroundProgram = Program(gl, vsQuad, fsBackground)
  val treeProgram = Program(gl, vsTree, fsDiffuse, Program.PNT)

  val skyCubeTexture = TextureCube(gl,
      "media/posx512.jpg", "media/negx512.jpg",
      "media/posy512.jpg", "media/negy512.jpg",
      "media/posz512.jpg", "media/negz512.jpg"
    )

  val backgroundMaterial = Material(backgroundProgram).apply{
    this["envTexture"]?.set( skyCubeTexture )
  }

  val treeMaterial = Material(treeProgram).apply{
    this["colorTexture"]?.set(Texture2D(gl, "media/barkpaint.png"))
  }

  val jsonLoader = JsonLoader()

  val treeElementGeometries = jsonLoader.loadRiggedGeometries(gl, "media/y6.json")
  init {
    treeElementGeometries[0].nInstances = 127
  }

  val backgroundMesh = Mesh(backgroundMaterial, quadGeometry)

  val vsBillboard = Shader(gl, GL.VERTEX_SHADER, "billboard-vs.glsl")    
  val fsBillboard = Shader(gl, GL.FRAGMENT_SHADER, "billboard-fs.glsl")
  val billboardProgram = Program(gl, vsBillboard, fsBillboard)  
  val foliageMaterial = Material(billboardProgram).apply{
    this["billboardTexture"]?.set(
      Texture2D(gl, "media/leaf.png"))
  }

  val billboardsGeometry = BillboardsGeometry(gl)

  fun resize(canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)//#viewport# tell the rasterizer which part of the canvas to draw to ˙HUN˙ a raszterizáló ide rajzoljon
  }

  val gameObjects = ArrayList<GameObject>()
  init{
    gameObjects += GameObject(
      Mesh(treeMaterial, treeElementGeometries[0])
    ).apply{move = TreeMotion(this)}
    //gameObjects += GameObject( Mesh(foliageMaterial, billboardsGeometry) ).apply{
    //  position.set(0f, 10f, 0f)
    //  scale.set(10.0f, 10.0f, 10.0f)
    //}    
  }

  val lights = Array<Light>(1) { Light(it) }
  init{
    lights[0].position.set(1.0f, 1.0f, 1.0f, 0.0f).normalize()
    lights[0].powerDensity.set(1.0f, 1.0f, 1.0f)
  }

  val camera = PerspectiveCamera()

  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  init{
    camera.position.z += 20.0f
    gl.enable(GL.DEPTH_TEST)
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
    timeAtLastFrame = timeAtThisFrame

    camera.move(dt, keysPressed)
    
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)//## red, green, blue, alpha in [0, 1]
    gl.clearDepth(1.0f)//## will be useful in 3D ˙HUN˙ 3D-ben lesz hasznos
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)//#or# bitwise OR of flags
  
    val spawn = ArrayList<GameObject>()
    gameObjects.forEach{
      it.move(dt, t, keysPressed, gameObjects, spawn)
    }

    gameObjects.forEach { it.update() }
    backgroundMesh.draw(camera)
    gameObjects.forEach { it.draw( camera, *lights ) }

  }
}
