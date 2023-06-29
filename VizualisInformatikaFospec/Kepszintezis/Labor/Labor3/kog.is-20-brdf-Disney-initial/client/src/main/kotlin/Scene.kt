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
            "kd" -> uniform.set(Random.nextFloat() * 0.33f, Random.nextFloat()* 0.33f, Random.nextFloat(), Random.nextFloat()* 0.33f)
            "kr" -> uniform.set(Random.nextFloat() * 0.33f, Random.nextFloat()* 0.33f, Random.nextFloat(), Random.nextFloat())
            "ks" -> {
              val xi = Random.nextFloat() * 2.0f
              uniform.set(xi, xi, xi)
            }
            "shininess" -> {
              uniform.set(Random.nextFloat() * 50.0f)
            }
            "roughness" -> uniform.set(Random.nextFloat())
            "sdspecular" -> uniform.set(Random.nextFloat())
            "metallic" -> uniform.set(Random.nextFloat())
            "specular" -> uniform.set(Random.nextFloat())
            "subsurface" -> uniform.set(Random.nextFloat())
            "sheen" -> uniform.set(Random.nextFloat())
            "sheenTint" -> uniform.set(Random.nextFloat())
            "clearcoat" -> uniform.set(Random.nextFloat())
            "clearcoatGloss" -> uniform.set(Random.nextFloat())
            "anisotropic" -> uniform.set(Random.nextFloat())
            "baseColor" -> {
              val xi = Random.nextFloat()
              uniform.set(xi, xi, xi)
            }
            else -> {
              uniform.set(Random.nextFloat() * 1f, Random.nextFloat() * 1f, Random.nextFloat() * 1f, Random.nextFloat() * 1f)
            }
          }
        }
      }
    }
    return name to material
  }

  val materials = arrayOf(
    makeMaterial("envmapped"),
    makeMaterial("disney")
  )

  val gameObjects = ArrayList<GameObject>()
  init {
    val radius = materials.size.toFloat() * 5.0f
    materials.forEachIndexed{
      iMaterial, (materialName, material) ->
      val phi = iMaterial.toFloat() / materials.size.toFloat() * PI.toFloat() * 2f
      val mesh = Mesh(material, exhibitGeometries[0])
      gameObjects += GameObject(mesh)
      .apply{
        yaw = iMaterial.toFloat()
        position.set(
          cos(phi) * radius,
          -10f,
          sin(phi) * radius
        )
      //  move = object : GameObject.Motion(this){
      //    override operator fun invoke(
      //      dt : Float,
      //      t : Float,
      //      keysPressed : Set<String>,
      //      interactors : ArrayList<GameObject>,
      //      spawn : ArrayList<GameObject>
      //      ) : Boolean {
      //      yaw += dt
      //      return true
      //    }
      //  }
      }
    }
  }

  val lights = Array<Light>(1) { Light(it) }
  init{
    lights[0].position.set(1.0f, 1.0f, 1.0f, 0.0f).normalize()
    lights[0].powerDensity.set(5.0f, 5.0f, 5.0f)
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
                slider("${uniformName}", {v -> uniform.x.also{uniform.x = v}}, 0f, 1f){}
              }              
              if(uniform is Vec3){
                slider("${uniformName}.r", {v -> uniform.x.also{uniform.x = v}}, 0f, 1f){}
                slider("${uniformName}.g", {v -> uniform.y.also{uniform.y = v}}, 0f, 1f){}
                slider("${uniformName}.b", {v -> uniform.z.also{uniform.z = v}}, 0f, 1f){}
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
