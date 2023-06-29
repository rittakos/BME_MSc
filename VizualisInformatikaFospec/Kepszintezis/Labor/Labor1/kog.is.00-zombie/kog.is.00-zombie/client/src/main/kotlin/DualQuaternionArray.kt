import vision.gears.webglmath.Vec4Array

class DualQuaternionArray(backingVec4Array: Vec4Array?, startIndex: Int = 0, endIndex: Int = 0) {

  constructor(size : Int) : this(null, size, size) {}

  val qt = backingVec4Array?.subarray(startIndex*2, endIndex*2)?:Vec4Array(startIndex*2)
  val storage = qt.storage
  val length = storage.length / 8

  operator fun get(index : Int) : DualQuaternion {
    return DualQuaternion(qt[index*2], qt[index*2+1])
  }

  fun subarray(begin : Int, end : Int) : DualQuaternionArray {
    return DualQuaternionArray(qt, begin, end)
  }

  fun fill(value : DualQuaternion) {
    for(i in 0 until length) {
    	qt[i*2].set(value.q)
    	qt[i*2+1].set(value.t)
    }
  }
}

