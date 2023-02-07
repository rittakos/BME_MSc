using UnityEngine;
using System.Collections;

public class GenerateMoria : MonoBehaviour {
	public Transform prefabPillar;
	public Transform prefabCeiling;
	public Transform prefWall;
	public Transform prefFloor;
	void Start() {
		/*
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 8; j++) {
				Instantiate(prefabPillar, new Vector3((-10 + i) * 10, 0, (-4 + j) * 10), Quaternion.identity);
			}
		}

		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 9; j++) {
				Instantiate(prefabCeiling, new Vector3((-10.5f + i) * 10f, 16.5f, (-4.5f + j) * 10f), Quaternion.identity);
			}
		}

		for (int i = 0; i < 16; i++) {
			Instantiate(prefWall, new Vector3((-10.5f + i) * 10f, 0.0f, -40.0f), Quaternion.identity);
			Instantiate(prefWall, new Vector3((-10.5f + i) * 10f, 0.0f,  30.0f), Quaternion.identity);
		}*/
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 9; j++) {
				Instantiate(prefFloor, new Vector3((-10.5f + i) * 10f, -0.2f, (-4.5f + j) * 10f), Quaternion.identity);
			}
		}
	}
}