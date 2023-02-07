using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
[RequireComponent(typeof(Camera))]
public class ConvolutionEffect : PostEffectsBase
{

    void Start()
    {
        shader = Shader.Find("Custom/Convolution");
        CreateMaterial();
    }

    void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        if (CreateMaterial())
        {
            Graphics.Blit(source, destination, material);
        }
        else
        {
            Graphics.Blit(source, destination);
        }
    }
}