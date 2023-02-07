using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeLightColor : MonoBehaviour
{
    Color colorNoon = new Color(1.0f, 1.0f, 1.0f);
    Color colorDawn = new Color(0.6f, 0.56f, 0.34f);
    Color colorNight = new Color(0.0f, 0.0f, 0.0f);
    Light light;
    // Start is called before the first frame update
    void Start()
    {
        light = GetComponent<Light>();
    }

    // Update is called once per frame
    void Update()
    {
        Color lightColor;
        float cutoffHeight = 3.0f;
        float sunHeight = transform.position.y;
        if (sunHeight >= 0.0f)
        {
            float h = sunHeight / cutoffHeight;
            if (h > 1.0f) h = 1.0f;
            lightColor = h * colorNoon + (1.0f - h) * colorDawn;
        }
        else
        {
            float h = -sunHeight / cutoffHeight;
            if (h > 1.0f) h = 1.0f;
            lightColor = h * colorNight + (1.0f - h) * colorDawn;
        }
        light.color = lightColor;
    }
}
