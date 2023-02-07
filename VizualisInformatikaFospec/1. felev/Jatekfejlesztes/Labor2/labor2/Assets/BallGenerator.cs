using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class BallGenerator : MonoBehaviour
{
    public float coolDown = 1;
    public float force = 1000;
    public Transform ball;
    public Transform camera;

    private float lastFireTime = 0;

    // Start is called before the first frame update
    void Start()
    {
        lastFireTime = 0;
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 dir = new Vector3(1, 0, 0);

        lastFireTime += Time.deltaTime;

        if(Input.GetKeyDown(KeyCode.Space) && lastFireTime >= coolDown)
        {
            lastFireTime = 0;
            Transform newBall = Instantiate(ball);
            newBall.transform.position = camera.transform.position;
            dir = camera.transform.forward;
            newBall.GetComponent<Rigidbody>().AddForce(force * dir);
        }
    }
}
