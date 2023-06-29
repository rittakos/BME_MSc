import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Vec4
import vision.gears.webglmath.Mat4
import kotlin.math.sqrt
import org.khronos.webgl.get

class DualQuaternion(
  val q : Vec4 = Vec4(0.0f, 0.0f, 0.0f, 1.0f),
  val t : Vec4 = Vec4(0.0f, 0.0f, 0.0f, 0.0f)
  ) {

  fun fromMatrix(matrix : Mat4) {
    val m = matrix.storage
    val t = 1.0f + m[0] + m[5] + m[10]

    // large enough
    if( t > 0.001) {
      val s = sqrt( t) * 2.0f
      q.x = (m[9] - m[6]) / s
      q.y = (m[2] - m[8]) / s
      q.z = (m[4] - m[1]) / s
      q.w = 0.25f * s
    } else if( m[0] > m[5] && m[0] > m[10] ) { 
      // Column 0: 
      val s = sqrt( 1.0f + m[0] - m[5] - m[10]) * 2.0f
      q.x = 0.25f * s
      q.y = (m[4] + m[1]) / s
      q.z = (m[2] + m[8]) / s
      q.w = (m[9] - m[6]) / s
    } else if( m[5] > m[10]) { 
      // Column 1: 
      val s = sqrt( 1.0f + m[5] - m[0] - m[10]) * 2.0f
      q.x = (m[4] + m[1]) / s
      q.y = 0.25f * s
      q.z = (m[9] + m[6]) / s
      q.w = (m[2] - m[8]) / s
    } else { 
      // Column 2:
      val s = sqrt( 1.0f + m[10] - m[0] - m[5]) * 2.0f
      q.x = (m[2] + m[8]) / s
      q.y = (m[9] + m[6]) / s
      q.z = 0.25f * s
      q.w = (m[4] - m[1]) / s
    }

    val l = q.length();

    if(l < 0.99 || l > 1.01) {
      console.log("nonononorm")
    }

    setTranslation(Vec3(m[3], m[7], m[11]))
  }

  fun setTranslation(tv : Vec3) {
    t.x = 0.5f*( tv.x*q.w + tv.y*q.z - tv.z*q.y)
    t.y = 0.5f*(-tv.x*q.z + tv.y*q.w + tv.z*q.x)
    t.z = 0.5f*( tv.x*q.y - tv.y*q.x + tv.z*q.w)
    t.w =-0.5f*( tv.x*q.x + tv.y*q.y + tv.z*q.z)
  }

  fun setTranslationFromArray(ta : Array<Float>) {
    t.x = 0.5f*( ta[0]*q.w + ta[1]*q.z - ta[2]*q.y)
    t.y = 0.5f*(-ta[0]*q.z + ta[1]*q.w + ta[2]*q.x)
    t.z = 0.5f*( ta[0]*q.y - ta[1]*q.x + ta[2]*q.w)
    t.w =-0.5f*( ta[0]*q.x + ta[1]*q.y + ta[2]*q.z)
  }

  fun setRotationFromArray(qa : Array<Float>) {
    q.x = qa[1]
    q.y = qa[2]
    q.z = qa[3]
    q.w = qa[0]
  }
}