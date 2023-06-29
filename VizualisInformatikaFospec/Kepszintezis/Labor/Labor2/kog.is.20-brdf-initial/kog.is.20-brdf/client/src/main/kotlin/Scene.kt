import org.w3c.dom.HTMLCanvasElement
import org.w3c.dom.HTMLDivElement
import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import org.khronos.webgl.Uint32Array
import vision.gears.webglmath.*
import kotlin.js.Date
import kotlin.math.*
import kotlin.random.*

class Scene (
  val gl : WebGL2RenderingContext,
  val overlay : HTMLDivElement,
  val canvas : HTMLCanvasElement) : UniformProvider("scene") {

  val vsQuad = Shader(gl, GL.VERTEX_SHADER, "quad-vs.glsl")
  val fsBackground = Shader(gl, GL.FRAGMENT_SHADER, "background-fs.glsl")

  val quadGeometry = TexturedQuadGeometry(gl)

  val backgroundProgram = Program(gl, vsQuad, fsBackground)
  val backgroundMaterial = Material(backgroundProgram)
  val skyCubeTexture = TextureCube(gl,
      "media/posx512.jpg", "media/negx512.jpg",
      "media/posy512.jpg", "media/negy512.jpg",
      "media/posz512.jpg", "media/negz512.jpg"
    )
  init {
    backgroundMaterial["envTexture"]?.set( skyCubeTexture )
  }
  val backgroundMesh = Mesh(backgroundMaterial, quadGeometry)

  val jsonLoader = JsonLoader()
  val exhibitGeometries = jsonLoader.loadGeometries(gl, "media/slowpoke/Slowpoke.json")

  val vsTransform = Shader(gl, GL.VERTEX_SHADER, "transform-vs.glsl")

  val programs = HashMap<String, Program>()

  fun makeMaterial(name : String) : Pair<String, Material>{
    val program = programs.getOrPut(name){
      val fs = Shader(gl, GL.FRAGMENT_SHADER, "${name}-fs.glsl")
      Program(gl, vsTransform, fs)
    }
    val material = Material(program).apply{
      uniforms["environment"]?.set(skyCubeTexture)
      uniforms.forEach{ (name, uniform) ->
        if(uniform is UniformFloat){
          when(name){
            "kr" -> uniform.set(Random.nextFloat() * 0.33f, Random.nextFloat()* 0.33f, Random.nextFloat(), Random.nextFloat())
            "kd" -> uniform.set(Random.nextFloat() * 0.33f, Random.nextFloat()* 0.33f, Random.nextFloat(), Random.nextFloat())
            "ks" -> uniform.set(Random.nextFloat() * 0.33f, Random.nextFloat()* 0.33f, Random.nextFloat(), Random.nextFloat())
            "shininess" -> uniform.set(Random.nextFloat() * 2.0f)
            else -> {
              uniform.set(Random.nextFloat() * 1000.0f, Random.nextFloat() * 10f, Random.nextFloat() * 10f, Random.nextFloat() * 10f)
            }
          }
        }
      }
    }
    return name to material
  }

val lights = Array<Light>(2){Light(it)}
init{
  lights[1].position.set(0.0f, 0.0f, 0.0f, 1.0f)
  lights[1].powerDensity.set(1000.0f, 1000.0f, 1000.0f)
}

  val materials = arrayOf(
    makeMaterial("envmapped"),
    makeMaterial("phongBlinn2"),
    makeMaterial("phongBlinn"),
    makeMaterial("lambert"),
    makeMaterial("maxBlinn")
  )

  
  val materialCount = materials.size
  val r = materialCount.toFloat() * 5.0f

  val gameObjects = ArrayList<GameObject>()
  init {
    materials.forEachIndexed{
      iMaterial, (materialName, material) ->
      val meshes = exhibitGeometries.map{Mesh(material, it)}.toTypedArray()
      val alpha = iMaterial.toFloat() / materialCount.toFloat() * PI.toFloat() * 2.0f
      gameObjects += GameObject(*meshes).apply{
        yaw = iMaterial * 0.5f;
        position = Vec3(cos(alpha) * r, 0.0f, sin(alpha) * r);
        move = object : GameObject.Motion(this){
          override operator fun invoke(dt : Float, t : Float,  keysPressed : Set<String>, interactors : ArrayList<GameObject>, spawn : ArrayList<GameObject>) : Boolean {
            yaw += dt
            return true
          }
        }
      }
    }
  }

  val camera = PerspectiveCamera()

  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  init{
    gl.enable(GL.DEPTH_TEST)
  }


  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>, timeStamp : Double) {

    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t  = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    timeAtLastFrame = timeAtThisFrame

    camera.move(dt, keysPressed)

    // clear the screen
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)
    gl.clearDepth(1.0f)
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)

    val spawn = ArrayList<GameObject>()
    val killList = ArrayList<GameObject>()    
    gameObjects.forEach { 
      if(!it.move(dt, t, keysPressed, gameObjects, spawn)){
        killList.add(it)
      }
    }
    killList.forEach{ gameObjects.remove(it) }
    spawn.forEach{ gameObjects.add(it) }  
    gameObjects.forEach { it.update() }

    backgroundMesh.draw(camera)
    gameObjects.forEach { it.draw( camera, *lights ) }

    ImGui_Impl.NewFrame(timeStamp)
    ImGui.NewFrame()
    with(dsl) {
      ImGui.SetNextWindowPos(Vec2(ImGui.GetIO().DisplaySize.x, 0.0f), Cond.Always.i, Vec2(1f, 0f))
      window("Material shop", null, WindowFlag.NoMove or WindowFlag.NoTitleBar or WindowFlag.AlwaysAutoResize or WindowFlag.NoResize) {
        materials.forEach{ (materialName, material) ->
          treeNode(materialName){
            material.uniforms.forEach{ (uniformName, uniform) ->
              if(uniform is Vec1){
                slider("${uniformName}", {v -> uniform.x.also{uniform.x = v}}, 0f, 50f){}
              }              
              if(uniform is Vec3){
                slider("${uniformName}.r", {v -> uniform.x.also{uniform.x = v}}, 0f, 10f){}
                slider("${uniformName}.g", {v -> uniform.y.also{uniform.y = v}}, 0f, 10f){}
                slider("${uniformName}.b", {v -> uniform.z.also{uniform.z = v}}, 0f, 10f){}
              }
            }
          }
        }
      }
    }
    ImGui.EndFrame()
    ImGui.Render()
    ImGui_Impl.RenderDrawData(ImGui.GetDrawData())

    overlay.innerHTML = (materials zip gameObjects).map{
      (mp, gameObject) ->
      val (materialName, material) = mp 
      val ndc = gameObject.position.xyz1 * camera.viewProjMatrix
      if(ndc.w > 0) 
      """<div style="color:pink;position:absolute;left:${((ndc.x/ndc.w*0.5f + 0.5f) * canvas.width).toInt()}px;bottom:-${((0.5f - ndc.y/ndc.w * 0.5f) * canvas.height).toInt()}px">${materialName}</div>"""
      else
      ""
    }.joinToString("")
  }
}
