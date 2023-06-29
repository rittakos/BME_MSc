package vision.gears.webglmath

import org.khronos.webgl.Int32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import kotlin.reflect.KProperty
import kotlin.random.Random

@Suppress("NOTHING_TO_INLINE")
class IVec1(backingStorage: Int32Array?, offset: Int = 0) : UniformInt {

  constructor(u: Int = 0) : this(null, 0){
    storage[0] = u
  }
  constructor(other : IVec1) : this(null, 0)  {
    storage.set(other.storage)
  }

  override val storage: Int32Array = backingStorage?.subarray(offset, offset+1)?:Int32Array(1)
  inline var x : Int
    get() = storage[0]
    set(value) { storage[0] = value }
  inline val xx : IVec2
    get() = IVec2(storage[0], storage[0])
  inline val xxx : IVec3
    get() = IVec3(storage[0], storage[0], storage[0])
  inline val xxxx : IVec4
    get() = IVec4(storage[0], storage[0], storage[0], storage[0])

  inline fun clone() : IVec1 {
    return IVec1(this)
  }

  override fun set(firstValue : Int, vararg values : Int) : IVec1 {
    storage[0] = firstValue
    return this 
  }

  companion object {
    val zeros = IVec1()
    val ones = IVec1(1)
  }

  inline fun clamp(minVal: IVec1 = IVec1.zeros, maxVal: IVec1 = IVec1.ones) : IVec1 {
    if(storage[0] < minVal.storage[0]){
      storage[0] = minVal.storage[0]
    }
    if(storage[0] > maxVal.storage[0]){
      storage[0] = maxVal.storage[0]
    }
    return this
  }

  operator inline fun unaryPlus() : IVec1 {
    return this
  }

  operator inline fun times(scalar : Int) : IVec1 {
    return IVec1(
      storage[0] * scalar
      )
  }

  operator inline fun div(scalar : Int) : IVec1 {
    return IVec1(
      storage[0] / scalar
      )
  }

  operator inline fun timesAssign(scalar : Int) {
    storage[0] *= scalar
  }

  operator inline fun divAssign(scalar : Int) {
    storage[0] /= scalar
  }    

  operator inline fun plusAssign(other : IVec1) {
    storage[0] += other.storage[0]
  }

  operator inline fun plus(other : IVec1) : IVec1 {
    return IVec1(
      storage[0] + other.storage[0]
      )
  }

  operator inline fun minusAssign(other : IVec1) {
    storage[0] -= other.storage[0]
  }

  operator inline fun minus(other : IVec1) : IVec1 {
    return IVec1(
      storage[0] - other.storage[0]
      )
  }

  operator inline fun timesAssign(other : IVec1) {
    storage[0] *= other.storage[0]
  }

  operator inline fun times(other : IVec1) : IVec1 {
    return IVec1(
      storage[0] * other.storage[0]
      )
  }

  operator inline fun divAssign(other : IVec1) {
    storage[0] /= other.storage[0]
  }

  operator inline fun div(other : IVec1) : IVec1 {
    return IVec1(
      storage[0] / other.storage[0]
      )
  }       

  inline fun lengthSquared() : Int {
    return storage[0] * storage[0]
  }

  inline fun length() : Int {
    return storage[0]
  }

  operator fun provideDelegate(
      provider: UniformProvider,
      property: KProperty<*>) : IVec1 {
    provider.register(property.name, this)
    return this
  }

  operator fun getValue(provider: UniformProvider, property: KProperty<*>): IVec1 {
    return this
  }

  operator fun setValue(provider: UniformProvider, property: KProperty<*>, value: IVec1) {
    set(value)
  }

  override fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int){
    gl.uniform1iv(uniformLocation, storage)
  }
}

@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.times(v: IVec1) = IVec1(this * v.storage[0])
@Suppress("NOTHING_TO_INLINE")
operator inline fun Int.div(v: IVec1) = IVec1(this / v.storage[0])
