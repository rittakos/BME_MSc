import org.w3c.dom.HTMLCanvasElement
import org.w3c.dom.HTMLDivElement
import org.w3c.dom.events.Event
import org.w3c.dom.events.KeyboardEvent
import org.w3c.dom.events.MouseEvent
import kotlin.browser.document
import kotlin.browser.window

class App(val canvas: HTMLCanvasElement, val overlay: HTMLDivElement) {

    val gl = (canvas.getContext("webgl2") ?: throw Error("Browser does not support WebGL2")) as WebGL2RenderingContext
    val scene = Scene(gl)

    init {
        resize()
    }

    fun resize() {
        canvas.width = canvas.clientWidth
        canvas.height = canvas.clientHeight
        scene.resize(gl, canvas)
    }

    val keysPressed = HashSet<String>()

    @Suppress("UNUSED_PARAMETER")
    fun registerEventHandlers() {
        document.onkeydown = { event: KeyboardEvent ->
            keysPressed.add(keyNames[event.keyCode])
        }

        document.onkeyup = { event: KeyboardEvent ->
            keysPressed.remove(keyNames[event.keyCode])
        }

        canvas.onmousedown = { event: MouseEvent ->
            scene.camera.mouseDown()
            event
        }

        canvas.onmousemove = { event: MouseEvent ->
            event.stopPropagation()
            scene.camera.mouseMove(event)
        }

        canvas.onmouseup = { event: MouseEvent ->
            scene.camera.mouseUp()
            event // This line is a placeholder for event handling code. It has no effect, but avoids the "unused parameter" warning.
        }

        canvas.onmouseout = { event: Event ->
            scene.camera.mouseUp()
            event // This line is a placeholder for event handling code. It has no effect, but avoids the "unused parameter" warning.
        }

        window.addEventListener("resize", { resize() })
        window.requestAnimationFrame { update() }
    }

    fun update() {
        scene.update(gl, keysPressed)
        window.requestAnimationFrame { update() }
    }
}

fun main() {
    val canvas = document.getElementById("canvas") as HTMLCanvasElement
    val overlay = document.getElementById("overlay") as HTMLDivElement
    overlay.innerHTML = """<font color="red">WebGL</font>"""

    try {
        val app = App(canvas, overlay)
        app.registerEventHandlers()
    } catch (e: Error) {
        console.error(e.message)
    }

}