using UnityEngine;

[ExecuteInEditMode]
[RequireComponent(typeof(Camera))]
public class LumQuantEffect : PostEffectsBase
{

    [Range(1, 50)] // allowed range in the inspector view
    public int levels = 8;

    void Start()
    {
        shader = Shader.Find("Hidden/NewImageEffectShader");
        CreateMaterial();
    }

    void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        if (CreateMaterial())
        {
            material.SetInt("levels", levels);
            Graphics.Blit(source, destination, material);
        }
        else
        {
            Graphics.Blit(source, destination);
        }
    }
}