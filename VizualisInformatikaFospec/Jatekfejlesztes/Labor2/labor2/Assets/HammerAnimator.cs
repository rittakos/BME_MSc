using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HammerAnimator : MonoBehaviour
{
    public float rotateSpeed = 300.0f;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float dt = Time.deltaTime;
        transform.Rotate(Vector3.up * dt * rotateSpeed);

    }
}
