using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class LightAnimation : MonoBehaviour
{
    // Start is called before the first frame update
    public Transform light;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float t = Time.time;
        float dt = Time.deltaTime;
        this.transform.position = new Vector3(0.0f, 2.5f, 20.0f*Mathf.Sin(t * 2.0f));
    }
}
