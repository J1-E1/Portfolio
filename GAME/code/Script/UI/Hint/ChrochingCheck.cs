using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChrochingCheck : MonoBehaviour
{
    public ChrochingCheck nextCheckPoint;

    private void OnTriggerEnter(Collider other)
    {
        if (other.transform.tag == "Player")
        {
            FindObjectOfType<HintMenu>().iscrouch = !FindObjectOfType<HintMenu>().iscrouch;
        }
    }
}
