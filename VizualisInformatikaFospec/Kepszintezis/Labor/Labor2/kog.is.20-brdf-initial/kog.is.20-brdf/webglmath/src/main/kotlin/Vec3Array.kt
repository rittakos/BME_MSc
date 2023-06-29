package vision.gears.webglmath

import org.khronos.webgl.Float32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import kotlin.reflect.KProperty
import kotlin.random.Random
import kotlin.math.pow
import kotlin.math.sqrt
/*import kotlinx.serialization.*
import kotlinx.serialization.descriptors.*
import kotlinx.serialization.json.*
import kotlinx.serialization.encoding.*

object Vec3ArraySerializer : KSerializer<Vec3Array> {
  @kotlinx.serialization.InternalSerializationApi
  override val descriptor: SerialDescriptor =
    buildSerialDescriptor("vision.gears.Vec3Array", StructureKind.LIST)
  override fun deserialize(decoder: Decoder): Vec3Array {
    val input = decoder as? JsonDecoder ?: throw SerializationException("Expected Json Input")
    val array = input.decodeJsonElement() as? JsonArray ?: throw SerializationException("Expected JsonArray")
    val va = Vec3Array(array.size)
    array.forEachIndexed{ (i : Int, e : JsonElement) ->
      val qrr = e as? JsonArray ?: throw SerializationException("Expected JsonArray of JsonArrays")
      va.storage[i*3 + 0] = qrr?.getOrNull(0)?.float ?: 0.0f
      va.storage[i*3 + 1] = qrr?.getOrNull(1)?.float ?: 0.0f
      va.storage[i*3 + 2] = qrr?.getOrNull(2)?.float ?: 0.0f            
    }
    return va
  }
  override fun serialize(encoder: Encoder, value : Vec3Array) {
    val output = encoder as? JsonEncoder ?: throw SerializationException("This class can be saved only by Json")
    val array = buildJsonArray {
      for(i in 0 until storage.length/3) {
        buildJsonArray {
          add(storage[i*3+0])
          add(storage[i*3+1])
          add(storage[i*3+2])                
        }
      }
    }
    output.encodeJsonElement(array)
  }      
}

@Serializable(with = Vec3ArraySerializer::class)*/
class Vec3Array(backingStorage: Float32Array?, startIndex: Int = 0, endIndex: Int = 0) : VecArray() {

  constructor(size : Int) : this(null, size, size) {}

  override val storage = backingStorage?.subarray(startIndex*3, endIndex*3)?:Float32Array(startIndex*3)

  override fun set(vararg values : Float) : Vec3Array {
    for(i in 0 until storage.length) {
      storage[i] = values.getOrNull(i%3) ?: 0.0f
    }
    return this
  }

  operator fun get(i : Int) : Vec3{
    return Vec3(storage, i*3)
  }

  fun subarray(begin : Int, end : Int) : Vec3Array {
    return Vec3Array(storage, begin, end)
  }

  fun setNormalized(b : Vec3Array) {
    for(i in 0 until storage.length step 3) {
      val l2 =
        b.storage[i  ] * b.storage[i  ] +
        b.storage[i+1] * b.storage[i+1] +
        b.storage[i+2] * b.storage[i+2]
      val linv = 1 / sqrt(l2)
      storage[i  ] = b.storage[i  ] * linv
      storage[i+1] = b.storage[i+1] * linv
      storage[i+2] = b.storage[i+2] * linv
    }
  }

  fun setCrossed(b : Vec3Array, c : Vec3Array) {
    var j = 0
    for(i in 0 until storage.length step 3) {
      val b0 = b.storage[j]
      val c0 = c.storage[j++]    
      val b1 = b.storage[j]
      val c1 = c.storage[j++]    
      val b2 = b.storage[j]
      val c2 = c.storage[j++]
      storage[i  ] = b1 * c2 - b2 * c1
      storage[i+1] = b2 * c0 - b0 * c2
      storage[i+2] = b0 * c1 - b1 * c0 
    }
  }  

  fun setAffineTransformed(v : Vec3Array, m : Mat4) {  
    for(i in 0 until storage.length step 3) {
      storage[i+0] =
         v.storage[i+0] * m.storage[ 0] +
         v.storage[i+1] * m.storage[ 1] +
         v.storage[i+2] * m.storage[ 2] +
                          m.storage[ 3]
      storage[i+1] =
         v.storage[i+0] * m.storage[ 4] +
         v.storage[i+1] * m.storage[ 5] +
         v.storage[i+2] * m.storage[ 6] +
                          m.storage[ 7]
      storage[i+2] =
         v.storage[i+0] * m.storage[ 8] +
         v.storage[i+1] * m.storage[ 9] +
         v.storage[i+2] * m.storage[10] +
                          m.storage[11]      
    }
  }

  fun setAffineNormalTransformed(v : Vec3Array, m : Mat4) {  
    for(i in 0 until storage.length step 3) {
      storage[i+0] =
         v.storage[i+0] * m.storage[ 0] +
         v.storage[i+1] * m.storage[ 1] +
         v.storage[i+2] * m.storage[ 2]
      storage[i+1] =
         v.storage[i+0] * m.storage[ 4] +
         v.storage[i+1] * m.storage[ 5] +
         v.storage[i+2] * m.storage[ 6]
      storage[i+2] =
         v.storage[i+0] * m.storage[ 8] +
         v.storage[i+1] * m.storage[ 9] +
         v.storage[i+2] * m.storage[10]      
    }
  }  

  operator fun provideDelegate(
      provider: UniformProvider,
      property: KProperty<*>) : Vec3Array {
    provider.register(property.name, this)
    return this
  }

  operator fun getValue(provider: UniformProvider, property: KProperty<*>): Vec3Array {
    return this
  }
  
  operator fun setValue(provider: UniformProvider, property: KProperty<*>, value: Vec3Array) {
    set(value)
  }  

  override fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int){
    gl.uniform3fv(uniformLocation, storage)
  }  
} 