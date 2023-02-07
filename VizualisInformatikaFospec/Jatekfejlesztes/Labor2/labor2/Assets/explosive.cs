using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class explosive : MonoBehaviour
{
    public float power = 1000.0f;
    void OnTriggerEnter(Collider other)
    {
        Rigidbody otherRB = other.GetComponent<Rigidbody>();
        if (otherRB != null)
        {
            Vector3 force = new Vector3(Random.Range(-1.0f, 1.0f),
                                        1.0f,
                                        Random.Range(-1.0f, 1.0f));
            otherRB.AddForce(force * power);
        }
    }
    void OnTriggerStay(Collider other)
    {
    }
    void OnTriggerExit(Collider other)
    {
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
