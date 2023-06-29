import vision.gears.webglmath.*

class Light(id : Int) : UniformProvider("lights[$id]") {

  val position by Vec4(0.0f, 1.0f, 0.0f, 0.0f) 
  val powerDensity by Vec3(0.0f, 0.0f, 0.0f)
    
}