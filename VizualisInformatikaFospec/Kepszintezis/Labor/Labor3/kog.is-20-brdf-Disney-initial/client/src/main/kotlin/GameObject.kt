import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.*


open class GameObject(vararg meshes : Mesh) : UniformProvider("gameObject") {

  val position = Vec3()
  var roll = 0.0f 
  var yaw = 0.0f
  var pitch = 0.0f     
  val scale = Vec3(1.0f, 1.0f, 1.0f)  

  val modelMatrix by Mat4()
  val modelMatrixInverse by Mat4()  

  var parent : GameObject? = null

  init {
    addComponentsAndGatherUniforms(*meshes)
  }

  fun update(){
    modelMatrix.set().
      scale(scale).
      rotate(roll).
      rotate(pitch, 1.0f, 0.0f, 0.0f).
      rotate(yaw, 0.0f, 1.0f, 0.0f).
      translate(position)
    parent?.let { parent ->
      parent.update()
      modelMatrix *= parent.modelMatrix
    }
    modelMatrixInverse.set(modelMatrix).invert()

  }

  open class Motion(val gameObject : GameObject){
    open operator fun invoke(
      dt : Float,
      t : Float,
      keysPressed : Set<String>,
      interactors : ArrayList<GameObject>,
      spawn : ArrayList<GameObject>
      ) : Boolean {
      return true
    }
  }
  var move = Motion(this)

}