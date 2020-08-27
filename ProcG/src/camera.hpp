#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

// System headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>


namespace ProcG
{
	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat   movementSpeed = 10.0f,
			GLfloat   mouseSensitivity = 0.005f)
		{
			mPosition = position;
			mMovementSpeed = movementSpeed;
			mMouseSensitivity = mouseSensitivity;

			// Set up the initial view matrix
			updateViewMatrix();
		}

		glm::vec3 getPosition() { return mPosition; }

		glm::mat4 getRotation() { return glm::mat4_cast(inverse(mQuaternion)); }

		glm::mat4 getViewMatrix() { return viewMat; }

		/* Function that keeps track of pressed buttons*/
		void processKeyboardInputs(int key, int action)
		{
			if (key >= 0 && key < 512)
			{
				if (action == GLFW_PRESS)
				{
					pressedKeys[key] = true;
				}
				else if (action == GLFW_RELEASE)
				{
					pressedKeys[key] = false;
				}
			}
		}

		void processMouseButtonInputs(int button, int action)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			{
				isMousePressed = true;
			}
			else
			{
				isMousePressed = false;
				resetMouse = true;
			}
		}

		void processCursorPosInput(double xpos, double ypos)
		{
			if (isMousePressed == false)
				return;

			if (resetMouse)
			{
				lastXPos = xpos;
				lastYPos = ypos;
				resetMouse = false;
			}

			currentYaw = (xpos - lastXPos);
			currentPitch = (ypos - lastYPos);

			lastXPos = xpos;
			lastYPos = ypos;
		}


		/* Update the camera position and view matrix
		`deltaTime` is the time between the current and last frame */
		void updateCamera(GLfloat deltaTime)
		{
			// Extract movement information from the view matrix
			
			glm::vec3 dirX(viewMat[0][0], 0.0f, viewMat[2][0]);
			glm::vec3 dirY(0.0f, viewMat[1][1], 0.0f);
			glm::vec3 dirZ(viewMat[0][2], 0.0f, viewMat[2][2]);
			
			// Alter position in the appropriate direction
			glm::vec3 fMovement(0.0f, 0.0f, 0.0f);

			if (pressedKeys[GLFW_KEY_W])  // forward
				fMovement -= dirZ;

			if (pressedKeys[GLFW_KEY_S])  // backward
				fMovement += dirZ;

			if (pressedKeys[GLFW_KEY_A])  // left
				fMovement -= dirX;

			if (pressedKeys[GLFW_KEY_D])  // right
				fMovement += dirX;

			if (pressedKeys[GLFW_KEY_E])  // vertical up
				fMovement += dirY;

			if (pressedKeys[GLFW_KEY_Q])  // vertical down
				fMovement -= dirY;

			// Make sure movement speed is dependent on framerate
			GLfloat velocity = mMovementSpeed * deltaTime;

			// Update camera position using the appropriate velocity
			mPosition += fMovement * velocity;

			// Update the view matrix based on the new information
			updateViewMatrix();
		}

	private:
		// Disable copying and assignment
		Camera(Camera const &) = delete;
		Camera & operator =(Camera const &) = delete;

		/* Update the view matrix based on the current information */
		void updateViewMatrix()
		{
			// Adjust cursor movement using the specified sensitivity
			currentPitch *= mMouseSensitivity;
			currentYaw *= mMouseSensitivity;

			// Create quaternions given the current pitch and yaw
			glm::quat qPitch = glm::quat(glm::vec3(currentPitch, 0.0f, 0.0f));
			glm::quat qYaw = glm::quat(glm::vec3(0.0f, currentYaw, 0.0f));

			// Reset pitch and yaw values for the current rotation
			currentPitch = 0.0f;
			currentYaw = 0.0f;

			// Update camera quaternion and normalise
			mQuaternion = qPitch *  mQuaternion * qYaw;
			mQuaternion = glm::normalize(mQuaternion);

			// Build rotation matrix using the camera quaternion
			glm::mat4 matRotation = glm::mat4_cast(mQuaternion);

			// Build translation matrix
			glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f), -mPosition);

			// Update view matrix
			viewMat = matRotation * matTranslate;
		}

		glm::quat mQuaternion;
		glm::mat4 viewMat;

		GLfloat currentPitch = 0.0f;
		GLfloat currentYaw = 0.0f;

		// Camera position
		glm::vec3 mPosition;

		// Input states
		GLboolean resetMouse = true;
		GLboolean isMousePressed = false;
		GLboolean pressedKeys[512] = { false };

		// Last cursor position
		GLfloat lastXPos = 0.0f;
		GLfloat lastYPos = 0.0f;

		// Camera settings
		GLfloat mMovementSpeed;
		GLfloat mMouseSensitivity;
	};
}

#endif