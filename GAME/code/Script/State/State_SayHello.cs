using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
public class State_SayHello : IState
{
    PedstrainController owner;
    NavMeshAgent agent;
    Animator animator;

    public State_SayHello(PedstrainController owner)
    {
        this.owner = owner;
    }

    public void Enter()
    {
        Debug.Log("Entering Say hello state");
       

        agent = owner.GetComponent<NavMeshAgent>();
        animator = owner.GetComponent<Animator>();

        if (owner.seenTarget)
        {
            agent.isStopped = true;
        }
    }

    public void Execute()
    {
        if (!agent.pathPending && agent.remainingDistance < 5.0f)
        {
            agent.isStopped = true;
            animator.SetBool("move", false);
        }

        if (owner.seenTarget != true)
        {
            Debug.Log("lost sight");
            animator.SetBool("move", true);
            owner.stateMachine.ChangeState(new State_Walk(owner));
        }

    }

    public void Exit()
    {
        Debug.Log("Exiting say hello state");
        agent.isStopped = true;
    }
}
