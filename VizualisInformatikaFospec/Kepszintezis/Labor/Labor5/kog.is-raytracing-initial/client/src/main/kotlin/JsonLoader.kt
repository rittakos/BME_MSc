import org.w3c.xhr.XMLHttpRequest
import org.w3c.dom.events.*
import kotlinx.serialization.*
import kotlinx.serialization.json.*
import vision.gears.webglmath.Geometry

@Serializable
data class JsonMesh(
	val vertices : Array<Float>,
	val normals : Array<Float>,
	val texturecoords : Array<Array<Float>>,
	val faces : Array<Array<Short>>)

@Serializable
data class JsonModel(
	val meshes : Array<JsonMesh>)

class JsonLoader(){
  fun loadGeometries(gl : WebGL2RenderingContext,
      jsonModelFileUrl : String) : Array<Geometry> {
    val request = XMLHttpRequest()
    request.overrideMimeType("application/json")
    request.open("GET", jsonModelFileUrl, false)
    var geometries : Array<Geometry>? = null
    request.onloadend = { 
      val json = Json { ignoreUnknownKeys=true }
      val jsonModel = json.decodeFromString(
                       JsonModel.serializer(), request.responseText)
      geometries = jsonModel.meshes.map{ SubmeshGeometry(gl, it) }.toTypedArray()
      Unit
    }
    request.send()
    return geometries!!
  }
  fun loadMeshes(
      gl : WebGL2RenderingContext,
      jsonModelFileUrl : String,
      vararg materials : Material) : Array<Mesh>{
    val geometries = loadGeometries(gl, jsonModelFileUrl)
    return (materials zip geometries).map{(m, g) -> Mesh(m, g)}.toTypedArray()
  }
}