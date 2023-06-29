import kotlin.browser.document
import kotlin.browser.window
import org.w3c.dom.HTMLDivElement
import org.w3c.dom.HTMLCanvasElement
import org.w3c.dom.events.*
import org.khronos.webgl.Uint32Array
import org.w3c.dom.Window

class App(val canvas : HTMLCanvasElement, val overlay : HTMLDivElement) {
  
  val gl = (canvas.getContext("webgl2", object{val alpha = false}) ?: throw Error("Browser does not support WebGL2")) as WebGL2RenderingContext
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
    document.onkeydown =  { 
      event : KeyboardEvent ->
      keysPressed.add( keyNames[event.keyCode] )
    }

    document.onkeyup = { 
      event : KeyboardEvent ->
      keysPressed.remove( keyNames[event.keyCode] )
    }

    canvas.onmousedown = { 
      event : MouseEvent ->
      scene.camera.mouseDown()
      undefined
    }

    canvas.onmousemove = { 
      event : MouseEvent ->
      scene.camera.mouseMove(event)
      event.stopPropagation()
    }

    canvas.onmouseup = { 
      event : Event ->
      scene.camera.mouseUp()
      event // This line is a placeholder for event handling code. It has no effect, but avoids the "unused parameter" warning.
    }

    canvas.onmouseout = { 
      event : Event ->
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

external object crypto {
  fun getRandomValues(array : Uint32Array)
}

fun main() {
  val canvas = document.getElementById("canvas") as HTMLCanvasElement
  val overlay = document.getElementById("overlay") as HTMLDivElement
  overlay.innerHTML = """<font color="red">WebGL</font>"""

  try{
    val app = App(canvas, overlay)
    app.registerEventHandlers()
  } catch(e : Error) {
    console.error(e.message)
  }
}