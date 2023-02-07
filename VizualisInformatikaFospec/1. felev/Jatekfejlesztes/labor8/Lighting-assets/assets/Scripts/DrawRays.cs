using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawRays : MonoBehaviour
{
    public bool drawRays = true;
    public bool drawPixels = true;
    public uint rayDensity = 10;
    public float rayLength = 10;
    Camera cam;

    void Start()
    {
        cam = GetComponent<Camera>();
    }

    void Update()
    {
        float dx = (float)cam.pixelWidth / rayDensity;
        float dy = (float)cam.pixelHeight / rayDensity;

        if (drawRays)
        {
            for (float x = dx * 0.5f; x <= cam.pixelWidth - 1; x += dx)
            {
                for (float y = dy * 0.5f; y <= cam.pixelHeight - 1; y += dy)
                {
                    Ray ray = cam.ScreenPointToRay(new Vector3(x, y, 0));
                    Debug.DrawRay(ray.origin, ray.direction * rayLength, Color.yellow);
                }
            }
        }

        if (drawPixels)
        {
            for (float x = 0; x <= cam.pixelWidth - 1; x += dx)
            {
                Vector3 start = cam.ScreenToWorldPoint(new Vector3(x, 0, cam.nearClipPlane));
                Vector3 end = cam.ScreenToWorldPoint(new Vector3(x, cam.pixelHeight, cam.nearClipPlane));
                Debug.DrawRay(start, end - start, Color.red);
            }
            for (float y = 0; y <= cam.pixelHeight - 1; y += dy)
            {
                Vector3 start = cam.ScreenToWorldPoint(new Vector3(0, y, cam.nearClipPlane));
                Vector3 end = cam.ScreenToWorldPoint(new Vector3(cam.pixelWidth, y, cam.nearClipPlane));
                Debug.DrawRay(start, end - start, Color.red);
            }
        }
    }
}
