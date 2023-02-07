using UnityEngine;
using System.Collections;

public class Move : MonoBehaviour {

	public float speed = 20;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 newPos = transform.position;
		newPos.x += Time.deltaTime * speed;
		transform.position = newPos;
	}
}
