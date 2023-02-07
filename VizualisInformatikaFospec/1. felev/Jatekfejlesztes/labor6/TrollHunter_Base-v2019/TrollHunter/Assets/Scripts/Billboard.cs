using UnityEngine;
using System.Collections;

public class Billboard : MonoBehaviour {
	void Start () {
	}
	
	void Update () {
        transform.LookAt(Camera.main.transform.position);
        transform.Rotate(0, 180, 0);
    }
}
