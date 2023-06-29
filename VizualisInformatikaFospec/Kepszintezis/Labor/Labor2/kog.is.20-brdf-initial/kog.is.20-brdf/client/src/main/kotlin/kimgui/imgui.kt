//@file:JsModule("imgui")
//@file:JsNonModule

import org.w3c.dom.HTMLCanvasElement
import kotlin.js.Promise
import org.khronos.webgl.WebGLTexture
import vision.gears.webglmath.*
import kotlin.reflect.KMutableProperty0

external class KDIM_Fonts {
   fun AddFontDefault():Unit
}

external class KDIM_Font {
}

external class KDIM_DrawData {
}

external class KDIM_ImGui_Impl {
   fun Init(canvas : HTMLCanvasElement):Unit
   fun NewFrame(timeStamp : Double):Unit
   fun RenderDrawData( drawData : KDIM_DrawData):Unit

}

external class KDIM_Vec2 {
   var x : Float
   var y : Float
}

external class KDIM_IO {
   val Fonts : KDIM_Fonts
   val DisplaySize : KDIM_Vec2
   val MousePos : KDIM_Vec2   
   val WantCaptureMouse : Boolean
   val WantCaptureKeyboard : Boolean
}

external class KDIM_mallinfo {
   val uordblks : Int
}


external class KDIM_bind {
   fun mallinfo():KDIM_mallinfo
   val __EMSCRIPTEN_major__ : Int
   val __EMSCRIPTEN_minor__ : Int
   val __EMSCRIPTEN_tiny__ : Int
}

external class KDIM_ImGui {
   val defaultFont : KDIM_Font
   fun default():Promise<Unit>
   fun CHECKVERSION():Unit
   fun CreateContext():Unit
   fun StyleColorsDark():Unit   
   fun GetIO():KDIM_IO
   val bind:KDIM_bind
   fun NewFrame():Unit
   fun EndFrame():Unit
   fun Render():Unit
   fun GetDrawData() : KDIM_DrawData
   fun GetCursorScreenPos() : KDIM_Vec2
   fun SetCursorScreenPos(pos : Vec2)
   fun GetCursorPos() : KDIM_Vec2
   fun SetCursorPos(pos : Vec2)   

   fun ArrowButton(id: String, dir: Dir): Boolean
   fun Begin(name: String, pOpen: ((Boolean)->Boolean)? = definedExternally, flags_: WindowFlags = definedExternally): Boolean
   fun BeginChild(id: ID, sizeArg: Vec2 = definedExternally, border: Boolean = definedExternally, flags: WindowFlags = definedExternally): Boolean
   fun BeginChild(str_id: String, sizeArg: Vec2 = definedExternally, border: Boolean = definedExternally, flags: WindowFlags = definedExternally): Boolean   
   fun BeginChildFrame(id: ID, size: Vec2, extraFlags: WindowFlags = definedExternally): Boolean
   fun BeginCombo(label: String, previewValue: String?, flags_: ComboFlags = definedExternally): Boolean
   fun BeginDragDropSource(flag: DragDropFlag): Boolean
   fun BeginDragDropSource(flags: DragDropFlags = definedExternally): Boolean
   fun BeginDragDropTarget(): Boolean
   fun BeginGroup()
   fun BeginMainMenuBar(): Boolean
   fun BeginMenu(label: String, enabled: Boolean = definedExternally): Boolean
   fun BeginMenuBar(): Boolean
   fun BeginPopup(strId: String, flags_: WindowFlags = definedExternally): Boolean
   fun BeginPopupContextItem(strId: String = definedExternally, popupFlags: PopupFlags = definedExternally): Boolean
   fun BeginPopupContextVoid(strId: String = definedExternally, popupFlags: PopupFlags = definedExternally): Boolean
   fun BeginPopupContextWindow(strId: String = definedExternally, popupFlags: PopupFlags = definedExternally): Boolean
   fun BeginPopupModal(name: String, pOpen: BooleanArray, flags_: WindowFlags = definedExternally): Boolean
   fun BeginPopupModal(name: String, pOpen: ((Boolean)->Boolean)? = definedExternally, flags_: WindowFlags = definedExternally): Boolean
   fun BeginTabBar(strId: String, flags: TabBarFlags = definedExternally): Boolean
   fun BeginTabItem(label: String, pOpen: BooleanArray, index: Int, flags: TabItemFlags = definedExternally) : Boolean
   fun BeginTabItem(label: String, pOpen: ((Boolean)->Boolean)? = definedExternally, flags: TabItemFlags = definedExternally): Boolean
   fun BeginTable(strId: String, columns: Int, flags: TableFlags = definedExternally,
                   outerSize: Vec2 = definedExternally, innerWidth: Float = definedExternally): Boolean
   fun TableNextRow(row_flags : TableRowFlags = definedExternally, min_row_height : Float = definedExternally) : Boolean
   fun TableNextColumn() : Boolean
   fun BeginTooltip()
   fun Button(label: String, sizeArg: Vec2 = definedExternally): Boolean
   fun Checkbox(label: String, vPtr: (Boolean)->Boolean): Boolean
   fun CheckboxFlags(label: String, flagsPtr: (Int)->Int, flagsValue: Int): Boolean
   fun CloseCurrentPopup()   
   fun CollapsingHeader(label: String, flags: TreeNodeFlags = definedExternally): Boolean
   fun CollapsingHeader(label: String, visible: (Boolean)->Boolean?, flags_: TreeNodeFlags = definedExternally): Boolean
   fun ColorButton(label: String, col : Vec4 = definedExternally, flags: ButtonFlags = definedExternally, size: Vec2 = definedExternally): Boolean
   fun Combo(label: String, currentItemPtr: (Int)->Int, items: List<String>, popupMaxHeightInItem: Int = definedExternally): Boolean
   fun Combo(label: String, currentItem: (Int)->Int, itemsSeparatedByZeros: String, heightInItems: Int = definedExternally): Boolean
   fun DragFloat(label : String, v : (Float)->Float, v_speed : Float = definedExternally, v_min : Float = definedExternally, v_max : Float = definedExternally, display_format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun DragFloatRange2(label : String, v_current_min : (Float)->Float, v_current_max : (Float)->Float, v_speed : Float = definedExternally, v_min : Float = definedExternally, v_max : Float = definedExternally, display_format : String = definedExternally, display_format_max : String? = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun End()
   fun EndChild()
   fun EndChildFrame()
   fun EndCombo()
   fun EndDragDropSource()
   fun EndDragDropTarget()
   fun EndGroup()
   fun EndMainMenuBar()
   fun EndMenu()
   fun EndMenuBar()
   fun EndPopup()
   fun EndTabBar()
   fun EndTabItem()
   fun EndTable()
   fun EndTooltip()
   fun GetID(str_id : String) : Any 
   fun GetWindowSize() : KDIM_Vec2
   fun GetWindowPos() : KDIM_Vec2     
   fun GetMouseCursor() : MouseCursor 
   fun Image(userTextureId: WebGLTexture, size: Vec2, uv0: Vec2 = definedExternally, uv1: Vec2 = definedExternally, tintCol: Vec4 = definedExternally)
   fun ImageButton(userTextureId: WebGLTexture, size: Vec2, uv0: Vec2 = definedExternally, uv1: Vec2 = definedExternally, framePadding: Int = definedExternally,
                    bgCol: Vec4 = definedExternally, tintCol: Vec4 = definedExternally): Boolean
   fun Indent(indentW: Float)
   fun InvisibleButton(strId: String, sizeArg: Vec2, flags: ButtonFlags = definedExternally): Boolean
   fun IsItemClicked(mouse_button : MouseButton = definedExternally) : Boolean
   fun IsItemHovered(flags : HoveredFlags = definedExternally) : Boolean   
   fun IsPopupOpen(str_id : String, flags : PopupFlags = definedExternally) : Boolean
   fun ListBoxFooter()
   fun ListBoxHeader(label: String, itemsCount: Int, heightInItems_: Int = definedExternally): Boolean
   fun ListBoxHeader(label: String, sizeArg: Vec2): Boolean
   fun MenuItem(label: String, shortcut: String = definedExternally, selected: Boolean = definedExternally, enabled: Boolean = definedExternally): Boolean
   fun MenuItem(label: String, shortcut: String = definedExternally, pSelected: BooleanArray?, enabled: Boolean = definedExternally): Boolean
   fun MenuItem(label: String, shortcut: String = definedExternally, selected: (Boolean)->Boolean?, enabled: Boolean = definedExternally): Boolean   
   fun OpenPopup(strId: String, flags_: PopupFlags = definedExternally)
   fun PlotHistogram(label : String,
      data : Array<Float>,
      values_count : Int,
      values_offset : Float,
      overlay_text : String,
      scale_min : Float,
      scale_max : Float,
      graph_size : Vec2,
      stride : Int )
   fun PopAllowKeyboardFocus()
   fun PopButtonRepeat()
   fun PopClipRect()
   fun PopFont()
   fun PopID()
   fun PopItemWidth()
   fun PopStyleColor(count: Int = definedExternally)
   fun PopStyleVar(count: Int = definedExternally)
   fun PopTextWrapPos()
   fun ProgressBar(fraction : Float, size_arg : Vec2 = definedExternally, overlay : String = definedExternally)
   fun PushAllowKeyboardFocus(allowKeyboardFocus: Boolean)
   fun PushButtonRepeat(repeat: Boolean)
   fun PushClipRect(clipRectMin: Vec2, clipRectMax: Vec2, intersectWithCurrentClipRect: Boolean)
   fun PushFont(font: KDIM_Font = definedExternally)
   fun PushID(id : Any)
   fun PushItemWidth(itemWidth: Int)
   fun PushItemWidth(itemWidth: Float)
   fun PushStyleColor(idx: Int, col: Int)
   fun PushStyleColor(idx: Int, col: Vec4)
   fun PushStyleVar(idx: StyleVar, value: Any)
   fun PushTextWrapPos(wrapLocalPosX: Float = definedExternally)
   fun RadioButton(label: String, v: Boolean): Boolean   
   fun RadioButton(label: String, v: (Int)->Int, vButton: Int): Boolean
   fun SameLine(offset_from_start_x : Float = definedExternally, spacing : Float = definedExternally)
   fun NewLine()
   fun Selectable(label: String, selected: Boolean = definedExternally, flags: Int = definedExternally, sizeArg: Vec2 = definedExternally) : Boolean
   fun SmallButton(label: String): Boolean
   fun Separator(): Unit
   fun SetItemAllowOverlap()   
   fun SetNextItemWidth(width : Float)   
   fun SetNextWindowPos(pos : Vec2, cond : CondFlags = definedExternally, pivot : Vec2 = definedExternally)
   fun SetNextWindowSize(size : Vec2, cond : CondFlags = definedExternally)   
   fun SetTooltip(text : String)
   fun SliderInt(label : String, v : 
      IVec1
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun SliderInt(label : String, v : 
      (Int) -> Int
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun SliderInt(label : String, v : 
      Array<Int>
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun SliderFloat(label : String, v : 
      (Float) -> Float
      , v_min : Float, v_max : Float, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   //fun SliderFloat2(label : String, v : (Vec2) -> Vec2, v_min : Float, v_max : Float, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun SliderFloat2(label : String, v : Vec2, v_min : Float, v_max : Float, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun VSliderInt(label : String, v : 
      IVec1
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun VSliderInt(label : String, size : Vec2, v : 
      (Int) -> Int
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun VSliderInt(label : String, size : Vec2, v : 
      Array<Int>
      , v_min : Int, v_max : Int, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean
   fun VSliderFloat(label : String, size : Vec2, v : 
      (Float) -> Float
      , v_min : Float, v_max : Float, format : String = definedExternally, flags : SliderFlags = definedExternally) : Boolean

   fun Text(txt: String): Unit
   fun TextWrapped(txt: String): Unit   
   fun TreeNode(ptrID: Any): Boolean
   fun TreeNode(ptrID: Any, fmt: String, vararg args: Any): Boolean
   fun TreeNodeEx(ptrID: Any, flags: TreeNodeFlags): Boolean
   fun TreeNodeEx(ptrID: Any, flags: TreeNodeFlags, fmt: String, vararg args: Any): Boolean
   fun TreePop()
   fun Unindent(indentW: Float)
//import imgui.font.Font
}

external val ImGui : KDIM_ImGui
external val ImGui_Impl : KDIM_ImGui_Impl
