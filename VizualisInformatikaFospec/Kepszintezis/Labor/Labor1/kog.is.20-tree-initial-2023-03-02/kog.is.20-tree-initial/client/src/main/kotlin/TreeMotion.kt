

import vision.gears.webglmath.*

class TreeMotion(gameObject : GameObject) : GameObject.Motion(gameObject){

  val bones by Mat4Array(256)
  val rigging by Mat4Array(4)

  override operator fun invoke(
            dt : Float,
            t : Float,
            keysPressed : Set<String>,
            interactors : ArrayList<GameObject>,
            spawn : ArrayList<GameObject>
    ) : Boolean {
        bones[0].set().scale(1f, 1f, 2f).rotate(1.57f, 1f)
        bones[1].set().scale(1f, 1f, 2f).rotate(1.57f, 1f)
        bones[2].set().scale(1f, 1f, 2f).rotate(1.57f, 1f)
        /*rigging[0] = Mat4Array (1f, 0f, 0f, 0f,
                                0f, 1f, 0f, 0f,
                                0f, 0f, 1f, 0f,
                                0f, 0f, 0f, 1f)*/
        return true
  }
}