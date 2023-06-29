package vision.gears.webglmath

import org.khronos.webgl.Float32Array
import org.khronos.webgl.Int32Array
import org.khronos.webgl.get
import org.khronos.webgl.set
import org.khronos.webgl.WebGLRenderingContext
import org.khronos.webgl.WebGLUniformLocation
import org.khronos.webgl.WebGLTexture
import kotlin.reflect.KProperty

interface Texture {
	abstract val glTexture : WebGLTexture?
}

interface Uniform {
	fun set(other: Uniform) : Uniform
	fun set(vararg values : Float) : Uniform
	fun set(firstValue : Int, vararg values : Int) : Uniform
	fun set(firstTexture : Texture, vararg moreTextures : Texture)
	fun getStorageSize() : Int
	infix fun gets(other : Uniform){
		set(other)
	}

	fun commit(gl : WebGLRenderingContext, uniformLocation : WebGLUniformLocation, samplerIndex : Int = 0)
}

interface UniformFloat : Uniform {
	abstract val storage : Float32Array

	override fun getStorageSize() : Int{
		return storage.length
	}

	override fun set(other: Uniform) : Uniform {
		if(other is UniformFloat){
			for(i : Int in 0 until storage.length) {
	    		storage[i] = if(i < other.storage.length) other.storage[i] else 0.0f
	    }
    } else {
			throw Error("Cannot set a uniform of floats from a non-float uniform.")
    }
    return this
	}

	override fun set(firstValue : Int, vararg values : Int) : Uniform {
		throw Error("Cannot set int values to a float uniform.")
	}	

	override fun set(firstTexture : Texture, vararg moreTextures : Texture){
		throw Error("Cannot set a texture to a non-sampler uniform.")
	}

}

interface UniformInt : Uniform {
	abstract val storage : Int32Array

	override fun getStorageSize() : Int{
		return storage.length
	}

	override fun set(other: Uniform) : Uniform {
		if(other is UniformInt){
			for(i : Int in 0 until storage.length) {
	    		storage[i] = if(i < other.storage.length) other.storage[i] else 0
	    }
    } else {
			throw Error("Cannot set a uniform of ints from a non-int uniform.")
    }
    return this
	}

	override fun set(vararg values : Float) : Uniform {
		if(values.size == 0){
			for(i : Int in 0 until storage.length) {
	    		storage[i] = 0
	    }			
		} else {
			throw Error("Cannot set float values to an int uniform.")
		}
		return this
	}	

	override fun set(firstTexture : Texture, vararg moreTextures : Texture){
		throw Error("Cannot set a texture to a non-sampler uniform.")
	}
}

interface UniformSampler : Uniform {
	abstract val storage : Int32Array
	abstract val glTextures : Array<WebGLTexture?>

	override fun getStorageSize() : Int{
		return storage.length
	}

	override fun set(other: Uniform) : Uniform {
		if(other is UniformSampler){
			for(i : Int in 0 until storage.length) {
	    		storage[i] = if(i < other.storage.length) other.storage[i] else 0
	    		glTextures[i] = other.glTextures.getOrNull(i)
	    }
    } else {
			throw Error("Cannot set a uniform of textures from a non-texture uniform.")
    }
    return this
	}

	override fun set(firstTexture : Texture, vararg moreTextures : Texture){
		glTextures[0] = firstTexture.glTexture
		for(i : Int in 0 until storage.length) {
			glTextures[i+1] = moreTextures.getOrNull(i)?.glTexture
		}
	}

	override fun set(vararg values : Float) : Uniform {
		if(values.size == 0){
			throw Error("Cannot set no value to a texture uniform.")
		} else {
			throw Error("Cannot set float values to a texture uniform.")
		}
	}

	override fun set(firstValue : Int, vararg values : Int) : Uniform {
		throw Error("Cannot set int values to a texture uniform.")
	}	
}

