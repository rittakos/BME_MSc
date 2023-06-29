import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import org.khronos.webgl.Uint16Array
import org.khronos.webgl.Uint8Array
import org.khronos.webgl.set
import org.khronos.webgl.get
import vision.gears.webglmath.Geometry
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Mat4Array

class RiggedGeometry(
  val gl : WebGL2RenderingContext,
  val jsonMesh : JsonRiggedMesh,
  ) : Geometry() {
   
  var nInstances : Int = 1

  val vertexBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( jsonMesh.vertices ),
      GL.STATIC_DRAW)
  }

  val vertexNormalBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexNormalBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( jsonMesh.normals ),
      GL.STATIC_DRAW)
  }

  val vertexTexCoordBuffer = gl.createBuffer()
  init{
    gl.bindBuffer(GL.ARRAY_BUFFER, vertexTexCoordBuffer)
    gl.bufferData(GL.ARRAY_BUFFER,
      Float32Array( jsonMesh.texturecoords[0] ),
      GL.STATIC_DRAW)
  }    

  val blendIndicesBuffer = gl.createBuffer()
  val blendWeightsBuffer = gl.createBuffer()
  init {
    val blendIndices = Uint8Array(jsonMesh.vertices.size/3*4)
    val blendWeights = Float32Array(jsonMesh.vertices.size/3*4)
    for(i in 0 until jsonMesh.vertices.size/3*4) {
      blendWeights[i] = 0.0f
      blendIndices[i] = 0
    }
    val nWeightsPerVertex = Uint8Array(jsonMesh.vertices.size/3)
    for(i in 0 until jsonMesh.vertices.size) {
      nWeightsPerVertex[i] = 0
    }    

    jsonMesh.bones.forEachIndexed { iBone, bone -> 
      for(weight in bone.weights) {
        val iVertex = weight[0].toInt()
        val weights = weight[1]
        blendWeights[ iVertex*4 + nWeightsPerVertex[iVertex] ] = weights
        blendIndices[ iVertex*4 + nWeightsPerVertex[iVertex] ] = iBone.toByte()
        nWeightsPerVertex[iVertex]++
      }     
    }

    gl.bindBuffer(GL.ARRAY_BUFFER, blendIndicesBuffer)
    gl.bufferData(GL.ARRAY_BUFFER, blendIndices, GL.STATIC_DRAW)

    gl.bindBuffer(GL.ARRAY_BUFFER, blendWeightsBuffer)
    gl.bufferData(GL.ARRAY_BUFFER, blendWeights, GL.STATIC_DRAW)
  }

  val indexBuffer = gl.createBuffer()
  val indexCount = jsonMesh.faces.flatten().size
  init{
    val indexIterator = jsonMesh.faces.flatten().iterator()
    val indexArray = Array<Short>(indexCount) {indexIterator.next()}

    gl.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, indexBuffer)
    gl.bufferData(GL.ELEMENT_ARRAY_BUFFER,
      Uint16Array( indexArray ),
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
    
    gl.bindBuffer(GL.ARRAY_BUFFER, blendIndicesBuffer)
    gl.enableVertexAttribArray(3)
    gl.vertexAttribPointer(3,
      4, GL.UNSIGNED_BYTE, //< four integers
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )
    gl.bindBuffer(GL.ARRAY_BUFFER, blendWeightsBuffer)
    gl.enableVertexAttribArray(4)
    gl.vertexAttribPointer(4,
      4, GL.FLOAT, //< four floats
      false, //< do not normalize (make unit length)
      0, //< tightly packed
      0 //< data starts at array start
    )
 
    gl.bindVertexArray(null)
  }

  val nBones = jsonMesh.bones.size
  val rigging = Mat4Array(nBones)
  val boneNames = Array<String>(nBones) {
    val offsetMatrix = Mat4(*jsonMesh.bones[it].offsetmatrix.toFloatArray())
    offsetMatrix.transpose()
    rigging[it].set(offsetMatrix)
    jsonMesh.bones[it].name
  }

  override fun draw() {
    gl.bindVertexArray(inputLayout)
    gl.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, indexBuffer)

    //gl.drawElements(GL.TRIANGLES, indexCount, GL.UNSIGNED_SHORT, 0)
    gl.drawElementsInstanced(GL.TRIANGLES, indexCount, GL.UNSIGNED_SHORT, 0, nInstances)
  }
}

