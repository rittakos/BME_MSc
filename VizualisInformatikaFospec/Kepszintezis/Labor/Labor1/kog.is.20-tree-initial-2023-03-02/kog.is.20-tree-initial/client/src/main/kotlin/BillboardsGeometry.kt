import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import org.khronos.webgl.Uint16Array
import vision.gears.webglmath.*

class BillboardsGeometry(val gl : WebGL2RenderingContext) : Geometry() {

  val vertexBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( arrayOf<Float>(
        -1.0f, -1.0f, 0.999999f,
        -1.0f,  1.0f, 0.999999f,
         1.0f, -1.0f, 0.999999f,
         1.0f,  1.0f, 0.999999f
      )),
      GL.STATIC_DRAW)
  }

  val vertexNormalBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexNormalBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( arrayOf<Float>(
         0.0f,  0.0f, 1.0f,
         0.0f,  0.0f, 1.0f,
         0.0f,  0.0f, 1.0f,
         0.0f,  0.0f, 1.0f
      )),
      GL.STATIC_DRAW)
  }

  val vertexTexCoordBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexTexCoordBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( arrayOf<Float>(
         0.0f,  1.0f, 
         0.0f,  0.0f, 
         1.0f,  1.0f, 
         1.0f,  0.0f
         )),
      GL.STATIC_DRAW)
  }    

  val billboardCount = 4096
  val billboardPoolSize = 4096
  val billboardPositions = Vec4Array(billboardPoolSize)
  val billboardNormals = Vec4Array(billboardPoolSize)
  init{
    billboardPositions.randomize()
    billboardNormals.randomize()

    for(i in 0 until billboardCount){
      billboardPositions[i].w = 1f
      billboardPositions[i].xyz.plusAssign(Vec3(-0.5f, -0.5f, -0.5f))
    }
  }

  val billboardPositionBuffer = gl.createBuffer()
  val billboardNormalBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, billboardPositionBuffer) 
    gl.bufferData(GL.ARRAY_BUFFER,
      billboardPositions.storage, 
      GL.DYNAMIC_DRAW)
    gl.bindBuffer(GL.ARRAY_BUFFER, billboardNormalBuffer) 
    gl.bufferData(GL.ARRAY_BUFFER,
      billboardNormals.storage,
      GL.DYNAMIC_DRAW) 
  }

  val indexBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, indexBuffer)
    gl.bufferData(GL.ELEMENT_ARRAY_BUFFER,
      Uint16Array( arrayOf<Short>(
        0, 1, 2,
        1, 2, 3
      )),
      GL.STATIC_DRAW)
  }

  val inputLayout = gl.createVertexArray()
  init{
    gl.bindVertexArray(inputLayout)

    gl.bindBuffer(GL.ARRAY_BUFFER, vertexBuffer)
    gl.enableVertexAttribArray(0)
    gl.vertexAttribPointer(0,
      3, GL.FLOAT, //< three pieces of float
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexNormalBuffer)
    gl.enableVertexAttribArray(1)
    gl.vertexAttribPointer(1,
      3, GL.FLOAT, //< three pieces of float
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexTexCoordBuffer)
    gl.enableVertexAttribArray(2)
    gl.vertexAttribPointer(2,
      2, GL.FLOAT, //< two pieces of float
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )    

    gl.bindBuffer(GL.ARRAY_BUFFER, billboardPositionBuffer)
    gl.enableVertexAttribArray(3)
    gl.vertexAttribPointer(3,
      4, GL.FLOAT, //< two pieces of float
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )    
    gl.vertexAttribDivisor(3, 1)

    gl.bindBuffer(GL.ARRAY_BUFFER, billboardNormalBuffer)
    gl.enableVertexAttribArray(4)
    gl.vertexAttribPointer(4,
      4, GL.FLOAT, //< two pieces of float
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )    
    gl.vertexAttribDivisor(4, 1)

    gl.bindVertexArray(null)    
  }

  override fun draw() {
    gl.bindVertexArray(inputLayout)
    gl.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, indexBuffer)  

    gl.drawElementsInstanced(GL.TRIANGLES, 6, GL.UNSIGNED_SHORT,
      0, billboardCount)
  }
}
