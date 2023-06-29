import org.w3c.xhr.XMLHttpRequest
import org.w3c.dom.events.*
import kotlinx.serialization.*
import kotlinx.serialization.json.*
import vision.gears.webglmath.Geometry

@Serializable
data class JsonMesh(
	val vertices : Array<Float>,
	val normals : Array<Float>,
  val tangents : Array<Float>,
  val bitangents : Array<Float>,    
	val texturecoords : Array<Array<Float>>,
	val faces : Array<Array<Short>>)

@Serializable
data class JsonModel(
	val meshes : Array<JsonMesh>)

@Serializable
data class JsonBone(
  val name : String,
  val offsetmatrix : Array<Float>,
  val weights : Array<Array<Float>>)

@Serializable
data class JsonRiggedMesh(
  val vertices : Array<Float>,
  val normals : Array<Float>,
  val texturecoords : Array<Array<Float>>,
  val faces : Array<Array<Short>>,
  val bones : Array<JsonBone>)

@Serializable
data class JsonRiggedModel(
  val meshes : Array<JsonRiggedMesh>)

class JsonLoader(){
  fun loadGeometries(gl : WebGL2RenderingContext,
      jsonModelFileUrl : String) : List<Geometry> {
    val request = XMLHttpRequest()
    request.overrideMimeType("application/json")
    request.open("GET", jsonModelFileUrl, false)
    var geometries : List<Geometry>? = null
    request.onloadend = { 
      val json = Json { ignoreUnknownKeys=true }
      val jsonModel = json.decodeFromString(
                       JsonModel.serializer(), request.responseText)
      geometries = jsonModel.meshes.map{ SubmeshGeometry(gl, it) }
      Unit
    }
    request.send()
    return geometries ?: throw Error("Geometries never loaded.")
  }
  fun loadMeshes(
      gl : WebGL2RenderingContext,
      jsonModelFileUrl : String,
      vararg materials : Material) : Array<Mesh>{
    val geometries = loadGeometries(gl, jsonModelFileUrl)
    return (materials zip geometries).map{(m, g) -> Mesh(m, g)}.toTypedArray()
  }
/*  fun loadRiggedGeometries(gl : WebGL2RenderingContext,
      jsonModelFileUrl : String) : List<RiggedGeometry> {
    val request = XMLHttpRequest()
    request.overrideMimeType("application/json")
    request.open("GET", jsonModelFileUrl, false)
    var geometries : List<RiggedGeometry>? = null
    request.onloadend = { 
      val json = Json { ignoreUnknownKeys=true }
      val jsonModel = json.decodeFromString(JsonRiggedModel.serializer(), request.responseText)
      geometries = jsonModel.meshes.map{ RiggedGeometry(gl, it) }
      Unit
    }
    request.send()
    return geometries ?: throw Error("Geometries never loaded.")
  }
  fun loadRiggedMeshes(
      gl : WebGL2RenderingContext,
      jsonModelFileUrl : String,
      vararg materials : Material) : Array<Mesh>{
    val geometries = loadRiggedGeometries(gl, jsonModelFileUrl)
    return (materials zip geometries).map{(m, g) -> Mesh(m, g)}.toTypedArray()
  }    */
}