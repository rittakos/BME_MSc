using UnityEngine;
using System.Collections;

public class BigObstacleTrigger : MonoBehaviour {
	Animator animator;
	// Use this for initialization
	void Start () {
		animator = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnTriggerEnter(Collider other) {
		animator.SetTrigger ("MoveTrigger");
	}
}
