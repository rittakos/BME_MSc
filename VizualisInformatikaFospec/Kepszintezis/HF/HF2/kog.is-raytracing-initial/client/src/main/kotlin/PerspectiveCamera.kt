import org.w3c.dom.events.MouseEvent
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3
import kotlin.math.tan

class PerspectiveCamera(vararg programs: Program) : UniformProvider("camera") {

    val position = Vec3(0.0f, 0.0f, 0.0f)
    var roll = 0.0f
    var pitch = 0.0f
    var yaw = 0.0f

    var fov = 1.0f
    var aspect = 1.0f
    var nearPlane = 0.1f
    var farPlane = 1000.0f

    var ahead = Vec3(0.0f, 0.0f, -1.0f)
    var right = Vec3(1.0f, 0.0f, 0.0f)
    var up = Vec3(0.0f, 1.0f, 0.0f)

    var speed = 2f
    var isDragging = false
    val mouseDelta = Vec2(0.0f, 0.0f)

    val rotationMatrix = Mat4()
    val viewProjMatrix = Mat4()
    val rayDirMatrix = Mat4()

    companion object {
        val worldUp = Vec3(0.0f, 1.0f, 0.0f)
    }

    init {
        update()
        register("rayDirMatrix", rayDirMatrix)
        register("position", position)
        addComponentsAndGatherUniforms(*programs)
    }

    fun update() {
        rotationMatrix.set().rotate(roll).rotate(pitch, 1.0f, 0.0f, 0.0f).rotate(yaw, 0.0f, 1.0f, 0.0f)
        viewProjMatrix.set(rotationMatrix).translate(position).invert()

        val yScale = 1.0f / tan(fov * 0.5f)
        val xScale = yScale / aspect
        val f = farPlane
        val n = nearPlane
        viewProjMatrix *= Mat4(
                xScale, 0.0f, 0.0f, 0.0f,
                0.0f, yScale, 0.0f, 0.0f,
                0.0f, 0.0f, (n + f) / (n - f), -1.0f,
                0.0f, 0.0f, 2 * n * f / (n - f), 0.0f)

        rayDirMatrix.set().translate(position)
        rayDirMatrix *= viewProjMatrix
        rayDirMatrix.invert()
    }

    fun setAspectRatio(ar: Float) {
        aspect = ar
        update()
    }

    fun place(to: Vec3) = position.set(to)

    fun move(dt: Float, keysPressed: Set<String>) {
        if (isDragging) {
            yaw -= mouseDelta.x * 0.002f
            pitch -= mouseDelta.y * 0.002f
            if (pitch > 3.14f / 2.0f) {
                pitch = 3.14f / 2.0f
            }
            if (pitch < -3.14f / 2.0f) {
                pitch = -3.14f / 2.0f
            }
            mouseDelta.set()
        }
        if ("W" in keysPressed) {
            position += ahead * (speed * dt)
        }
        if ("S" in keysPressed) {
            position -= ahead * (speed * dt)
        }
        if ("D" in keysPressed) {
            position += right * (speed * dt)
        }
        if ("A" in keysPressed) {
            position -= right * (speed * dt)
        }
        if ("E" in keysPressed) {
            position += up * (speed * dt)
        }
        if ("Q" in keysPressed) {
            position -= up * (speed * dt)
        }

        update()
        ahead = (Vec3(0.0f, 0.0f, -1.0f).xyz0 * rotationMatrix).xyz
        right = (Vec3(1.0f, 0.0f, 0.0f).xyz0 * rotationMatrix).xyz
        up = (Vec3(0.0f, 1.0f, 0.0f).xyz0 * rotationMatrix).xyz
    }

    fun mouseDown() {
        isDragging = true
        mouseDelta.set()
    }

    fun mouseMove(event: MouseEvent) {
        mouseDelta.x += event.asDynamic().movementX as Float
        mouseDelta.y += event.asDynamic().movementY as Float
        event.preventDefault()
    }

    fun mouseUp() {
        isDragging = false
    }
}