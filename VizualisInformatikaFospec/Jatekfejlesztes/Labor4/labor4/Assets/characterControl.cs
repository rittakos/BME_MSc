using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class characterControl : MonoBehaviour
{
    Animator animator;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    void Die() 
    { 
        animator.enabled = !animator.enabled; 
        Rigidbody ownBody = GetComponent<Rigidbody>(); 
        Rigidbody[] ragdollBodies; ragdollBodies = GetComponentsInChildren<Rigidbody>(); 
        foreach (Rigidbody body in ragdollBodies) 
        { 
            if (body != ownBody) 
                body.isKinematic = animator.enabled; 
        } 
    }

    // Update is called once per frame
    void Update()
    {
        float runAxis = Input.GetAxis("Run");
        float forwardAxis = Input.GetAxis("Vertical"); 
        animator.SetFloat("forward", forwardAxis * (1.0f + runAxis)); 
        float sideAxis = Input.GetAxis("Horizontal"); 
        animator.SetFloat("side", sideAxis);
        float mouseX = Input.GetAxis("MouseX");
        transform.Rotate(new Vector3(0, mouseX, 0));

        if (Input.GetKeyDown(KeyCode.Space))
        {
            animator.SetTrigger("jumpTriggered");
        }
        else if (Input.GetKeyDown("q"))
        {
            animator.SetInteger("attackType", 0);
            animator.SetTrigger("attackTrigger");
        }
        else if (Input.GetKeyDown("e"))
        {
            animator.SetInteger("attackType", 1);
            animator.SetTrigger("attackTrigger");
        } else if (Input.GetKeyDown("x")) 
        { 
            Die(); 
        }
    }
}
