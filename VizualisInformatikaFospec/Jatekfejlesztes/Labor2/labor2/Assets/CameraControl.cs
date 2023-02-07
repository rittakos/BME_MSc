using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float moveSpeed = 10;
        float dt = Time.deltaTime;
        Vector3 move = new Vector3(0, 0, 0);
        if (Input.GetAxis("Horizontal") < 0)
        {
            move = move + new Vector3(-1, 0, 0);
        }
        else if (Input.GetAxis("Horizontal") > 0)
        {
            move = move + new Vector3(1, 0, 0);
        }
        if (Input.GetAxis("Vertical") > 0)
        {
            move = move + new Vector3(0, 0, 1);
        }
        else if (Input.GetAxis("Vertical") < 0)
        {
            move = move + new Vector3(0, 0, -1);
        }
        move.Normalize();
        transform.Translate(move * dt * moveSpeed);

        float rotateSpeed = 2.0f;
        if (Input.GetAxis("Mouse X") > 0)
        {
            transform.RotateAround(Vector3.up, dt * rotateSpeed);
        }
        if (Input.GetAxis("Mouse X") < 0)
        {
            transform.RotateAround(Vector3.up, -dt * rotateSpeed);
        }
        Vector3 rightVector = transform.rotation * Vector3.right;
        if (Input.GetAxis("Mouse Y") > 0)
        {
            transform.RotateAround(rightVector, -dt * rotateSpeed);
        }
        if (Input.GetAxis("Mouse Y") < 0)
        {
            transform.RotateAround(rightVector, dt * rotateSpeed);
        }

    }

}
