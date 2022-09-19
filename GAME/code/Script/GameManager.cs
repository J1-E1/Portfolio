using UnityEngine;
using UnityEngine.SceneManagement;
public class GameManager : MonoBehaviour
{
   bool gameIsEnded = false;
   public float restartDelay = 1f;
   public void EndGame()
    {
        // game only end once
        if (gameIsEnded == false)
        {
                gameIsEnded = true;
                Debug.Log("Gamer over");

            // delay to call the function
            Invoke("Restart", restartDelay);
    
            
        }
   
    }

    void Restart()
    {

        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

}
