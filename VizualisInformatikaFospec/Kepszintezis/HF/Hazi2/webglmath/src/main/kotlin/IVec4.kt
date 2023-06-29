package vision.gears.webglmath

import org.khronos.webgl.Int32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import kotlin.reflect.KProperty
import kotlin.random.Random

@Suppress("NOTHING_TO_INLINE")
class IVec4(backingStorage: Int32Array?, offset: Int = 0) : UniformInt {

  constructor(u: Int = 0, v: Int = 0, s: Int = 0, t: Int = 1) : this(null, 0){
    storage[0] = u
    storage[1] = v
    storage[2] = s
    storage[3] = t
  }
  constructor(other : IVec1, v: Int = 0, s: Int = 0, w: Int = 1) : this(other.storage[0], v, s, w){}
  constructor(other : IVec2, s: Int = 0, w: Int = 1) : this(other.storage[0], other.storage[1], s, w){}
  constructor(other : IVec3, w: Int = 1) : this(other.storage[0], other.storage[1], other.storage[2], w){}
  constructor(other : IVec4) : this(null, 0)  {
    storage.set(other.storage)
  }

  override val storage: Int32Array = backingStorage?.subarray(offset, offset+4)?:Int32Array(4)
  inline var x : Int
    get() = storage[0]
    set(value) { storage[0] = value }
  inline var y : Int
    get() = storage[1]
    set(value) { storage[1] = value }
  inline var z : Int
    get() = storage[2]
    set(value) { storage[2] = value }
  inline var w : Int
    get() = storage[3]
    set(value) { storage[3] = value }    
  inline var xy : IVec2
    get() = IVec2(storage)
    set(value) { IVec2(storage).set(value) }
  inline var xyz : IVec3
    get() = IVec3(storage)
    set(value) { IVec3(storage).set(value) }

  inline fun clone() : IVec4 {
    return IVec4(this)
  }

  override fun set(firstValue : Int, vararg values : Int) : IVec4 {
    storage[0] = firstValue
    storage[1] = values.getOrElse(0) {0}
    storage[2] = values.getOrElse(1) {0}
    storage[3] = values.getOrElse(2) {0}    
    return this
  }

  companion object {
    val zeros = IVec4(0, 0, 0, 0)
    val ones = IVec4(1, 1, 1, 1) 

    inline fun makeRandom(minVal: IVec4 = IVec4.zeros, maxVal: IVec4 = IVec4.ones) : IVec4 {
      return IVec4(
          Random.nextInt() * (maxVal.storage[0] - minVal.storage[0]) + minVal.storage[0],
          Random.nextInt() * (maxVal.storage[1] - minVal.storage[1]) + minVal.storage[1],
          Random.nextInt() * (maxVal.storage[2] - minVal.storage[2]) + minVal.storage[2],                    
          Random.nextInt() * (maxVal.storage[3] - minVal.storage[3]) + minVal.storage[3]
        )  
    }
    inline fun makeRandom(minVal: Int = 0, maxVal: Int = 1) : IVec4 {
      return IVec4.makeRandom(IVec4(minVal, minVal, minVal, minVal), IVec4(maxVal, maxVal, maxVal, maxVal))
    }
  }

  inline fun setRandom(minVal: IVec4 = IVec4.zeros, maxVal: IVec4 = IVec4.ones){
    set(IVec4.makeRandom(minVal, maxVal))
  }
  inline fun setRandom(minVal: Int = 0, maxVal: Int = 1){
    setRandom(IVec4(minVal, minVal, minVal, minVal), IVec4(maxVal, maxVal, maxVal, minVal))
  }

  inline fun clamp(minVal: IVec4 = IVec4.zeros, maxVal: IVec4 = IVec4.ones) : IVec4 {
    if(storage[0] < minVal.storage[0]){
      storage[0] = minVal.storage[0]
    }
    if(storage[1] < minVal.storage[1]){
      storage[1] = minVal.storage[1]
    }
    if(storage[2] < minVal.storage[2]){
      storage[2] = minVal.storage[2]
    }
    if(storage[3] < minVal.storage[3]){
      storage[3] = minVal.storage[3]
    }    
    if(storage[0] > maxVal.storage[0]){
      storage[0] = maxVal.storage[0]
    }
    if(storage[1] > maxVal.storage[1]){
      storage[1] = maxVal.storage[1]
    }
    if(storage[2] > maxVal.storage[2]){
      storage[2] = maxVal.storage[2]
    }        
    if(storage[3] > maxVal.storage[3]){
      storage[3] = maxVal.storage[3]
    }            
    return this
  }

  operator inline fun unaryPlus() : IVec4 {
    return this
  }

  operator inline fun unaryMinus() : IVec4 {
    return IVec4(-storage[0], -storage[1], -storage[2], -storage[3])
  }

  operator inline fun times(scalar : Int) : IVec4 {
    return IVec4(
      storage[0] * scalar,
      storage[1] * scalar,
      storage[2] * scalar,
      storage[3] * scalar
      )
  }

  operator inline fun div(scalar : Int) : IVec4 {
    return IVec4(
      storage[0] / scalar,
      storage[1] / scalar,
      storage[2] / scalar,
      storage[3] / scalar      
      )
  }

  operator inline fun timesAssign(scalar : Int) {
    storage[0] *= scalar
    storage[1] *= scalar
    storage[2] *= scalar    
    storage[3] *= scalar
  }

  operator inline fun divAssign(scalar : Int) {
    storage[0] /= scalar
    storage[1] /= scalar
    storage[2] /= scalar
    storage[3] /= scalar
  }  

  operator inline fun plusAssign(other : IVec4) {
    storage[0] += other.storage[0]
    storage[1] += other.storage[1]
    storage[2] += other.storage[2]
    storage[3] += other.storage[3]
  }

  operator inline fun plus(other : IVec4) : IVec4 {
    return IVec4(
      storage[0] + other.storage[0],
      storage[1] + other.storage[1],
      storage[2] + other.storage[2],
      storage[3] + other.storage[3]
      )
  }

  operator inline fun minusAssign(other : IVec4) {
    storage[0] -= other.storage[0]
    storage[1] -= other.storage[1]
    storage[2] -= other.storage[2]
    storage[3] -= other.storage[3]
  }

  operator inline fun minus(other : IVec4) : IVec4 {
    return IVec4(
      storage[0] - other.storage[0],
      storage[1] - other.storage[1],
      storage[2] - other.storage[2],
      storage[3] - other.storage[3]
      )
  }

  operator inline fun timesAssign(other : IVec4) {
    storage[0] *= other.storage[0]
    storage[1] *= other.storage[1]
    storage[2] *= other.storage[2]
    storage[3] *= other.storage[3]
  }

  operator inline fun times(other : IVec4) : IVec4 {
    return IVec4(
      storage[0] * other.storage[0],
      storage[1] * other.storage[1],
      storage[2] * other.storage[2],
      storage[3] * other.storage[3]
      )
  }

  operator inline fun divAssign(other : IVec4) {
    storage[0] /= other.storage[0]
    storage[1] /= other.storage[1]
    storage[2] /= other.storage[2]
    storage[3] /= other.storage[3]
  }

  operator inline fun div(other : IVec4) : IVec4 {
    return IVec4(
      storage[0] / other.storage[0],
      storage[1] / other.storage[1],
      storage[2] / other.storage[2],
      storage[3] / other.storage[3]
      )
  }       

  inline fun lengthSquared() : Int {
    return storage[0] * storage[0] + storage[1] * storage[1] + storage[2] * storage[2] + storage[3] * storage[3]
  }

  infix inline fun dot(other : IVec4) : Int {
    return (
      storage[0] * other.storage[0] +
      storage[1] * other.storage[1] +
      storage[2] * other.storage[2] +
      storage[3] * other.storage[3] )
  }

  operator fun provideDelegate(
      provider: UniformProvider,
      property: KProperty<*>) : IVec4 {
    provider.register(property.name, this)
    return this
  }

  operator fun getValue(provider: UniformProvider, property: KProperty<*>): IVec4 {
    return this
  }

  operator fun setValue(provider: UniformProvider, property: KProperty<*>, value: IVec4) {
    set(value)
  }

  override fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int){
    gl.uniform4iv(uniformLocation, storage)
  }
}

@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.times(v: IVec4) = IVec4(this * v.storage[0], this * v.storage[1], this * v.storage[2], this * v.storage[3])
@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.div(v: IVec4) = IVec4(this / v.storage[0], this / v.storage[1], this / v.storage[2], this / v.storage[3])
