using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class PostEffectsBase : MonoBehaviour
{
    public Shader shader = null;
    protected Material material = null;

    // CreateMaterial: következő fólia

    protected bool CreateMaterial()
    {
        if (!SystemInfo.supportsImageEffects)
        {
            Debug.LogWarning("Image Effects are not supported on the current platform in " + ToString());
            enabled = false;
            return false;
        }
        if (shader == null)
        {
            Debug.LogWarning("No shader is set in " + ToString());
            enabled = false;
            return false;
        }
        if (!shader.isSupported)
        {
            Debug.LogWarning("Unsupported shader in " + ToString());
            enabled = false;
            return false;
        }
        if (material != null && material.shader == shader) return true;
        material = new Material(shader);
        material.hideFlags = HideFlags.DontSave;
        return material != null;
    }
}

