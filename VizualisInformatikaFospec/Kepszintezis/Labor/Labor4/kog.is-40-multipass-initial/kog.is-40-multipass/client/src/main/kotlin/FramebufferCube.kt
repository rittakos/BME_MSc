import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.WebGLTexture
import org.khronos.webgl.WebGLFramebuffer

class FramebufferCube(
  gl : WebGL2RenderingContext,
  targetCount : Int = 1,
  val resolution : Int = 512  
  ) {

  val glFramebuffers = Array<WebGLFramebuffer?>(6) { gl.createFramebuffer() }
  val targets = Array<RenderTargetTextureCube>(targetCount) { 
    RenderTargetTextureCube(gl, resolution)
  }
  val depthBuffer = gl.createRenderbuffer()
  init {
    gl.bindRenderbuffer(GL.RENDERBUFFER, depthBuffer)
    gl.renderbufferStorage(GL.RENDERBUFFER, GL.DEPTH_COMPONENT16, resolution, resolution)

    for(i in 0 until 6){
      gl.bindFramebuffer(GL.FRAMEBUFFER, glFramebuffers[i])
      gl.drawBuffers(IntArray(targetCount){GL.COLOR_ATTACHMENT0 + it})
      targets.forEachIndexed { j, target ->
        gl.framebufferTexture2D(GL.FRAMEBUFFER, GL.COLOR_ATTACHMENT0 + j,
         GL.TEXTURE_CUBE_MAP_POSITIVE_X+i, target.glTexture, 0)
      }
      gl.framebufferRenderbuffer(GL.FRAMEBUFFER, GL.DEPTH_ATTACHMENT, GL.RENDERBUFFER, depthBuffer)
      gl.bindFramebuffer(GL.FRAMEBUFFER, null)
    }
  }

  fun bind(gl : WebGL2RenderingContext, face : Int){
    gl.bindFramebuffer(GL.FRAMEBUFFER, glFramebuffers[face])
    gl.viewport(0, 0, resolution, resolution)
  }
}
