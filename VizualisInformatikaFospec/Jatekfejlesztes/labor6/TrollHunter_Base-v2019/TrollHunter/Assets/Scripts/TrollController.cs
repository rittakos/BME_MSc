using UnityEngine;
using System.Collections;
using UnityEngine.AI;

public class TrollController : CharacterControlBase {

	GameObject CurrentTarget = null;
    NavMeshAgent NavAgent;

    private float VisibilityRange = 20.0f;

    protected override void StartImpl() 
	{ 
		NavAgent = GetComponent<NavMeshAgent>();
        NavAgent.updatePosition = false;
    }

    void OnAnimatorMove()
	{
        transform.position = animator.rootPosition; 
		NavAgent.nextPosition = transform.position;
    }

    public TrollController () {
		MaxHealth = Health = 120;
		Damage1 = 40;
		Damage2 = 60;
		Damage3 = 80;
		ResurrectionTime = -1; //no resurrection
		DamageRange = 1.5f;
	}

	protected float targetCost(GameObject target)
	{
		return 0;	
	}

	protected override void UpdateImpl() {

		GameObject[] paladins = GameObject.FindGameObjectsWithTag ("Player");

		GameObject target = null;
		float minCost = 10000000000;

		foreach (GameObject p in paladins) {
			if (p.GetComponent<CharacterControlBase> ().isDead)
				continue;

			Vector3 dir = p.transform.position - transform.position;
			float angle = Vector3.Angle(dir, transform.forward);
			float distance = dir.magnitude;
			if (distance < VisibilityRange && angle < 120 || distance < DamageRange)
			{
				float cost = distance;
				if (cost < minCost) {
					minCost = distance;
					target = p;
				}
			}
		}				
		if (target == null)
		{
			if (CurrentTarget == null || CurrentTarget.tag != "TrollImportantPoint") {
				GameObject[] importantPoints = GameObject.FindGameObjectsWithTag ("TrollImportantPoint");
				CurrentTarget = importantPoints [(int)Random.Range (0, importantPoints.Length - 1)];
			}
		}
		else
			CurrentTarget = target;


		{
			Vector3 dir = CurrentTarget.transform.position - transform.position;
			float angle = Vector3.Angle(dir, transform.forward);
			float distance = dir.magnitude;
            //transform.LookAt (new Vector3(CurrentTarget.transform.position.x,transform.position.y,CurrentTarget.transform.position.z));
            //if (distance > DamageRange * 0.2f) {
            //	animator.SetFloat ("forward", 
            //		Mathf.Lerp (0.0f, 2, Mathf.Min (1.0f, (distance - DamageRange * 0.2f) / (DamageRange * 2.0f))));
            //} 
            NavAgent.destination = CurrentTarget.transform.position;
            dir = NavAgent.nextPosition - transform.position; 
			dir.y = 0;
            //animator.SetFloat("forward", dir.magnitude / Time.deltaTime);
            transform.forward = dir.normalized;
            if (distance > DamageRange * 0.2f)
            {
                animator.SetFloat("forward", Mathf.Lerp(0.0f, 2, Mathf.Min(1.0f, (distance - DamageRange * 0.2f) / (DamageRange * 2.0f))));
            }

            if (CurrentTarget.tag == "Player" && distance < DamageRange && angle < 45) 
			{
                if (Random.Range(0.0f, 1.0f) > 0.5f) 
					animator.SetInteger("AttackType", 0);
                else
                    animator.SetInteger("AttackType", 1);
                animator.SetTrigger("AttackTriggered");

            }
        }

	}
}

