using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
public class State_Walk : IState
{

    PedstrainController owner;
    NavMeshAgent agent;
    Waypoint waypoint;

    public State_Walk(PedstrainController owner)
    {
        this.owner = owner;
    }

    public void Enter()
    {
        Debug.Log("Entering predestrain walking state");
        waypoint = owner.waypoint;
        agent = owner.GetComponent<NavMeshAgent>();

        agent.destination = waypoint.transform.position;
        agent.isStopped = false;

    }

    public void Execute()
    {
        if (!agent.pathPending && agent.remainingDistance < 0.5f)
        {
            Waypoint nextWaypoint = waypoint.nextWaypoint;
            waypoint = nextWaypoint;
            agent.destination = waypoint.transform.position;

        }

        if (owner.seenTarget)
        {
            owner.stateMachine.ChangeState(new State_SayHello(owner));
        }
    }

    public void Exit()
    {
        Debug.Log("Exiting walking state");
        agent.isStopped = true;
    }
}
