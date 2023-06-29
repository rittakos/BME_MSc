import kotlinx.browser.document
import kotlinx.browser.window
import org.w3c.dom.HTMLDivElement
import org.w3c.dom.HTMLCanvasElement
import org.w3c.dom.events.*
import org.khronos.webgl.Uint32Array
import org.w3c.dom.Window

class App(val canvas : HTMLCanvasElement, val overlay : HTMLDivElement) {
  
  val gl = (canvas.getContext("webgl2", object{val antialias = false; val alpha = false}) ?: throw Error("Browser does not support WebGL2")) as WebGL2RenderingContext
  init {
    gl.getExtension("EXT_color_buffer_float") ?: throw Error("Browser does not support extension EXT_color_buffer_float")
  }
  val scene = Scene(gl, overlay, canvas)
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
      if(!ImGui.GetIO().WantCaptureMouse){
        scene.camera.mouseDown()
      }
      undefined
    }

    canvas.onmousemove = { 
      event : MouseEvent ->
      if(!ImGui.GetIO().WantCaptureMouse){
        scene.camera.mouseMove(event)
      }
      event.stopPropagation()
    }

    canvas.onmouseup = { 
      event : MouseEvent ->
      if(!ImGui.GetIO().WantCaptureMouse){
        scene.camera.mouseUp()
        canvas.focus()        
      }
      event // This line is a placeholder for event handling code. It has no effect, but avoids the "unused parameter" warning.
    }

    canvas.onmouseout = { 
      event : MouseEvent ->
      if(!ImGui.GetIO().WantCaptureMouse){
        scene.camera.mouseUp()
        canvas.focus()
      }
      event // This line is a placeholder for event handling code. It has no effect, but avoids the "unused parameter" warning.
    }

    window.onresize = { resize() }
    window.requestAnimationFrame {
      timeStamp : Double ->
        update(timeStamp)
    }
  }  

  fun update(timeStamp : Double) {
    scene.update(gl, keysPressed, timeStamp)
    window.requestAnimationFrame {
      timeStamp : Double ->
      update(timeStamp)
    }
  }
}

external object crypto {
  fun getRandomValues(array : Uint32Array)
}

fun main() {
  val canvas = document.getElementById("canvas") as HTMLCanvasElement
  val overlay = document.getElementById("overlay") as HTMLDivElement
  overlay.innerHTML = """<font color="red">WebGL</font>"""

  ImGui.default().then {
    var EMSCRIPTEN_VERSION = "${ImGui.bind.__EMSCRIPTEN_major__}.${ImGui.bind.__EMSCRIPTEN_minor__}.${ImGui.bind.__EMSCRIPTEN_tiny__}"
    console.log("Emscripten Version", EMSCRIPTEN_VERSION);
    console.log("Total allocated space (uordblks) @ _init:", ImGui.bind.mallinfo().uordblks);

    ImGui.CHECKVERSION()
    ImGui.CreateContext()
    val io = ImGui.GetIO()
    ImGui.StyleColorsDark()
    io.Fonts.AddFontDefault()
    ImGui_Impl.Init(canvas)

    try{
      val app = App(canvas, overlay)
      app.registerEventHandlers()
    } catch(e : Error) {
      console.error(e.message)
    }
  }
}