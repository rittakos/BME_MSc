using UnityEngine;
using System.Collections;

public class LevelGenerator : MonoBehaviour {
	public Transform groundPrefab;
	public Transform level1Prefab;
	public Transform level2Prefab;
	public Transform groundCoinPrefab;
	public Transform level1CoinPrefab;
	public Transform level2CoinPrefab;
	public Transform groundMonsterPrefab;
	public Transform level1MonsterPrefab;
	public Transform level2MonsterPrefab;
	public Transform groundBoxPrefab;
	public Transform level1BoxPrefab;
	public Transform level2BoxPrefab;

	void Start () {
		int levelSize = 50;
		float groundProb = 5.0f / 6.0f;
		float level1Prob = 0.5f;
		float level2Prob = 0.5f;
		float coinProb = 1.0f/3.0f;
		float monsterProb = 0.25f;
		float boxProb = 0.5f;
		int lastGround = -10;
		int lastLevel1 = -10;
		for (int i = -3; i < levelSize+3; ++i) {
			Vector3 offset = new Vector3(i*10,0,0);
			if(i < 0 || i >= levelSize)
			{
				Transform newGroundElement = Instantiate<Transform> (groundPrefab);
				newGroundElement.Translate(offset);
			}
			else
			{
				//ground
				bool ground = false;
				float rand = Random.value;
				if(rand < groundProb || (lastGround < i-1 && lastLevel1 < i-2))
				{
					Transform newGroundElement = Instantiate<Transform> (groundPrefab);
					newGroundElement.Translate(offset);
					lastGround = i;
					ground = true;

					bool coin = false;
					rand = Random.value;
					if(rand < coinProb){
						Transform newCoinElement = Instantiate<Transform> (groundCoinPrefab);
						newCoinElement.Translate(offset);
						coin = true;
					}
					bool monster = false;
					rand = Random.value;
					if(rand < monsterProb){
						Transform newMonsterElement = Instantiate<Transform> (groundMonsterPrefab);
						newMonsterElement.Translate(offset);
						monster = true;
					}
					if(!coin && !monster)
					{
						rand = Random.value;
						if(rand < boxProb){
							Transform newBoxElement = Instantiate<Transform> (groundBoxPrefab);
							newBoxElement.Translate(offset);						
						}
					}
				}

				//first floor
				bool level1 = false;
				if(ground) // put first level only above ground
				{
					rand = Random.value;
					if(rand < level1Prob)
					{
						Transform newElement = Instantiate<Transform> (level1Prefab);
						newElement.Translate(offset);
						level1 = true;
						lastLevel1 = i;

						bool coin = false;
						rand = Random.value;
						if(rand < coinProb){
							Transform newCoinElement = Instantiate<Transform> (level1CoinPrefab);
							newCoinElement.Translate(offset);
							coin = true;
						}

						bool monster = false;
						rand = Random.value;
						if(rand < monsterProb){
							Transform newMonsterElement = Instantiate<Transform> (level1MonsterPrefab);
							newMonsterElement.Translate(offset);
							monster = true;
						}
						if(!coin && !monster)
						{
							rand = Random.value;
							if(rand < boxProb){
								Transform newBoxElement = Instantiate<Transform> (level1BoxPrefab);
								newBoxElement.Translate(offset);						
							}
						}
					}
				}

				//second floor
				bool level2 = false;
				if(level1) // put second level only above first level
				{
					rand = Random.value;
					if(rand < level2Prob)
					{
						Transform newElement = Instantiate<Transform> (level2Prefab);
						newElement.Translate(offset);
						level2 = true;

						bool coin = false;
						rand = Random.value;
						if(rand < coinProb){
							Transform newCoinElement = Instantiate<Transform> (level2CoinPrefab);
							newCoinElement.Translate(offset);
							coin = true;
						}

						bool monster = false;
						rand = Random.value;
						if(rand < monsterProb){
							Transform newMonsterElement = Instantiate<Transform> (level2MonsterPrefab);
							newMonsterElement.Translate(offset);
							monster = true;
						}

						if(!coin && !monster)
						{
							rand = Random.value;
							if(rand < boxProb){
								Transform newBoxElement = Instantiate<Transform> (level2BoxPrefab);
								newBoxElement.Translate(offset);						
							}
						}
					}
				}
			}
		}
	}
}
