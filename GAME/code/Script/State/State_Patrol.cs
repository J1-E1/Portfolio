using UnityEngine;
using UnityEngine.AI;

public class State_Patrol : IState
{

    AIController owner;
    NavMeshAgent agent;
    Waypoint waypoint;

    public State_Patrol(AIController owner)
    {
        this.owner = owner;
    }

    public void Enter()
    {
        Debug.Log("entering patrol state");

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
            owner.stateMachine.ChangeState(new State_Hello(owner));
        }
    }
    public void Exit()
    {
        Debug.Log("exiting patrol state");
        agent.isStopped = true;
    }

}
