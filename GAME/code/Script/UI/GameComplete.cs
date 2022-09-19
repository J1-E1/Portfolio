using UnityEngine.SceneManagement;
using UnityEngine;

public class GameComplete : MonoBehaviour
{
    public static bool GameIsCompleted = false;

    public GameObject gameCompeleteUI;
  

    // Update is called once per frame
    void Update()
    {
        if(GameIsCompleted )
        {
            GameCompleted();
        }else
        {
            gameCompeleteUI.SetActive(false);
        }
        
    }

    public void GameCompleted()
    {
        gameCompeleteUI.SetActive(true);
        GameIsCompleted = true;
    }
    public void ContinuetheGame()
    {
        gameCompeleteUI.SetActive(false);
        GameIsCompleted = false;
    }

    public void LoadMenu()
    {
        Time.timeScale = 1f;
        SceneManager.LoadScene("Menu");
    }

    public void QuitGame()
    {
        Debug.Log("Quit menu");
        Application.Quit();
    }
}
