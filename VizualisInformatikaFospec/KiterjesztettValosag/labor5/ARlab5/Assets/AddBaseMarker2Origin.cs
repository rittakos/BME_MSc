using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddBaseMarker2Origin : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update() 
    { 
        AROrigin origin = FindObjectOfType<AROrigin>(); 
        if (origin.GetBaseMarker() == null) 
        { 
            ARTrackedCamera tc = GetComponent<ARTrackedCamera>(); 
            origin.AddMarker(tc.GetMarker()); 
        } 
    }
}
