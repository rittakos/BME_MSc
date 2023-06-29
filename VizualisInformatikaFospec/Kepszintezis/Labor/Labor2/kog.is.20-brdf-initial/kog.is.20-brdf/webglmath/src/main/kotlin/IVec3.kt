package vision.gears.webglmath

import org.khronos.webgl.Int32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import kotlin.reflect.KProperty
import kotlin.random.Random


@Suppress("NOTHING_TO_INLINE")
class IVec3(backingStorage: Int32Array?, offset: Int = 0) : UniformInt {

  constructor(u: Int = 0, v: Int = 0, s: Int = 0) : this(null, 0){
    storage[0] = u
    storage[1] = v
    storage[2] = s
  }
  constructor(other : IVec1, v: Int = 0, s: Int = 0) : this(other.storage[0], v, s){}
  constructor(other : IVec2, s: Int = 0) : this(other.storage[0], other.storage[1], s){}
  constructor(other : IVec3) : this(null, 0)  {
    storage.set(other.storage)
  }
  constructor(other : IVec4) : this(other.storage[0]/other.storage[3], other.storage[1]/other.storage[3], other.storage[2]/other.storage[3]){}

  override val storage: Int32Array = backingStorage?.subarray(offset, offset+3)?:Int32Array(3)
  inline var x : Int
    get() = storage[0]
    set(value) { storage[0] = value }
  inline var y : Int
    get() = storage[1]
    set(value) { storage[1] = value }
  inline var z : Int
    get() = storage[2]
    set(value) { storage[2] = value }
  inline var xy : IVec2
    get() = IVec2(storage)
    set(value) { IVec2(storage).set(value) }
  inline val xyz0 : IVec4
    get() = IVec4(storage[0], storage[1], storage[2], 0)    
  inline val xyz1 : IVec4
    get() = IVec4(storage[0], storage[1], storage[2], 1)

  inline fun clone() : IVec3 {
    return IVec3(this)
  }

  override fun set(firstValue : Int, vararg values : Int) : IVec3 {
    storage[0] = firstValue
    storage[1] = values.getOrElse(0) {0}
    storage[2] = values.getOrElse(1) {0}    
    return this
  }

  companion object {
    val zeros = IVec3()
    val ones = IVec3(1, 1, 1) 

    inline fun makeRandom(minVal: IVec3 = IVec3.zeros, maxVal: IVec3 = IVec3.ones) : IVec3 {
      return IVec3(
          Random.nextInt() * (maxVal.storage[0] - minVal.storage[0]) + minVal.storage[0],
          Random.nextInt() * (maxVal.storage[1] - minVal.storage[1]) + minVal.storage[1],
          Random.nextInt() * (maxVal.storage[2] - minVal.storage[2]) + minVal.storage[2]                    
        )  
    }
    inline fun makeRandom(minVal: Int = 0, maxVal: Int = 1) : IVec3 {
      return IVec3.makeRandom(IVec3(minVal, minVal, minVal), IVec3(maxVal, maxVal, maxVal))
    }
  }

  inline fun randomize(minVal: IVec3 = IVec3.zeros, maxVal: IVec3 = IVec3.ones){
    set(IVec3.makeRandom(minVal, maxVal))
  }
  inline fun randomize(minVal: Int = 0, maxVal: Int = 1){
    randomize(IVec3(minVal, minVal, minVal), IVec3(maxVal, maxVal, maxVal))
  }

  inline fun clamp(minVal: IVec3 = IVec3.zeros, maxVal: IVec3 = IVec3.ones) : IVec3 {
    if(storage[0] < minVal.storage[0]){
      storage[0] = minVal.storage[0]
    }
    if(storage[1] < minVal.storage[1]){
      storage[1] = minVal.storage[1]
    }
    if(storage[2] < minVal.storage[2]){
      storage[2] = minVal.storage[2]
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
    return this
  }

  operator inline fun get(index : Int) : Int {
    return storage[index]
  }

  operator fun set(index: Int, value: Int) {
    storage[index] = value 
  }  

  operator inline fun unaryPlus() : IVec3 {
    return this
  }

  operator inline fun unaryMinus() : IVec3 {
    return IVec3(-storage[0], -storage[1], -storage[2])
  }

  operator inline fun times(scalar : Int) : IVec3 {
    return IVec3(
      storage[0] * scalar,
      storage[1] * scalar,
      storage[2] * scalar
      )
  }

  operator inline fun div(scalar : Int) : IVec3 {
    return IVec3(
      storage[0] / scalar,
      storage[1] / scalar,
      storage[2] / scalar      
      )
  }

  operator inline fun timesAssign(scalar : Int) {
    storage[0] *= scalar
    storage[1] *= scalar
    storage[2] *= scalar    
  }

  operator inline fun divAssign(scalar : Int) {
    storage[0] /= scalar
    storage[1] /= scalar
    storage[2] /= scalar
  }

  operator inline fun plusAssign(other : IVec3) {
    storage[0] += other.storage[0]
    storage[1] += other.storage[1]
    storage[2] += other.storage[2]
  }

  operator inline fun plus(other : IVec3) : IVec3 {
    return IVec3(
      storage[0] + other.storage[0],
      storage[1] + other.storage[1],
      storage[2] + other.storage[2]
      )
  }

  operator inline fun minusAssign(other : IVec3) {
    storage[0] -= other.storage[0]
    storage[1] -= other.storage[1]
    storage[2] -= other.storage[2]
  }

  operator inline fun minus(other : IVec3) : IVec3 {
    return IVec3(
      storage[0] - other.storage[0],
      storage[1] - other.storage[1],
      storage[2] - other.storage[2]
      )
  }

  operator inline fun timesAssign(other : IVec3) {
    storage[0] *= other.storage[0]
    storage[1] *= other.storage[1]
    storage[2] *= other.storage[2]
  }

  operator inline fun times(other : IVec3) : IVec3 {
    return IVec3(
      storage[0] * other.storage[0],
      storage[1] * other.storage[1],
      storage[2] * other.storage[2]
      )
  }

  operator inline fun divAssign(other : IVec3) {
    storage[0] /= other.storage[0]
    storage[1] /= other.storage[1]
    storage[2] /= other.storage[2]
  }

  operator inline fun div(other : IVec3) : IVec3 {
    return IVec3(
      storage[0] / other.storage[0],
      storage[1] / other.storage[1],
      storage[2] / other.storage[2]
      )
  }       

  inline fun lengthSquared() : Int {
    return storage[0] * storage[0] + storage[1] * storage[1] + storage[2] * storage[2]
  }

  infix inline fun dot(other : IVec3) : Int {
    return (
      storage[0] * other.storage[0] +
      storage[1] * other.storage[1] +
      storage[2] * other.storage[2] )
  }

  infix inline fun cross(other : IVec3) : IVec3 {
    return IVec3(
      storage[1] * other.storage[2] - storage[2] * other.storage[1],
      storage[2] * other.storage[0] - storage[0] * other.storage[2],
      storage[0] * other.storage[1] - storage[1] * other.storage[0])
  }

  operator fun provideDelegate(
      provider: UniformProvider,
      property: KProperty<*>) : IVec3 {
    provider.register(property.name, this)
    return this
  }

  operator fun getValue(provider: UniformProvider, property: KProperty<*>): IVec3 {
    return this
  }

  operator fun setValue(provider: UniformProvider, property: KProperty<*>, value: IVec3) {
    set(value)
  }

  override fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int){
    gl.uniform3iv(uniformLocation, storage)
  }
}

@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.times(v: IVec3) = IVec3(v.x * this, v.y * this, v.z * this)
@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.div(v: IVec3) = IVec3(this / v.x, this / v.y, this / v.z)