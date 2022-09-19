using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CompassController : MonoBehaviour
{

    public Transform playertransform;
    public Transform targetTransform;
    float angle;

    Vector3 copdir;

    private void Update()
    {
        copdir = (targetTransform.position - playertransform.position).normalized;
        angle = Vector3.Angle(copdir, playertransform.forward);
        transform.rotation = Quaternion.Euler(transform.eulerAngles.x, transform.eulerAngles.y, angle);
    }

 

}
