using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AutoOff : MonoBehaviour
{
    Light light;
    float baseIntensity;
    // Start is called before the first frame update
    void Start()
    {
        light = GetComponent<Light>();
        baseIntensity = light.intensity;
    }

    // Update is called once per frame
    void Update()
    {
        float intensityMultiplier = transform.position.y;
        if (intensityMultiplier < 0.0f)
            intensityMultiplier = 0.0f;
        if (intensityMultiplier > 1.0f)
            intensityMultiplier = 1.0f;

        light.intensity = baseIntensity * intensityMultiplier;
        //if (transform.position.y < 0.0f && light.enabled)
        //    light.enabled = false;
        //if (transform.position.y > 0.0f && !light.enabled)
        //    light.enabled = true;
    }
}
