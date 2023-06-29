using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSCamera : MonoBehaviour
{
    public Transform target; 
    public float cameraHeight = 3.0f;
    public float targetHeight = 1.6f; 
    public float camDistance = 3.0f; 
    public float smoothness = 0;
    Transform targetTransform; 
    Transform cameraTransform;
    void Start() 
    { 
        targetTransform = target.transform;
        cameraTransform = transform;
    }
    void Update()
    {
        float mouseY = Input.GetAxis("MouseY");
        cameraHeight += mouseY; 
        float mouseScroll = Input.GetAxis("MouseScrollWheel"); 
        camDistance += mouseScroll; 
        Vector3 targetDir = targetTransform.forward;
        Vector3 oldCamPos = cameraTransform.position;
        Vector3 newCamPos = targetTransform.position - targetDir * camDistance + new Vector3(0, cameraHeight, 0); 
        Vector3 targetPos = targetTransform.position + new Vector3(0, targetHeight, 0); 
        newCamPos = Vector3.Lerp(newCamPos, oldCamPos, smoothness); 
        cameraTransform.position = newCamPos; 
        cameraTransform.LookAt(targetPos); 
        oldCamPos = newCamPos;
    }
}
