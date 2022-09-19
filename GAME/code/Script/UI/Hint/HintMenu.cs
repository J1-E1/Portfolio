using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HintMenu : MonoBehaviour
{
    public GameObject hintMenuUI;
    public Text crouchingText;
    public Text levelHintText;

    public bool iscrouch = false;
    public bool islevelHint = false;
    void Update()
    {
       if(iscrouch )
        {
            hintMenuUI.SetActive(true);
            crouchingText.gameObject.SetActive(true);
            
        }
          
        else if (islevelHint )
        {
            hintMenuUI.SetActive(true);
            levelHintText.gameObject.SetActive(true);
            
        }
        else
        {
            hintMenuUI.SetActive(false);
            levelHintText.gameObject.SetActive(false);
            crouchingText.gameObject.SetActive(false);

        }
           

    }

    private void CrouchHint()
    {
        crouchingText.gameObject.SetActive(true);
    }


}
