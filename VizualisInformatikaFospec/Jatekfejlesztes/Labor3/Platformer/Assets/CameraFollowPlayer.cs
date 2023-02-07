using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollowPlayer : MonoBehaviour
{
    public GameObject target;
    public float followspeed = 2.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float dt = Time.deltaTime;
        float fspeed = Mathf.Min(1.0f, followspeed * dt);
        Vector3 oldPos = transform.position;
        Vector3 newPos = oldPos;
        newPos.x = target.transform.position.x;
        newPos = oldPos + (newPos - oldPos) * fspeed;
        transform.position = newPos;
    }

}
