using UnityEngine;
using System.Collections;

public class TargetCamera : MonoBehaviour {
	public float rotateSpeed = 10.0f;
	public float zoomSpeed = 10.0f;
	public GameObject target;
    Transform targetTransform;
	Transform cameraTransform;

    float polar = 0;
    float azimuth = 0;
    float r = 10;
	void Start () {
        targetTransform = target.transform;
		cameraTransform = gameObject.transform;
	}
	
	void Update () {
		float dt = Time.deltaTime;
        if(Input.GetMouseButton(0))
		{
			azimuth += Input.GetAxis("Mouse X") * rotateSpeed;
			polar -= Input.GetAxis("Mouse Y") * rotateSpeed;
		}
		r -= Input.GetAxis ("Mouse ScrollWheel") * dt * zoomSpeed;
		Vector3 camPos = targetTransform.position;
		camPos += Quaternion.Euler(0,azimuth,0) * Quaternion.Euler(0,0,polar) * (Vector3.right * r);
		cameraTransform.position = camPos;
		cameraTransform.LookAt(targetTransform, new Vector3(0,1,0));
	}
}
