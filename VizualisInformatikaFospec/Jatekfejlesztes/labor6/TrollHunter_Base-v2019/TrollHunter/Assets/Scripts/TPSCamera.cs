using UnityEngine;
using System.Collections;

public class TPSCamera : MonoBehaviour {
	public float cameraHeight = 3.0f;
	public float targetHeight = 1.6f;
	public float camDistance = 3.0f;
	public float smoothness = 0;
    [Range(0,1)]
    public float mouseSensitivity = 1.0f;

	Transform targetTransform;
	void Start () {
		targetTransform = gameObject.transform;
	}
	
	void Update () {
        Transform cameraTransform = Camera.main.transform;
		float mouseY = Input.GetAxis ("Mouse Y");
		cameraHeight += mouseY * Time.deltaTime * 100 * mouseSensitivity;
		if (cameraHeight > 10.0f)
			cameraHeight = 10.0f;
		if (cameraHeight < 0.1f)
			cameraHeight = 0.1f;
		float mouseScroll = Input.GetAxis ("Mouse ScrollWheel");
		camDistance += mouseScroll * Time.deltaTime * 100 * mouseSensitivity;


		Vector3 targetDir = targetTransform.forward;
		Vector3 oldCamPos = cameraTransform.position;
		Vector3 newCamPos = targetTransform.position 
			- targetDir * camDistance + new Vector3 (0, cameraHeight, 0);
		Vector3 targetPos = targetTransform.position + new Vector3 (0, targetHeight, 0);
		newCamPos = Vector3.Lerp (newCamPos, oldCamPos, smoothness);
		cameraTransform.position = newCamPos;
		cameraTransform.LookAt(targetPos);
		oldCamPos = newCamPos;
	}
}
