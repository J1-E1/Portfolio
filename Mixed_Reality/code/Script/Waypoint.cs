using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Waypoint : MonoBehaviour
{
    // to the next point - > path
    public Waypoint previousWaypoint;
    public Waypoint nextWaypoint;

    [Range(0f, 5f)]

    public float width = 1f;

    /// <summary>
    /// return a random waypoint postion 
    /// 
    /// </summary>
    /// <returns> way point towards the position </returns>
    public Vector3 GetPosition()
    {
        Vector3 minBound = transform.position + transform.right * width / 2f; // right half
        Vector3 maxBound = transform.position - transform.right * width / 2f; // left half

        return Vector3.Lerp(minBound, maxBound, Random.Range(0f, 1f));
    }

}
