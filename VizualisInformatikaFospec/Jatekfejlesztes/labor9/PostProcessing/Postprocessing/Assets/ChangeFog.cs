using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeFog : MonoBehaviour
{
    Color fogNoon = new Color(0.63f,0.68f,0.66f);
    Color fogDawn = new Color(0.6f, 0.56f, 0.34f);
    Color fogNight = new Color(0.0f, 0.0f, 0.0f);
    float fogDistanceNoon = 1000.0f;
    float fogDistanceNight = 100.0f;
    float fogDistanceDawn = 750.0f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Color fogColor;
        float fogDistance;
        float cutoffHeight = 2.0f;
        float sunHeight = transform.position.y;
        if (sunHeight  >= 0.0f)
        {
            float h = sunHeight / cutoffHeight;
            if (h > 1.0f) h = 1.0f;
            fogColor = h * fogNoon + (1.0f - h) * fogDawn;
            fogDistance = h * fogDistanceNoon + (1.0f - h) * fogDistanceDawn;
        }
        else
        {
            float h = -sunHeight / cutoffHeight;
            if (h > 1.0f) h = 1.0f;
            fogColor = h * fogNight + (1.0f - h) * fogDawn;
            fogDistance = h * fogDistanceNight + (1.0f - h) * fogDistanceDawn;
        }
        RenderSettings.fogColor = fogColor;
        RenderSettings.fogEndDistance = fogDistance;
    }
}
