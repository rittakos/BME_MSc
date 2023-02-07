using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TextureOffset : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    public float movespeed = 0.01f;
    void Update()
    {
        Vector3 pos = transform.position;
        Material mat = GetComponent<Renderer>().material;
        mat.SetTextureOffset("_MainTex",
                                                                   new Vector2(pos.x*movespeed, 0));
    }

}
