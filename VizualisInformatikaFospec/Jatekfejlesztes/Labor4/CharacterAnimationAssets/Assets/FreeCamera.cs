using UnityEngine;
using System.Collections;

public class FreeCamera : MonoBehaviour {
	public float moveSpeed = 5;
		
	void Update () {
		float dt = Time.deltaTime;
		Vector3 move = new Vector3(0,0,0);
		if (Input.GetAxis ("Horizontal") < 0) {
			move = move + new Vector3(-1,0,0);
		}
		else if(Input.GetAxis ("Horizontal") > 0) {
			move = move + new Vector3(1,0,0);
		}
		if (Input.GetAxis ("Vertical") > 0) {
			move = move + new Vector3(0,0,1);
		}
		else if (Input.GetAxis ("Vertical") < 0) {
			move = move + new Vector3(0,0,-1);
		}
		move.Normalize();
		transform.Translate(move * dt * moveSpeed);

		float rotateSpeed = 2.0f;
		transform.RotateAround(Vector3.up, dt *Input.GetAxis ("Mouse X") * rotateSpeed);
		Vector3 rightVector = transform.rotation * Vector3.right;
		transform.RotateAround(rightVector,-dt * Input.GetAxis ("Mouse Y") * rotateSpeed);

		//ez nem jó!
		//transform.Rotate(new Vector3(0,dt *Input.GetAxis ("Mouse X") * rotateSpeed,0));
		//transform.Rotate(new Vector3(-dt *Input.GetAxis ("Mouse Y") * rotateSpeed,0,0));

	}
}
