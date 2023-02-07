using UnityEngine;
using System.Collections;

public class Rotate : MonoBehaviour {
	public enum Axis {X, Y, Z};

	public Axis rotationAxis = Axis.Y;
	public float angleSpeed = 20.0f;
	
	void Start () {
	
	}

	void Update () {
		float t = Time.time;
		Quaternion newRotation = Quaternion.Euler(Vector3.zero);
		switch (rotationAxis) {
		case Axis.X:
			newRotation = Quaternion.Euler(new Vector3(t*angleSpeed,0,0));
			break;
		case Axis.Y:
			newRotation = Quaternion.Euler(new Vector3(0,t*angleSpeed,0));
			break;
		case Axis.Z:
			newRotation = Quaternion.Euler(new Vector3(0,0,t*angleSpeed));
			break;
		default:
			break;
		}
		transform.rotation = newRotation;
	}
}
