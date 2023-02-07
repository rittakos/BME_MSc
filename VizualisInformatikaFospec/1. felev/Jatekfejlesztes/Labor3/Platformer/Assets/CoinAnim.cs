using UnityEngine;
using System.Collections;

public class CoinAnim : MonoBehaviour {
	Vector3 center;
	public float moveSpeed = 10.0f;
	public float moveDist = 0.5f;
	public float rotateSpeed = 360.0f;
	void Start () {
		center = transform.position;
	}
	void Update () {
		float t = Time.time;
		transform.position = center + moveDist * Mathf.Sin(t * moveSpeed) * Vector3.up; 
		transform.eulerAngles = new Vector3(0,rotateSpeed*t,0);
	}
}
