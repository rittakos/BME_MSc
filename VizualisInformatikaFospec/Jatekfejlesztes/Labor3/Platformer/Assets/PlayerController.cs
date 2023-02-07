using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float movespeed = 5f;
    public float jumpVel = 50f;

    private Animator animator;
    private Rigidbody2D physiscBody;
    private GameObject fallTrigger;

    // Start is called before the first frame update
    void Start()
    {
        animator = this.GetComponent<Animator>();
        physiscBody = GetComponent<Rigidbody2D>();
        fallTrigger = GameObject.Find("FallTrigger");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float dt = Time.deltaTime;
        if (Input.GetKey(KeyCode.Escape))
            Application.Quit();

        bool grounded = false;
        RaycastHit2D hit = Physics2D.Raycast(transform.position + new Vector3(0, -1.5f, 0), new Vector3(0, -1, 0));
        if (hit.collider != null &&
           hit.distance < 0.02 &&
           hit.collider.gameObject != gameObject && 
           hit.collider.gameObject != fallTrigger)
            grounded = true;


        Vector3 dv = new Vector3(0, 0, 0);
        bool left = Input.GetAxis("Horizontal") < 0;
        bool right = Input.GetAxis("Horizontal") > 0;
        bool up = Input.GetAxis("Vertical") > 0;
        if (right) dv += new Vector3(movespeed * dt, 0, 0);
        if (left) dv += new Vector3(-movespeed * dt, 0, 0);
        if (up) dv += new Vector3(0, jumpVel * dt, 0);

         if (dv.magnitude > 0) animator.SetInteger("PlayerAnimState", 1);
        else animator.SetInteger("PlayerAnimState", 0);

        transform.position += dv;
        Vector3 oldVel = physiscBody.velocity;
        Vector3 newVel = oldVel + dv;
        physiscBody.velocity = newVel;

    }
}
