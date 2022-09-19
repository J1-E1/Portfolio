#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

#include <iostream>
#include "Model_dragon.h"
#include"texture.h"
#include "Model_vertices.h"
#include "camera.h"
#include "FlyThroughCamera.h"
#include "shader.h"
#include "window.h"


#pragma region Location_setting

// light direction variable 
glm::vec3 lightDirection_Spot = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos_Spot = glm::vec3(2.f, 6.f, 7.f);
glm::vec3 lightDirection_Posit = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos_Posit = glm::vec3(2.f, 0.5f, -2.f);

// model position
glm::vec3 obj_1_pos = glm::vec3(1.0f, 0.0f, -4.0f);
glm::vec3 dragon_pos = glm::vec3(-2.0f, 0.0f, -4.0f);
glm::vec3 background_pos = glm::vec3(0.0f, 0.0f, -4.0f);
/* for animation*/
bool swing_up = false;
float swing_angle = 0.0f;

// for dargon bones
std::vector<glm::vec3> spine_vertices;
std::vector<glm::vec3> leg_vertice;
std::vector<glm::vec3> wing_vertice;

#pragma endregion



SCamera Camera;

#pragma region KeyBoard & Mouse Input

void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			lightPos_Spot = Camera.Position;
			lightDirection_Spot = Camera.Front;
		}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)			MoveCamera(Camera, SCamera::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)			MoveCamera(Camera, SCamera::BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)			MoveCamera(Camera, SCamera::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)			MoveCamera(Camera, SCamera::RIGHT);
	
	//swing the sword
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		swing_up = false;

		swing_angle -= 1.0f;
		if (swing_angle <= 0.0f)
			swing_angle = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		swing_up = true;

		swing_angle += 1.0f;
		if (swing_angle >= 102.f)
			swing_angle = 101.f;
	}
	
}


bool firstMouse = true;
float prevMouseX;
float prevMouseY;

void processMouse(GLFWwindow* window, double x, double y)
{
	if (firstMouse)
	{
		prevMouseX = x;
		prevMouseY = y;
		firstMouse = false;
	}

	float dX = x - prevMouseX;
	float dY = y - prevMouseY;

	prevMouseX = x;
	prevMouseY = y;

	OrientCamera(Camera, dX, dY);
}

#pragma endregion

int main(int argc, char** argv)
{
	GLFWwindow* window = CreateGLFWWindow(1440, 720, "CW3");
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, processMouse);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// load bmp
	GLuint texture = setup_texture("jubilee.bmp");
	unsigned int shaderProgram = LoadShader("mvp.vert", "col.frag");
	InitCamera(Camera);
	


	
#pragma region VAO & VBO for Character and Sword
	const int model_dragon_size = 4;
	//model  Charater body  + Charater Arm + Sword + Background + dragon(4 kind of vertices)
	const int numb_model = 1 + 1 + 1 + 1 + model_dragon_size;

	unsigned int VAO[numb_model];
	glGenVertexArrays(numb_model, VAO);
	unsigned int VBO[numb_model];
	glGenBuffers(numb_model, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Background), Background, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CharacterArm), CharacterArm, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Character), Character, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Sword), Sword, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


#pragma region VAO &VBO for dragon
	//Get the bone postion
	getSpine(spine_vertices);
	getLegs(leg_vertice);
	getWings(wing_vertice);


	// for bones
	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bones), bones, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//for leg
	glBindVertexArray(VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bone_leg), bone_leg, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//for head
	glBindVertexArray(VAO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bone_head), bone_head, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// for wings
	glBindVertexArray(VAO[7]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bone_wing), bone_wing, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#pragma endregion


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgram);

#pragma endregion
	
	float angle = 0.f;
	while (!glfwWindowShouldClose(window))
	{

		processKeyboard(window);
		
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#pragma region Ligt,Charter setting

		// Uniform: fot light setting
		// one for spot light
		glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection[0]"), lightDirection_Spot.x, lightDirection_Spot.y, lightDirection_Spot.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightColour[0]"), 1.f, 1.f, 1.f);
		glUniform3f(glGetUniformLocation(shaderProgram, "camPos_spot"), Camera.Position.x, Camera.Position.y, Camera.Position.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightPos[0]"), lightPos_Spot.x, lightPos_Spot.y, lightPos_Spot.z);

		//one for postition light
		glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection[1]"), lightDirection_Posit.x, lightDirection_Posit.y, lightDirection_Posit.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightColour[1]"), 1.f, 1.f, 1.f);
		glUniform3f(glGetUniformLocation(shaderProgram, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightPos[1]"), lightPos_Posit.x, lightPos_Posit.y, lightPos_Posit.z);



		/* Background */
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, background_pos);
		model = glm::scale(model,glm::vec3(6.f, 2.f ,2.f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, Background_size);

		/* Right arm */
		glm::mat4 right_arm = glm::mat4(1.f);
		right_arm = glm::translate(right_arm, obj_1_pos);
		right_arm = glm::scale(right_arm, glm::vec3(0.2f, 0.25f, 0.25f));
		right_arm = glm::translate(right_arm, glm::vec3(1.3f, 1.3f, 0.0f));

		//Rotate: for animation
		// yx ; 30, z:-83 : arm down
		right_arm = glm::rotate(right_arm, glm::radians(37.f), glm::vec3(0.0f, 1.0f, 1.0f));
		right_arm = glm::rotate(right_arm, glm::radians(-83.f), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(right_arm));
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, CharacterArm_size);


		/* Left arm */
		glm::mat4 left_arm = glm::mat4(1.f);
		left_arm = glm::translate(left_arm, obj_1_pos);
		left_arm = glm::scale(left_arm, glm::vec3(0.2f, 0.22f, 0.22f));
		left_arm = glm::rotate(left_arm, glm::radians(180.f), glm::vec3(0.0f, 1.0f, 0.0f));
		left_arm = glm::translate(left_arm, glm::vec3(1.7f, 1.3f, 0.0f) );
		// Rotate: for animation
		left_arm = glm::rotate(left_arm, glm::radians(40.f), glm::vec3(1.0f, 0.0f, 0.f));
		left_arm = glm::rotate(left_arm, glm::radians(32.f), glm::vec3(0.0f, 1.0f, 0.f));
		// key : H 
		left_arm = glm::rotate(left_arm, glm::radians(-swing_angle), glm::vec3(0.0f, 0.0f, 1.f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(left_arm));
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, CharacterArm_size);

		/* Character body */
		glm::mat4 body = glm::mat4(1.f);
		body = glm::translate(body, obj_1_pos);
		body = glm::scale(body, glm::vec3(0.3f, 0.3f, 0.2f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(body));
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, Character_size);// 3: number of vertices

		/* Sword */  
		glm::mat4 sword = glm::mat4(1.f);
		sword = glm::translate(sword, obj_1_pos);
		sword = glm::translate(sword, glm::vec3(-0.97f, 0.357f, 0.2f));
		sword = glm::scale(sword, glm::vec3(0.3f, 0.3f, 0.3f));
		sword = glm::rotate(sword, glm::radians(102.f), glm::vec3(0.f, 1.0f, 0.f));
		sword = glm::rotate(sword, glm::radians(swing_angle), glm::vec3(0.0f, 0.0f, 1.f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(sword));
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, Sword_size);// 3: number of vertices

#pragma endregion



#pragma region Dragon

		/* Dragon spine*/
		for (int i = 0; i < spine_vertices.size(); i++) {
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, dragon_pos);
			model = glm::translate(model, spine_vertices[i]);
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.2f));

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glBindTexture(GL_TEXTURE_2D, texture);
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO[4]);
			glDrawArrays(GL_TRIANGLES, 0, Bones_size);// 3 * 
		}

		/* Dragon leg */
		for (int i = 0; i < leg_vertice.size(); i++) {
			glm::mat4 leg = glm::mat4(1.f);
			leg = glm::translate(leg, dragon_pos);
			leg = glm::translate(leg, leg_vertice[i]);
			leg = glm::scale(leg, glm::vec3(0.3f, 0.3f, 0.2f));
			
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(leg));
			glBindVertexArray(VAO[5]);
			glDrawArrays(GL_TRIANGLES, 0, Leg_size);
		}

		/* Dragon Head */
		glm::mat4 head = glm::mat4(1.f);

		head = glm::translate(head, dragon_pos);
		head = glm::rotate(head, glm::radians(30.0f), glm::vec3(0.f, 0.f, 1.f));
		head = glm::translate(head, glm::vec3(1.3f, 0.35f, 0.0f));
		head = glm::scale(head, glm::vec3(0.3f, 0.3f, 0.2f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(head));

		glBindVertexArray(VAO[6]);
		glDrawArrays(GL_TRIANGLES, 0, Head_size);

		/* Dragon wings */
		for (int i = 0; i < wing_vertice.size(); i++) {
			glm::mat4 wing = glm::mat4(1.f);
			wing = glm::translate(wing, dragon_pos);
			wing = glm::scale(wing, glm::vec3(0.3f, 0.3f, 0.2f));
			wing = glm::rotate(wing, glm::radians(angle), glm::vec3(1.f, 0.f, 1.f));

			//wing animation , angle is between 75 to 0
			angle += deltaAngle;
			if (angle >= 75.f || angle <= 0.0f) {
				deltaAngle = -deltaAngle;
			}

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(wing));
			glBindVertexArray(VAO[7]);
			glDrawArrays(GL_TRIANGLES, 0, Wing_size);



		}

#pragma endregion


#pragma region View and Projection Setting

		glm::mat4 view = glm::mat4(1.f);
		view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)1440 / (float)720, 1.f, 10.f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

#pragma endregion
		

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
