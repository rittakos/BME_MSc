using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookAround : MonoBehaviour
{
    float mx = 0.0f;
    float my = 0.0f;
    public float maxDist = 1.0f;
    public float mouseSensitivity = 1.0f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {        
        Vector3 localPos = transform.localPosition;
        mx += mouseSensitivity * Input.GetAxis("Mouse X");
        mx = Mathf.Max(Mathf.Min(mx, 1.0f), -1.0f);
        my += mouseSensitivity * Input.GetAxis("Mouse Y");
        my = Mathf.Max(Mathf.Min(my, 1.0f), -1.0f);
        localPos.x = mx * maxDist;
        localPos.y = my * maxDist;
        transform.localPosition = localPos;
    }
}
