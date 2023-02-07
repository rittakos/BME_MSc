using UnityEngine;
using System.Collections;

public class CharacterControlBase : MonoBehaviour
{
	public int Health = 60;
	public int Damage1 = 20;
	public int Damage2 = 30;
	public int Damage3 = 40;
	public float DamageRange = 1.0f;
    public GameObject healthBarImage;

	protected Animator animator;
	public bool isDead = false;
	protected float ResurrectionTime = 5.0f;
	protected int MaxHealth = 60;
    
    void Start () {
		animator = GetComponent<Animator> ();
		Reborn ();
		StartImpl ();
	}

	protected virtual void StartImpl(){

	}

    void UpdateHealthBar(int health) {
        if (!healthBarImage) {
            Debug.LogWarning("No health bar image connected!");
            return;
        }
        healthBarImage.transform.localScale = new Vector3((float)Mathf.Max(health, 0) / (float)MaxHealth, 1, 1);
    }

	void Update ()
	{
        UpdateHealthBar(Health);
		if (isDead) {
			return;
		}
		UpdateImpl();
	}

	protected virtual void UpdateImpl(){
		
	}

	protected void Die()
	{
		isDead = true;

		animator.enabled = false;
		Rigidbody ownBody = GetComponent<Rigidbody>();
		Rigidbody[] ragdollBodies;
		ragdollBodies = GetComponentsInChildren<Rigidbody> ();
		foreach (Rigidbody body in ragdollBodies) {
			if(body != ownBody)
				body.isKinematic = false;
		}
        GetComponent<Collider>().isTrigger = true;//make it unmovable
        ownBody.useGravity = false;
        GetComponentInChildren<Canvas>().enabled = false;
    }

	protected void Reborn()
	{
		isDead = false;
		Health = MaxHealth;
		animator.enabled = true;
		Rigidbody ownBody = GetComponent<Rigidbody>();
		Rigidbody[] ragdollBodies;
		ragdollBodies = GetComponentsInChildren<Rigidbody> ();
		foreach (Rigidbody body in ragdollBodies) {
			if(body != ownBody)
				body.isKinematic = true;
		}
        GetComponent<Collider>().isTrigger = false;//make it movable
        ownBody.useGravity = true;
        GetComponentInChildren<Canvas>().enabled = true;
    }

	public void takeDamage(int damage)
	{
        if (isDead) return;
		Health -= damage;
        if (Health <= 0) {
            Die();
            if (ResurrectionTime >= 0) {  // < 0: no resurrection
                Invoke("Reborn", ResurrectionTime);
            }
        }
	}

	protected void hit(int damage)
	{
		//Debug.Log ("Hit\n");
		GameObject[] paladins = GameObject.FindGameObjectsWithTag ("Player");
		foreach (GameObject p in paladins)
		{
			if (p == gameObject)
				continue;
			Debug.Log ("Checking paladin\n");
			Vector3 dir = p.transform.position - transform.position;
			Debug.Log ("Paladin range " + dir.magnitude);
			if (dir.magnitude < DamageRange)
			{
				Debug.Log ("Paladin in range\n");
				if (Vector3.Angle (dir.normalized, transform.forward) < 45)
				{
					Debug.Log ("paladin hit\n");
					p.GetComponent<CharacterControlBase> ().takeDamage (damage);
				}
			}
		}
		GameObject[] trolls = GameObject.FindGameObjectsWithTag ("Troll");
		foreach (GameObject t in trolls)
		{
			if (t == gameObject)
				continue;
			//Debug.Log ("Checking troll\n");
			Vector3 dir = t.transform.position - transform.position;
			//Debug.Log ("Troll range" + dir.magnitude);
			if (dir.magnitude < DamageRange)
			{
				//Debug.Log ("Troll in range\n");
				if (Vector3.Angle (dir.normalized, transform.forward) < 45)
				{
					//Debug.Log ("Troll hit\n");
					t.GetComponent<CharacterControlBase> ().takeDamage (damage);
				}
			}
		}
	}

	public void AnimationHitpoint(int mode)
	{
		switch (mode) {
		case 0:
			hit (Damage1);
			break;
		case 1:
			hit (Damage2);
			break;
		case 2:
			hit (Damage3);
			break;
		}
	}
}

public class CharacterControl : CharacterControlBase {	

	public CharacterControl()
	{
		MaxHealth = Health = 60;
		Damage1 = 20;
		Damage2 = 20;
		Damage3 = 40;
		ResurrectionTime = 10.0f;
		DamageRange = 2.0f;
	}

	protected override void StartImpl () {
		Cursor.lockState = CursorLockMode.Confined;
	}

	protected override void UpdateImpl() {
		float runAxis = Input.GetAxis ("Run");
		float forwardAxis = Input.GetAxis ("Vertical");
		animator.SetFloat ("forward", forwardAxis * (1.0f + runAxis));
		float sideAxis = Input.GetAxis ("Horizontal");
		animator.SetFloat ("side", sideAxis * (1.0f + runAxis));

		float mouseX = Input.GetAxis ("Mouse X");
		transform.Rotate(new Vector3(0,mouseX*Time.deltaTime*1000,0));

		if (Input.GetKeyDown (KeyCode.Space))
			animator.SetTrigger ("JumpTriggered");
		else if (Input.GetKeyDown ("q") || Input.GetMouseButtonDown(0)) {
			animator.SetInteger ("AttackType", 0);
			animator.SetTrigger ("AttackTriggered");
		} else if (Input.GetKeyDown ("e") || Input.GetMouseButtonDown(1)) {
			animator.SetInteger ("AttackType", 1);
			animator.SetTrigger ("AttackTriggered");
		}
        else if (Input.GetKeyDown("r") || Input.GetMouseButtonDown(2))
        {
            animator.SetInteger("AttackType", 2);
            animator.SetTrigger("AttackTriggered");
        }
        else if (Input.GetKeyDown ("k")) {
            takeDamage(MaxHealth);
		}
	}
}
