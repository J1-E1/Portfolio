using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;


[RequireComponent(typeof(NavMeshAgent))]
[RequireComponent(typeof(Animator))]

public class PedstrainController : MonoBehaviour
{
    Animator animator;
    NavMeshAgent agent;
    Vector2 smoothDeltaPosition = Vector2.zero;
    Vector2 velocity = Vector2.zero;

    public Waypoint waypoint;

    public GameObject traget;
    public StateMachine stateMachine = new StateMachine();


    void Start()
    {
        stateMachine.ChangeState(new State_Walk(this));//
        animator = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
        agent.updatePosition = false;
    }

    float sightFov = 110.0f;
    // Update is called once per frame
    void Update()
    {

        Vector3 worldDeltaPosition = agent.nextPosition - transform.position;
        // Map 'worldDeltaPosition' to local space
        float dx = Vector3.Dot(transform.right, worldDeltaPosition);
        float dz = Vector3.Dot(transform.forward, worldDeltaPosition);
        Vector2 deltaPosition = new Vector2(dx, dz);

        // Low-pass filter the deltaMove
        float smooth = Mathf.Min(1.0f, Time.deltaTime / 0.15f);
        smoothDeltaPosition = Vector2.Lerp(smoothDeltaPosition, deltaPosition, smooth);

        // Update velocity if time advances
        if (Time.deltaTime > 1e-5f)
            velocity = smoothDeltaPosition / Time.deltaTime;

        bool shouldMove = velocity.magnitude > 0.5f && agent.remainingDistance > agent.radius;

        // Update animation parameters
        animator.SetBool("move", shouldMove);
        animator.SetFloat("velocityX", velocity.x);
        animator.SetFloat("velocityZ", velocity.y);

      
    

        // Pull character towards agent
        if (worldDeltaPosition.magnitude > agent.radius)
            transform.position = agent.nextPosition - 0.9f * worldDeltaPosition;

        stateMachine.Update();//
    }

    // update the position of the character
    void OnAnimatorMove()
    {
        // Update position based on animation movement using navigation surface height
        Vector3 position = animator.rootPosition;
        position.y = agent.nextPosition.y;
        transform.position = position;
    }

    public bool seenTarget = false;
    public Vector3 lastSeenPosition;
    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject == traget)
        {
            // calculate the angle between target -- enmy
            Vector3 direction = other.transform.position - transform.position;
            float angle = Vector3.Angle(direction, transform.forward);

            RaycastHit hit;
            seenTarget = false;
            //0.5:half of that angle
            if (angle < sightFov * 0.5)
            {
                if (Physics.Raycast(transform.position + transform.up,
                    direction.normalized,
                    out hit, GetComponent<SphereCollider>().radius))
                {
                    if (hit.collider.gameObject == traget)
                    {
                        seenTarget = true;
                        lastSeenPosition = traget.transform.position;
                    }
                }
            }

        }

    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        if (GetComponent<SphereCollider>())
        {
            Gizmos.DrawWireSphere(transform.position, GetComponent<SphereCollider>().radius);


            if (seenTarget)
                Gizmos.DrawLine(transform.position, lastSeenPosition);
            if (lastSeenPosition != Vector3.zero)
                Gizmos.DrawWireSphere(lastSeenPosition, 1.0f);

            Vector3 leftPeripheral;
            Vector3 rightPeripheral;

            leftPeripheral = (Quaternion.AngleAxis(sightFov * 0.5f, Vector3.up) * transform.forward * GetComponent<SphereCollider>().radius) + transform.position;
            rightPeripheral = (Quaternion.AngleAxis(-sightFov * 0.5f, Vector3.up) * transform.forward * GetComponent<SphereCollider>().radius) + transform.position;

            Gizmos.DrawLine(transform.position, rightPeripheral);
            Gizmos.DrawLine(transform.position, leftPeripheral);
        }

    }
}
