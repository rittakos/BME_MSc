import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.WebGLTexture
import vision.gears.webglmath.Texture

class RenderTargetTextureCube(
  gl : WebGL2RenderingContext,
  resolution : Int = 512
  ) : Texture {
  override val glTexture : WebGLTexture? = gl.createTexture()

  init {
    gl.bindTexture(GL.TEXTURE_CUBE_MAP, glTexture)
    for(i in 0 until 6) {
      gl.texImage2D(
        GL.TEXTURE_CUBE_MAP_POSITIVE_X+i,
        0, GL.RGBA,
        resolution, resolution, 0,
        GL.RGBA, GL.UNSIGNED_BYTE, null) 
    }
    gl.texParameteri(GL.TEXTURE_CUBE_MAP, GL.TEXTURE_MAG_FILTER, GL.LINEAR) 
    gl.texParameteri(GL.TEXTURE_CUBE_MAP, GL.TEXTURE_MIN_FILTER, GL.LINEAR) 
  }
}

