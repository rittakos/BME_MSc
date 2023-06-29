package vision.gears.webglmath

import org.khronos.webgl.Int32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import kotlin.reflect.KProperty
import kotlin.random.Random

@Suppress("NOTHING_TO_INLINE")
class IVec2(backingStorage: Int32Array?, offset: Int = 0) : UniformInt {

  constructor(u: Int = 0, v: Int = 0) : this(null, 0){
    storage[0] = u
    storage[1] = v
  }
  constructor(other : IVec1, v: Int = 0) : this(other.storage[0], v ){}
  constructor(other : IVec2) : this(null, 0)  {
    storage.set(other.storage)
  }

  override val storage: Int32Array = backingStorage?.subarray(offset, offset+2)?:Int32Array(2)
  inline var x : Int
    get() = storage[0]
    set(value) { storage[0] = value }
  inline var y : Int
    get() = storage[1]
    set(value) { storage[1] = value }
  inline val xy0 : IVec3
    get() = IVec3(storage[0], storage[1], 0)
  inline val xy00 : IVec4
    get() = IVec4(storage[0], storage[1], 0, 0)    
  inline val xy01 : IVec4
    get() = IVec4(storage[0], storage[1], 0, 1)

  inline fun clone() : IVec2 {
    return IVec2(this)
  }

  override fun set(firstValue : Int, vararg values : Int) : IVec2 {
    storage[0] = firstValue
    storage[1] = values.getOrElse(0) {0}
    return this
  }

  companion object {
    val zeros = IVec2()
    val ones = IVec2(1, 1) 

    inline fun makeRandom(minVal: IVec2 = IVec2.zeros, maxVal: IVec2 = IVec2.ones) : IVec2 {
      return IVec2(
          Random.nextInt() * (maxVal.storage[0] - minVal.storage[0]) + minVal.storage[0],
          Random.nextInt() * (maxVal.storage[1] - minVal.storage[1]) + minVal.storage[1]
        )  
    }
    inline fun makeRandom(minVal: Int = 0, maxVal: Int = 1) : IVec2 {
      return IVec2.makeRandom(IVec2(minVal, minVal), IVec2(maxVal, maxVal))
    }
  }

  inline fun randomize(minVal: IVec2 = IVec2.zeros, maxVal: IVec2 = IVec2.ones){
    set(IVec2.makeRandom(minVal, maxVal))
  }
  inline fun randomize(minVal: Int = 0, maxVal: Int = 1){
    randomize(IVec2(minVal, minVal), IVec2(maxVal, maxVal))
  }

  inline fun clamp(minVal: IVec2 = IVec2.zeros, maxVal: IVec2 = IVec2.ones) : IVec2 {
    if(storage[0] < minVal.storage[0]){
      storage[0] = minVal.storage[0]
    }
    if(storage[1] < minVal.storage[1]){
      storage[1] = minVal.storage[1]
    }
    if(storage[0] > maxVal.storage[0]){
      storage[0] = maxVal.storage[0]
    }
    if(storage[1] > maxVal.storage[1]){
      storage[1] = maxVal.storage[1]
    }
    return this
  }

  operator inline fun unaryPlus() : IVec2 {
    return this
  }

  operator inline fun unaryMinus() : IVec2 {
    return IVec2(-storage[0], -storage[1])
  }

  operator inline fun times(scalar : Int) : IVec2 {
    return IVec2(
      storage[0] * scalar,
      storage[1] * scalar
      )
  }

  operator inline fun div(scalar : Int) : IVec2 {
    return IVec2(
      storage[0] / scalar,
      storage[1] / scalar      
      )
  }

  operator inline fun timesAssign(scalar : Int) {
    storage[0] *= scalar
    storage[1] *= scalar
  }

  operator inline fun divAssign(scalar : Int) {
    storage[0] /= scalar
    storage[1] /= scalar
  }

  operator inline fun plusAssign(other : IVec2) {
    storage[0] += other.storage[0]
    storage[1] += other.storage[1]
  }

  operator inline fun plus(other : IVec2) : IVec2 {
    return IVec2(
      storage[0] + other.storage[0],
      storage[1] + other.storage[1]
      )
  }

  operator inline fun minusAssign(other : IVec2) {
    storage[0] -= other.storage[0]
    storage[1] -= other.storage[1]
  }

  operator inline fun minus(other : IVec2) : IVec2 {
    return IVec2(
      storage[0] - other.storage[0],
      storage[1] - other.storage[1]
      )
  }

  operator inline fun timesAssign(other : IVec2) {
    storage[0] *= other.storage[0]
    storage[1] *= other.storage[1]
  }

  operator inline fun times(other : IVec2) : IVec2 {
    return IVec2(
      storage[0] * other.storage[0],
      storage[1] * other.storage[1]
      )
  }

  operator inline fun divAssign(other : IVec2) {
    storage[0] /= other.storage[0]
    storage[1] /= other.storage[1]
  }

  operator inline fun div(other : IVec2) : IVec2 {
    return IVec2(
      storage[0] / other.storage[0],
      storage[1] / other.storage[1]
      )
  }       

  inline fun lengthSquared() : Int {
    return storage[0] * storage[0] + storage[1] * storage[1]
  }

  infix inline fun dot(other : IVec2) : Int {
    return (
     storage[0] * other.storage[0] +
     storage[1] * other.storage[1] )
  }

  operator fun provideDelegate(
      provider: UniformProvider,
      property: KProperty<*>) : IVec2 {
    provider.register(property.name, this)
    return this
  }

  operator fun getValue(provider: UniformProvider, property: KProperty<*>): IVec2 {
    return this
  }

  operator fun setValue(provider: UniformProvider, property: KProperty<*>, value: IVec2) {
    set(value)
  }
  
  override fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int){
    gl.uniform2iv(uniformLocation, storage)
  }
}

@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.times(v: IVec2) = IVec2(this * v.storage[0], this * v.storage[1])
@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.div(v: IVec2) = IVec2(this / v.storage[0], this / v.storage[1])
