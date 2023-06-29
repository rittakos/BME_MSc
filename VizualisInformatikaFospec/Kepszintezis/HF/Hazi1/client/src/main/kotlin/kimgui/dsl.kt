import vision.gears.webglmath.*
import kotlin.reflect.KMutableProperty0
import org.khronos.webgl.WebGLTexture

object dsl {

    fun clicked(block: () -> Unit){
        if(ImGui.IsItemClicked()){
            block()
        }
    }

    fun hovered(flags : HoveredFlags = HoveredFlag.None.i, block: () -> Unit){
        if(ImGui.IsItemHovered(flags)){
            block()
        }
    }    

    fun tooltipText(text : String){
        if(ImGui.IsItemHovered(HoveredFlag.None.i)){
            ImGui.SetTooltip(text)
        }
    }    

    // Tables

    fun table(strId: String, columns: Int, flags: TableFlags = TableFlag.None.i, outerSize: Vec2 = Vec2(), innerWidth: Float = 0f, block: () -> Unit) {
        if (ImGui.BeginTable(strId, columns, flags, outerSize, innerWidth)) { // ~open
            block()
            ImGui.EndTable()
        }
    }

    fun row(block: () -> Unit){
        ImGui.TableNextRow()
        block()
    }

    fun column(block: () -> Unit){
        ImGui.TableNextColumn()
        block()

    }    

    // Windows

    fun window(name: String, open: ((Boolean)->Boolean)? = null, flags: WindowFlags = 0, block: () -> Unit) {
        if (ImGui.Begin(name, open, flags)) // ~open
            block()
        ImGui.End()
    }

    // Child Windows

    inline fun child(strId: String, size: Vec2 = Vec2(), border: Boolean = false, extraFlags: WindowFlags = 0, block: () -> Unit) {
        if (ImGui.BeginChild(strId, size, border, extraFlags)) // ~open
            block()
        ImGui.EndChild()
    }

    // Parameters stacks (shared)

    inline fun withFont(font: KDIM_Font = ImGui.defaultFont, block: () -> Unit) {
        ImGui.PushFont(font)
        block()
        ImGui.PopFont()
    }

    // ~private
    fun _push(idx: Col, col: Any) {
        if (col is Int)
            ImGui.PushStyleColor(idx.i, col)
        else
            ImGui.PushStyleColor(idx.i, col as Vec4)
    }

    inline fun withStyleColor(idx: Col, col: Any, block: () -> Unit) {
        _push(idx, col)
        block()
        ImGui.PopStyleColor()
    }

    inline fun withStyleColor(idx0: Col, col0: Any,
                              idx1: Col, col1: Any, block: () -> Unit) {
        _push(idx0, col0)
        _push(idx1, col1)
        block()
        ImGui.PopStyleColor(2)
    }

    inline fun withStyleColor(idx0: Col, col0: Any,
                              idx1: Col, col1: Any,
                              idx2: Col, col2: Any, block: () -> Unit) {
        _push(idx0, col0)
        _push(idx1, col1)
        _push(idx2, col2)
        block()
        ImGui.PopStyleColor(3)
    }

    inline fun withStyleColor(idx0: Col, col0: Any,
                              idx1: Col, col1: Any,
                              idx2: Col, col2: Any,
                              idx3: Col, col3: Any,
                              block: () -> Unit) {
        _push(idx0, col0)
        _push(idx1, col1)
        _push(idx2, col2)
        _push(idx3, col3)
        block()
        ImGui.PopStyleColor(4)
    }

    inline fun withStyleColor(idx0: Col, col0: Any,
                              idx1: Col, col1: Any,
                              idx2: Col, col2: Any,
                              idx3: Col, col3: Any,
                              idx4: Col, col4: Any, block: () -> Unit) {
        _push(idx0, col0)
        _push(idx1, col1)
        _push(idx2, col2)
        _push(idx3, col3)
        _push(idx4, col4)
        block()
        ImGui.PopStyleColor(5)
    }

    inline fun withStyleVar(idx: StyleVar, value: Any, block: () -> Unit) {
        ImGui.PushStyleVar(idx, value)
        block()
        ImGui.PopStyleVar()
    }

    // Parameters stacks (current window)

    inline fun withItemWidth(itemWidth: Int, block: () -> Unit) {
        ImGui.PushItemWidth(itemWidth)
        block()
        ImGui.PopItemWidth()
    }
    inline fun withItemWidth(itemWidth: Float, block: () -> Unit) {
        ImGui.PushItemWidth(itemWidth)
        block()
        ImGui.PopItemWidth()
    }

    inline fun withTextWrapPos(wrapPosX: Float = 0f, block: () -> Unit) {
        ImGui.PushTextWrapPos(wrapPosX)
        block()
        ImGui.PopTextWrapPos()
    }

    inline fun withAllowKeyboardFocus(allowKeyboardFocus: Boolean, block: () -> Unit) {
        ImGui.PushAllowKeyboardFocus(allowKeyboardFocus)
        block()
        ImGui.PopAllowKeyboardFocus()
    }

    inline fun <R> withButtonRepeat(repeat: Boolean, block: () -> R): R {
        ImGui.PushButtonRepeat(repeat)
        return block().also { ImGui.PopButtonRepeat() }
    }


    // Cursor / Layout

    inline fun indent(indentW: Float = 0f, block: () -> Unit) { // TODO indented?
        ImGui.Indent(indentW)
        block()
        ImGui.Unindent(indentW)
    }

    inline fun group(block: () -> Unit) {
        ImGui.BeginGroup()
        block()
        ImGui.EndGroup()
    }


    // ID stack/scopes

    inline fun withID(id: Int, block: () -> Unit) {
        ImGui.PushID(id)
        block()
        ImGui.PopID()
    }

    inline fun withID(id: String, block: () -> Unit) {
        ImGui.PushID(id)
        block()
        ImGui.PopID()
    }

    inline fun withID(id: Any, block: () -> Unit) {
        ImGui.PushID(id)
        block()
        ImGui.PopID()
    }


    // Widgets: Main

    inline fun button(label: String, sizeArg: Vec2 = Vec2(), block: () -> Unit) {
        if (ImGui.Button(label, sizeArg))
            block()
    }

    fun colorButton(label: String, col: Vec4 = Vec4(), block: () -> Unit) {
        if (ImGui.ColorButton(label, col))
            block()
    }

    inline fun smallButton(label: String, block: () -> Unit) {
        if (ImGui.SmallButton(label))
            block()
    }

    inline fun invisibleButton(strId: String, sizeArg: Vec2, block: () -> Unit) {
        if (ImGui.InvisibleButton(strId, sizeArg))
            block()
    }

    inline fun arrowButton(id: String, dir: Dir, block: () -> Unit) {
        if (ImGui.ArrowButton(id, dir))
            block()
    }

    inline fun imageButton(userTextureId: WebGLTexture, size: Vec2, uv0: Vec2 = Vec2(), uv1: Vec2 = Vec2(1f, 1f),
                           framePadding: Int = -1, bgCol: Vec4 = Vec4(), tintCol: Vec4 = Vec4(1f, 1f, 1f, 1f), block: () -> Unit) {
        if (ImGui.ImageButton(userTextureId, size, uv0, uv1, framePadding, bgCol, tintCol))
            block()
    }

    fun image(userTextureId: WebGLTexture, size: Vec2, uv0: Vec2 = Vec2(), uv1: Vec2 = Vec2(1f, 1f), tintCol: Vec4 = Vec4(1f, 1f, 1f, 1f)) {
        ImGui.Image(userTextureId, size, uv0, uv1, tintCol)
    }    

    fun checkbox(label: String, vPtr: (Boolean)->Boolean, block: () -> Unit) {
        if (ImGui.Checkbox(label, vPtr))
            block()
    }

    fun checkboxFlags(label: String, vPtr: (Int)->Int, flagsValue: Int, block: () -> Unit) {
        if (ImGui.CheckboxFlags(label, vPtr, flagsValue))
            block()
    }

    inline fun radioButton(label: String, active: Boolean, block: () -> Unit) {
        if (ImGui.RadioButton(label, active))
            block()
    }

    fun radioButton(label: String, v: (Int)->Int, vButton: Int, block: () -> Unit) {
        if (ImGui.RadioButton(label, v, vButton))
            block()
    }


    // Widgets: Combo Box


    inline fun useCombo(label: String, previewValue: String?, flags: ComboFlags = 0, block: () -> Unit) {
        if (ImGui.BeginCombo(label, previewValue, flags)) {
            block()
            ImGui.EndCombo()
        }
    }

    fun combo(label: String, currentItem: (Int)->Int, itemsSeparatedByZeros: String,
                     heightInItems: Int = -1, block: () -> Unit) {
        if (ImGui.Combo(label, currentItem, itemsSeparatedByZeros, heightInItems))
            block()
    }


    // Widgets: Trees

    inline fun treeNode(label: String, block: () -> Unit) {
        if (ImGui.TreeNode(label)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNode(strId: String, fmt: String, block: () -> Unit) {
        if (ImGui.TreeNode(strId, fmt)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNode(intPtr: Long, fmt: String, block: () -> Unit) {
        if (ImGui.TreeNode(intPtr, fmt)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNodeEx(strID: String, flags: TreeNodeFlags = 0, block: () -> Unit) {
        if(ImGui.TreeNodeEx(strID, flags)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNodeEx(strID: String, flags: TreeNodeFlags, fmt: String, vararg args: Any, block: () -> Unit) {
        if(ImGui.TreeNodeEx(strID, flags, fmt, args)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNodeEx(ptrID: Any, flags: TreeNodeFlags, fmt: String, vararg args: Any, block: () -> Unit) {
        if(ImGui.TreeNodeEx(ptrID, flags, fmt, args)) {
            block()
            ImGui.TreePop()
        }
    }

    inline fun treeNodeEx(intPtr: Long, flags: TreeNodeFlags, fmt: String, vararg args: Any, block: () -> Unit) {
        if(ImGui.TreeNodeEx(intPtr, flags, fmt, args)) {
            block()
            ImGui.TreePop()
        }
    }

//    inline fun treePushed(intPtr: Long?, block: () -> Unit) { TODO check me
//        treePush(intPtr)
//        try { block() } finally { treePop() }
//    }

    inline fun collapsingHeader(label: String, flags: TreeNodeFlags = 0, block: () -> Unit) {
        if (ImGui.CollapsingHeader(label, flags))
            block()
    }

    fun collapsingHeader(label: String, open: (Boolean)->Boolean, flags: TreeNodeFlags = 0, block: () -> Unit) {
        if (ImGui.CollapsingHeader(label, open, flags))
            block()
    }


    // Widgets: Selectables

    inline fun selectable(label: String, selected: Boolean = false, flags: Int = 0, sizeArg: Vec2 = Vec2(), block: () -> Unit) {
        if (ImGui.Selectable(label, selected, flags, sizeArg))
            block()
    }


    // Widgets: Menus

    inline fun mainMenuBar(block: () -> Unit) {
        if (ImGui.BeginMainMenuBar()) {
            block()
            ImGui.EndMainMenuBar()
        }
    }

    inline fun menuBar(block: () -> Unit) {
        if (ImGui.BeginMenuBar()) {
            block()
            ImGui.EndMenuBar()
        }
    }

    inline fun menu(label: String, enabled: Boolean = true, block: () -> Unit) {
        if (ImGui.BeginMenu(label, enabled)) {
            block()
            ImGui.EndMenu()
        }
    }

    inline fun menuItem(label: String, shortcut: String = "", selected: Boolean = false, enabled: Boolean = true, block: () -> Unit) {
        if (ImGui.MenuItem(label, shortcut, selected, enabled))
            block()
    }

    fun separator() {
        ImGui.Separator()
    }

    fun sameLine() {
        ImGui.SameLine()
    }


    // Tooltips

    inline fun tooltip(block: () -> Unit) {
        ImGui.BeginTooltip()
        block()
        ImGui.EndTooltip()
    }


    // Popups, Modals

    inline fun popup(strId: String, flags: WindowFlags = 0, block: () -> Unit) {
        if (ImGui.BeginPopup(strId, flags)) {
            block()
            ImGui.EndPopup()
        }
    }

    inline fun popupContextItem(strId: String = "", popupFlags: PopupFlags = PopupFlag.MouseButtonRight.i, block: () -> Unit) {
        if (ImGui.BeginPopupContextItem(strId, popupFlags)) {
            block()
            ImGui.EndPopup()
        }
    }

    inline fun popupContextWindow(strId: String = "", popupFlags: PopupFlags = PopupFlag.MouseButtonRight.i, block: () -> Unit) {
        if (ImGui.BeginPopupContextWindow(strId, popupFlags)) {
            block()
            ImGui.EndPopup()
        }
    }

    inline fun popupContextVoid(strId: String = "", popupFlags: PopupFlags = PopupFlag.MouseButtonRight.i, block: () -> Unit) {
        if (ImGui.BeginPopupContextVoid(strId, popupFlags)) {
            block()
            ImGui.EndPopup()
        }
    }

    fun popupModal(name: String, pOpen: ((Boolean)->Boolean)? = null, extraFlags: WindowFlags = 0, block: () -> Unit) {
        if (ImGui.BeginPopupModal(name, pOpen, extraFlags)) {
            block()
            ImGui.EndPopup()
        }
    }

    fun openPopup(id : String, popup_flags : PopupFlags = PopupFlag.None.i){
        ImGui.OpenPopup(id, popup_flags)
    }

    fun closeCurrentPopup(){
        ImGui.CloseCurrentPopup()
    }    

    // Tab Bars, Tabs

    inline fun tabBar(strId: String, flags: TabBarFlags = 0, block: () -> Unit) {
        if (ImGui.BeginTabBar(strId, flags)) {
            block()
            ImGui.EndTabBar()
        }
    }

    fun tabItem(label: String, pOpen: ((Boolean)->Boolean)? = null, flags: TabItemFlags = 0, block: () -> Unit) {
        if (ImGui.BeginTabItem(label, pOpen, flags)) {
            block()
            ImGui.EndTabItem()
        }
    }

    inline fun tabItem(label: String, pOpen: BooleanArray, ptr: Int, flags: TabItemFlags = 0, block: () -> Unit) {
        if (ImGui.BeginTabItem(label, pOpen, ptr, flags)) {
            block()
            ImGui.EndTabItem()
        }
    }

     fun progressBar(overlay : String, fraction : Float, size : Vec2 = Vec2()){
        ImGui.ProgressBar(fraction, size, overlay)
     }

    // Drag and Drop

    inline fun dragDropSource(flags: DragDropFlags = 0, block: () -> Unit) {
        if (ImGui.BeginDragDropSource(flags)) {
            block()
            ImGui.EndDragDropSource()
        }
    }

    inline fun dragDropTarget(block: () -> Unit) {
        if (ImGui.BeginDragDropTarget()) {
            block()
            ImGui.EndDragDropTarget()
        }
    }


    // Clipping

    inline fun withClipRect(clipRectMin: Vec2, clipRectMax: Vec2, intersectWithCurrentClipRect: Boolean, block: () -> Unit) {
        ImGui.PushClipRect(clipRectMin, clipRectMax, intersectWithCurrentClipRect)
        block()
        ImGui.PopClipRect()
    }


    // Miscellaneous Utilities

    inline fun childFrame(id: ID, size: Vec2, extraFlags: WindowFlags = 0, block: () -> Unit) {
        ImGui.BeginChildFrame(id, size, extraFlags)
        block()
        ImGui.EndChildFrame()
    }

    // listBox

    inline fun listBox(label: String, sizeArg: Vec2 = Vec2(), block: () -> Unit) {
        if (ImGui.ListBoxHeader(label, sizeArg)) {
            block()
            ImGui.ListBoxFooter()
        }
    }

    fun dragFloat(label: String, v : (Float)->Float, v_speed : Float = 1f, v_min : Float = 0f, v_max : Float = 0f, display_format : String = "%.3f", flags : SliderFlags = 0, block: () -> Unit) {
        if (ImGui.DragFloat(label, v, v_speed, v_min, v_max, display_format, flags)) {
            block()
        }
    }

    fun dragFloatRange(label: String, v_current_min : (Float)->Float, v_current_max : (Float)->Float, v_speed : Float = 1f, v_min : Float = 0f, v_max : Float = 0f, display_format : String = "%.3f", display_format_max : String? = null, flags : SliderFlags = 0, block: () -> Unit) {
        if (ImGui.DragFloatRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, display_format, display_format_max, flags)) {
            block()
        }
    }        

    fun slider(label : String, v : 
        (Int) -> Int
        , v_min : Int, v_max : Int, format : String = "%d", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.SliderInt(label, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun slider(label : String, v : 
        Array<Int>
        , v_min : Int, v_max : Int, format : String = "%d", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.SliderInt(label, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun slider(label : String, v : 
        IVec1
        , v_min : Int, v_max : Int, format : String = "%d", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.SliderInt(label, v, v_min, v_max, format, flags)){
            block()
        }
    }        

    fun slider(label : String, v : 
        (Float) -> Float
        , v_min : Float, v_max : Float, format : String = "%.3f", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.SliderFloat(label, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun slider2(label : String, v : Vec2, v_min : Float, v_max : Float , format : String = "%.3f", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.SliderFloat2(label, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun vslider(label : String, size : Vec2, v : 
        (Int) -> Int
        , v_min : Int, v_max : Int, format : String = "%d", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.VSliderInt(label, size, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun vslider(label : String, size : Vec2, v : 
        Array<Int>
        , v_min : Int, v_max : Int, format : String = "%d", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.VSliderInt(label, size, v, v_min, v_max, format, flags)){
            block()
        }
    }

    fun vslider(label : String, size : Vec2, v : 
        (Float) -> Float
        , v_min : Float, v_max : Float, format : String = "%.3f", flags : SliderFlags = 0, block: () -> Unit) {
        if(ImGui.VSliderFloat(label, size, v, v_min, v_max, format, flags)){
            block()
        }
    }        
    
    fun text(txt: String){
        ImGui.Text(txt)
    }

    fun textWrapped(txt: String){
        ImGui.TextWrapped(txt)
    }    

    // Focusscope TODO
}