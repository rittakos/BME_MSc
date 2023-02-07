using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeroControl : MonoBehaviour
{
    public float speed = 2.0f;
    CharacterController cController;
    Animator animator;

    float timeToDanceBase = 3.0f;
    float timeToDance = 3.0f;
    bool isDancing = false;
    // Start is called before the first frame update
    void Start()
    {
        cController = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!isDancing)
        {
            float runScaler = 0.8f;
            if (Input.GetKey(KeyCode.LeftShift))
                runScaler = 2.0f;
            Vector3 moveSpeed = new Vector3();
            moveSpeed = moveSpeed + Vector3.down;
            moveSpeed = moveSpeed + Vector3.right * Input.GetAxis("Horizontal") * runScaler;
            moveSpeed = moveSpeed + Vector3.forward * Input.GetAxis("Vertical") * runScaler;
            cController.SimpleMove(speed * moveSpeed);
            Vector3 forward = cController.velocity;
            forward.y = 0.0f;
            float velMag = forward.magnitude;
            if (velMag > 2.0f) velMag = 2.0f;
            if (velMag > 0.0f)
            {
                transform.forward = forward.normalized;
                timeToDance = timeToDanceBase;
                animator.SetFloat("speed", velMag);
            }
            else
                timeToDance -= Time.deltaTime;

            if (timeToDance < 0)
            {
                isDancing = true;
                timeToDance = timeToDanceBase;
            }

            if (isDancing)
                animator.SetTrigger("dance");
                
        }
        else
        {
            float time = animator.GetCurrentAnimatorStateInfo(0).normalizedTime;
            if (time > 1)
                isDancing = false;

        }

    }

    void OnControllerColliderHit(ControllerColliderHit hit)
    {         
        Rigidbody rb = hit.collider.gameObject.GetComponent<Rigidbody>();
        if(rb)
        {
            rb.AddForce(cController.velocity, ForceMode.VelocityChange);
        }
    }
}
