using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
[RequireComponent(typeof(Camera))]
public class ColorCorrectionEffect : PostEffectsBase
{
    [Range(0.0f, 1.0f)]
    public float hueShift = 0.0f;
    [Range(0.0f, 3.0f)]
    public float saturationScaler = 1.0f;
    [Range(0.0f, 3.0f)]
    public float brightnessScaler = 1.0f;
    public bool attenuateSaturation = true;
    public bool attenuateBrightness = true;
    public Vector2 attenuationCenter = new Vector2(0.5f, 0.5f);
    [Range(0.0f, 1.0f)]
    public float attenuationRadius = 0.3f;
    public Transform followObject;

    void Start()
    {
        shader = Shader.Find("Custom/ColorCorrectionShader");
        CreateMaterial();
    }


    void Update()
    {
        if (followObject != null)
        {
            Vector3 screenPoint =
                         GetComponent<Camera>().WorldToScreenPoint(followObject.position);
            attenuationCenter = new Vector2(
                 screenPoint.x / Screen.width,
                 screenPoint.y / Screen.height
            );
        }
    }

    void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        if (CreateMaterial())
        {
            material.SetFloat("hueShift", hueShift);
            material.SetFloat("saturationScaler", saturationScaler);
            material.SetFloat("brightnessScaler", brightnessScaler);
            material.SetVector("attenuationCenter", attenuationCenter);
            material.SetFloat("attenuationRadius", attenuationRadius);
            if (attenuateSaturation) material.EnableKeyword("ATTENUATE_SATURATION");
            else material.DisableKeyword("ATTENUATE_SATURATION");
            if (attenuateBrightness) material.EnableKeyword("ATTENUATE_BRIGHTNESS");
            else material.DisableKeyword("ATTENUATE_BRIGHTNESS");

            Graphics.Blit(source, destination, material);
        }
        else
        {
            Graphics.Blit(source, destination);
        }
    }

}