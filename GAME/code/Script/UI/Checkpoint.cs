using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Checkpoint : MonoBehaviour
{
    public Checkpoint nextCheckPoint;

    private void OnTriggerEnter(Collider other)
    {
        if(other.transform.tag == "Player")
        {
            Debug.Log("change");
            FindObjectOfType<CompassController>().targetTransform = nextCheckPoint.transform;
        }
    }
}
