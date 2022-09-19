using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class State_Hello : IState
{
    AIController owner;
    NavMeshAgent agent;
    Animator animator;

    public State_Hello(AIController owner)
    {
        this.owner = owner;
    }

    public void Enter()
    {
        Debug.Log("entered Hello state");

        agent = owner.GetComponent<NavMeshAgent>();
        animator = owner.GetComponent<Animator>();

        if (owner.seenTarget)
        {
            agent.destination = owner.lastSeenPosition;
            agent.isStopped = false;
        }
    }
    public void Execute()
    {
        agent.destination = owner.lastSeenPosition;
        agent.isStopped = false;
        if (!agent.pathPending && agent.remainingDistance < 1.0f)
        {
            agent.isStopped = true;
            animator.SetBool("move", false);
            animator.SetBool("find", true);
        }

        if(owner.seenTarget != true)
        {
            Debug.Log("lost sight");
            animator.SetBool("move", true);
            animator.SetBool("find", false);
            owner.stateMachine.ChangeState(new State_Patrol(owner));
        }
    }

    public void Exit()
    {
        Debug.Log("exiting Hello state");
        agent.isStopped = true;
    }

}
