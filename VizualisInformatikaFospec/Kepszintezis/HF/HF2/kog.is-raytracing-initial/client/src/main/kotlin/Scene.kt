import org.w3c.dom.HTMLCanvasElement
import vision.gears.webglmath.Sampler3D
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import kotlin.js.Date
import kotlin.math.PI
import kotlin.math.cos
import kotlin.math.sin
import org.khronos.webgl.WebGLRenderingContext as GL

class Scene(
        val gl: WebGL2RenderingContext) : UniformProvider("scene") {

    val vsQuad = Shader(gl, GL.VERTEX_SHADER, "shaders/quad-vs.glsl")
    val fsTrace = Shader(gl, GL.FRAGMENT_SHADER, "shaders/trace-fs.glsl")
    val traceProgram = Program(gl, vsQuad, fsTrace, Program.PNT)
    val quadGeometry = TexturedQuadGeometry(gl)

    val volumeTexture = Texture3D(gl, "media/brain-at_4096.jpg")
    val volume = Sampler3D()
    val lightPos = Vec3(-2f, -2f, -2f)
    val mode = Vec3()
    var keysPressedBefore = setOf<String>()

    var timeAtLastFrame = Date().getTime().toFloat()

    val camera = PerspectiveCamera(*Program.all)

    init {
        camera.place(Vec3(0.5f, 0.5f, 4.5f))
        register("volume", volume)
        register("lightPos", lightPos)
        register("mode", mode)
        volume.glTextures[0] = volumeTexture.glTexture
        addComponentsAndGatherUniforms(*Program.all)
    }

    fun resize(gl: WebGL2RenderingContext, canvas: HTMLCanvasElement) {
        gl.viewport(0, 0, canvas.width, canvas.height)
        camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
    }

    @Suppress("UNUSED_PARAMETER")
    fun update(gl: WebGL2RenderingContext, keysPressed: Set<String>) {
        if ("M" in keysPressed && "M" !in keysPressedBefore)
            mode.x++
        if ("B" in keysPressed && "B" !in keysPressedBefore)
            mode.y++

        val now = Date().getTime().toFloat()
        lightPos.x = 0.5f + 2 * sin(now * (1f / 1000 * 2 * PI.toFloat() / 2))
        lightPos.z = 0.5f + 2 * cos(now * (1f / 1000 * 2 * PI.toFloat() / 2))
        val dt = (now - timeAtLastFrame) / 1000.0f
        timeAtLastFrame = now
        camera.move(dt, keysPressed)

        // clear the screen
        gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)
        gl.clearDepth(1.0f)
        gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)

        traceProgram.draw(this, camera)
        quadGeometry.draw()

        keysPressedBefore = keysPressed.toSet()
    }
}
