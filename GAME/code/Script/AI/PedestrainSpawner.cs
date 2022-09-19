using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class PedestrainSpawner : MonoBehaviour
{

    public GameObject pedestrainPrefeb;

    public int pedestrainsToSpawn;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(Spawn());
    }

   

    IEnumerator Spawn()
    {
        int count = 0;
        while (count < pedestrainsToSpawn)
        {
            GameObject obj = Instantiate(pedestrainPrefeb);

            // start walk from random child. get random child form waypoint list
            Transform child = transform.GetChild(Random.Range(0, transform.childCount - 1)); 
            obj.GetComponent<PedstrainController>().waypoint = child.GetComponent<Waypoint>();
           // obj.GetComponent<NavMeshAgent>().transform.position = child.GetComponent<Waypoint>();
            obj.GetComponent<NavMeshAgent>().Warp(child.position);

            yield return new WaitForEndOfFrame();

            count++;
        }

    }
}
