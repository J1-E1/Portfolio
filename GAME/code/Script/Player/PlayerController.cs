using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class PlayerController : MonoBehaviour
{
    private Animator animator;
    private CharacterController characterController; 
    public HealthBar healthBar;
    public ProgressBar progressBar;
    private Cinemachine3rdPersonFollow cinemachine;

    public Pose pose_1;
    public Pose pose_2;
    public Pose pose_3;

    //Health bar

    public int maxHealth = 100;
    public int currentHealth;

    //Progress Bar
    public int minProgress = 0;
    public int currentProgress ;
    public float whole_distance;

    

    // Start is called before the first frame update
    void Start()
    {
       currentHealth = maxHealth;// set the health bar
       healthBar.SetMaxHealth(maxHealth);

        currentProgress = minProgress;
        progressBar.SetProgress(minProgress);

        characterController = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
        cinemachine = GetComponent<Cinemachine3rdPersonFollow>();

        whole_distance = Vector3.Distance(pose_1.position, pose_2.position)
            + Vector3.Distance(pose_2.position, pose_3.position);


    }


    float verticalVelocity = 0.0f;
    float y = 0.0f;
    float forwardSpeed;
    float lateralSpeed;
    public float turnSpeed = 90.0f;
    public float moveSpeed_Forward = 3.0f;
    public float moveSpeed_Backward = 2.0f;
    private float original_Speed = 4.0f;
    public float crouchingHeight = 1.45f;
    public float characterHeight = 1.772769f;
    private bool isCrouching = false;
    private bool isRunning = false;
    private bool isMoving = false;

    // Update is called once per frame
    void Update()
    {
        #region Player control

        //Camera
        float rotation = Input.GetAxis("Mouse X");
        transform.Rotate(0, 3.0f * rotation, 0);

        float updown = Input.GetAxis("Mouse Y") * 3.0f;

        if((y+updown) > 180|| (y + updown) < 340)
        {
            updown = 0;
        }
        y += updown;

        Camera.main.transform.RotateAround(transform.position, transform.right, updown);
        Camera.main.transform.LookAt(transform);
        //cinemachine.transform.RotateAround(transform.position, transform.right, updown);
       // cinemachine.transform.LookAt(transform);



        // Moving
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
      
        animator.SetFloat("VelocityX", horizontal, 0.1f, Time.deltaTime);
        animator.SetFloat("VelocityZ", vertical, 0.1f, Time.deltaTime);
        verticalVelocity += Physics.gravity.y * Time.deltaTime;

       
         //jump
        if(Input.GetButton("Jump") && characterController.isGrounded)
        {
            verticalVelocity = 3.0f;
        }

        //transform.Rotate(Vector3.up, horizontal * turnSpeed * Time.deltaTime);
        if(vertical != 0 || horizontal !=0)
        {
            forwardSpeed = (vertical > 0) ? moveSpeed_Forward : moveSpeed_Backward;
            lateralSpeed = 2.0f;
           
        }
            Vector3 movement = new Vector3(horizontal * lateralSpeed, verticalVelocity, vertical * forwardSpeed);
            movement = transform.rotation * movement;
            characterController.Move(movement * Time.deltaTime);

        //Running
        isMoving = Input.GetKey(KeyCode.W);
        isRunning = Input.GetKey(KeyCode.LeftShift);

        if (isRunning && isMoving)
        {
            moveSpeed_Forward = 7.0f;
            animator.SetBool("IsRun", isRunning);
            isRunning = false;
        }
        else
        {
            isRunning = false;
            moveSpeed_Forward = original_Speed;
            animator.SetBool("IsRun", isRunning);
        }
        
        //Crouching
        isCrouching = Input.GetKey(KeyCode.LeftControl);
        if (isCrouching)
        { 
            Crouch();
            forwardSpeed -= 1.0f;
            lateralSpeed -= 1.0f;
            animator.SetBool("IsCrouch", isCrouching);
            isCrouching = false;
        }
        else
        {
            isCrouching = false;
            goUp();
            animator.SetBool("IsCrouch", isCrouching);
            
        }
        #endregion

        #region Menu Control
        // take damage
        //if(Input.GetKey(KeyCode.Space))
        //TakeDamage(20);
        calculateProgress();

        //Restart the game
        if (currentHealth <= 0|| transform.position.y < -1)
        {
            Debug.Log("restart");
            FindObjectOfType<GameManager>().EndGame();
        }

        // Completed the game

        if(currentProgress >= 95)
        {
            FindObjectOfType<GameComplete>().GameCompleted();
        }

        #endregion
    }

    private void OnTriggerEnter(Collider other)
    {
       if(other.gameObject.tag == "HAND_PUNCH")
        {
            TakeDamage(15);
        }
    }
    private void calculateProgress()
    {
        float dis_P1toP2 = Vector3.Distance(pose_1.position, pose_2.position);
        float dis_P2toP3 = Vector3.Distance(pose_2.position, pose_3.position);


        float curretpos_wholesector = Vector3.Distance(transform.position, pose_1.position)
            + Vector3.Distance(transform.position, pose_3.position);
        float dis_currtoP3 = Vector3.Distance(transform.position, pose_3.position);

        if ((curretpos_wholesector / (dis_P1toP2 + dis_P2toP3)) > 1.2)
        {
            //current change is 0
            
        }
        else {
             int precent =(int) (((dis_P2toP3 + dis_P1toP2 -dis_currtoP3) / (dis_P2toP3 + dis_P1toP2)) * 100);
             UpdateProgress(precent);
             
        }
       
 

    }

    private void UpdateProgress(int progress)
    {
        currentProgress = progress;
        progressBar.SetProgress(progress);
    }

    private void TakeDamage(int damage)
    {
        currentHealth -= damage;
        healthBar.SetHealth(currentHealth);
    }

    void Crouch()
    {
        characterController.height = crouchingHeight;
    }

    void goUp()
    {
        characterController.height = characterHeight;
    }

}



