using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Orbit : MonoBehaviour
{
    public bool random = true;
    public float speed = 2.0f;
    public float maxRadius = 3.0f;

    float phi = 0;
    float theta = 0;
    float r = 3;

    void Update()
    {
        if (random)
        {
            phi += Random.value * speed * Time.deltaTime;
            theta += Random.value * speed * Time.deltaTime;
            r += (Random.value - 0.5f) * speed * Time.deltaTime;
            r = Mathf.Min(r, maxRadius);
        }
        else
        {
            phi = Time.time * speed * 1.07f;
            theta = (Time.time-0.37123f) * speed;
            r = (Mathf.Sin(Time.time * speed * 0.91f) + 1.0f) * 0.5f * maxRadius;
        }

        transform.position = new Vector3(
            r * Mathf.Sin(theta) * Mathf.Cos(phi), 
            r * Mathf.Sin(theta) * Mathf.Sin(phi), 
            r * Mathf.Cos(theta)
            );
    }
}
