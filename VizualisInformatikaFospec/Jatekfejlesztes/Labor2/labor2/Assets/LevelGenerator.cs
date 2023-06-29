using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelGenerator : MonoBehaviour
{
    // Start is called before the first frame update
    public Transform gate;

    void Start()
    {
        for (int i = 0; i < 10; ++i)
        {
            Transform newgate = GameObject.Instantiate(gate);
            newgate.transform.Translate(new Vector3(0, 0, -20 + 4* i));
        }

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
