using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenerateLevel : MonoBehaviour
{
    public uint sphereCountPerDim = 10;
    public uint lightCount = 100;
    public float lightSpeed = 0.4f;
    public Camera cam;
    public RenderingPath cameraRenderPath = RenderingPath.Forward;

    GameObject[] spheres;
    GameObject[] lights;
    Vector3[] lightPositions;

    void CreateSpheres()
    {
        if (spheres != null)
        {
            for (int i = 0; i < spheres.Length; ++i)
            {
                Destroy(spheres[i]);
            }
        }

        uint N = sphereCountPerDim;
        spheres = new GameObject[N * N * N];
        for (uint x = 0; x < N; ++x)
        {
            for (int y = 0; y < N; ++y)
            {
                for (int z = 0; z < N; ++z)
                {
                    GameObject go = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                    go.transform.position = new Vector3(x, y, z);
                    go.transform.localScale *= 0.7f;
                    spheres[x * N * N + y * N + z] = go;
                }
            }
        }

        if (cam == null)
        {
            cam = FindObjectOfType<Camera>();
        }
        if (cam)
        {
            TargetCamera targetCam = cam.GetComponent<TargetCamera>();
            if (targetCam)
            {
                targetCam.target = spheres[(N / 2) * N * N + N / 2 * N + N / 2];
            }
        }
    }

    void CreateLights()
    {
        if (lights != null)
        {
            for (int i = 0; i < lights.Length; ++i)
            {
                Destroy(lights[i]);
            }
        }

        uint N = lightCount;
        lights = new GameObject[N];
        lightPositions = new Vector3[N];
        for (int i = 0; i < N; ++i)
        {
            GameObject go = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            go.transform.localScale *= 0.15f;
            Light l = go.AddComponent<Light>();
            l.color = new Color(Random.value, Random.value, Random.value);
            go.GetComponent<Renderer>().material.shader = Shader.Find("Unlit/Color");
            go.GetComponent<Renderer>().material.color = l.color;
            l.intensity = Random.Range(0.05f / sphereCountPerDim, 5.0f / sphereCountPerDim);
            l.range = Random.Range(1, 10);
            go.transform.position = new Vector3(
                Random.Range(-0.2f * sphereCountPerDim, 1.2f * sphereCountPerDim),
                Random.Range(-0.2f * sphereCountPerDim, 1.2f * sphereCountPerDim),
                Random.Range(-0.2f * sphereCountPerDim, 1.2f * sphereCountPerDim));
            lightPositions[i] = go.transform.position;
            lights[i] = go;
        }
    }

    void Awake()
    {
        uint N = sphereCountPerDim;
        Debug.Log("Default pixel light count: " + QualitySettings.pixelLightCount);
        QualitySettings.pixelLightCount = (int)N;
        Debug.Log("New pixel light count: " + QualitySettings.pixelLightCount);

        CreateSpheres();
        CreateLights();
    }

    void Update()
    {
        if (cam)
        {
            cam.renderingPath = cameraRenderPath;
        }

        if (lightCount != lights.Length)
        {
            CreateLights();
        }

        for (int i = 0; i < lights.Length; ++i)
        {
            Vector3 dir = new Vector3(i % 7 - 3, i % 9 - 4, i % 13 - 6);
            lights[i].transform.position = lightPositions[i] + dir * Mathf.Sin(Time.time * (i % 5 + 1) * lightSpeed + (i % 29));
        }
    }
}
