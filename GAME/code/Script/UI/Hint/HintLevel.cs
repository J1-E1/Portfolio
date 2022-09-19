using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HintLevel : MonoBehaviour
{
    public HintLevel nextHintlevel;

    private void OnTriggerEnter(Collider other)
    {
        if (other.transform.tag == "Player")
        {
            FindObjectOfType<HintMenu>().islevelHint = !FindObjectOfType<HintMenu>().islevelHint;
        }
    }
}
