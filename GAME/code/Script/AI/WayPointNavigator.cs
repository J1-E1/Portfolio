using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WayPointNavigator : MonoBehaviour
{


    PedstrainController controller;
    public Waypoint currentWaypoint;
    int direction;

    private void Awake()
    {
         controller = GetComponent<PedstrainController>();
    }
    
    // Start is called before the first frame update
    void Start()
    {
        direction = Mathf.RoundToInt(Random.Range(0f, 1f));
       // controller.SetDestination(currentWaypoint.GetPosition());
    }

    // Update is called once per frame
    void Update()
    {
        /*
        if (controller.reachedDestination)
        {
            currentWaypoint = currentWaypoint.nextWaypoint;
            controller.SetDestination(currentWaypoint.GetPosition());
        }*/

        if(direction == 0)
        {
            currentWaypoint = currentWaypoint.nextWaypoint;
        }else if (direction == 1)
        {
            currentWaypoint = currentWaypoint.previousWaypoint;
        }


    }
}
    