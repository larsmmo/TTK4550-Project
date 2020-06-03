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
			GLfloat   movementSpeed = 5.0f,
			GLfloat   mouseSensitivity = 0.005f)
		{
			mPosition = position;
			mMovementSpeed = movementSpeed;
			mMouseSensitivity = mouseSensitivity;

			// Set up the initial view matrix
			updateViewMatrix();
		}

		/* Getter for camera position */
		glm::vec3 getPosition() { return mPosition; }

		/* Getter for camera rotation */
		glm::mat4 getRotation() { return glm::mat4_cast(inverse(mQuaternion)); }

		/* Getter for the view matrix */
		glm::mat4 getViewMatrix() { return matView; }


		/* Handle keyboard inputs from a callback mechanism */
		void processKeyboardInputs(int key, int action)
		{
			// Keep track of pressed/released buttons
			if (key >= 0 && key < 512)
			{
				if (action == GLFW_PRESS)
				{
					keysInUse[key] = true;
				}
				else if (action == GLFW_RELEASE)
				{
					keysInUse[key] = false;
				}
			}
		}


		/* Handle mouse button inputs from a callback mechanism */
		void processLeftMouseButtonInputs(int button, int action)
		{
			// Ensure that the camera only rotates when the left mouse button is
			// pressed
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


		/* Handle cursor position from a callback mechanism */
		void processCursorPosInput(double xpos, double ypos)
		{
			// Do nothing if the left mouse button is not pressed
			if (isMousePressed == false)
				return;

			// There should be no movement when the mouse button is released
			if (resetMouse)
			{
				lastXPos = xpos;
				lastYPos = ypos;
				resetMouse = false;
			}

			// Keep track of pitch and yaw for the current frame
			fYaw = (xpos - lastXPos);
			fPitch = (ypos - lastYPos);
			// Update last known cursor position
			lastXPos = xpos;
			lastYPos = ypos;
		}


		/* Update the camera position and view matrix
		`deltaTime` is the time between the current and last frame */
		void updateCamera(GLfloat deltaTime)
		{
			// Extract movement information from the view matrix
			glm::vec3 dirX(matView[0][0], 0.0f, matView[2][0]);
			glm::vec3 dirY(0.0f, matView[1][1], 0.0f);
			glm::vec3 dirZ(matView[0][2], 0.0f, matView[2][2]);

			// Alter position in the appropriate direction
			glm::vec3 fMovement(0.0f, 0.0f, 0.0f);

			if (keysInUse[GLFW_KEY_W])  // forward
				fMovement += dirZ;

			if (keysInUse[GLFW_KEY_S])  // backward
				fMovement -= dirZ;

			if (keysInUse[GLFW_KEY_A])  // left
				fMovement -= dirX;

			if (keysInUse[GLFW_KEY_D])  // right
				fMovement += dirX;

			if (keysInUse[GLFW_KEY_E])  // vertical up
				fMovement += dirY;

			if (keysInUse[GLFW_KEY_Q])  // vertical down
				fMovement -= dirY;

			// Trick to balance PC speed with movement
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
			fPitch *= mMouseSensitivity;
			fYaw *= mMouseSensitivity;

			// Create quaternions given the current pitch and yaw
			glm::quat qPitch = glm::quat(glm::vec3(fPitch, 0.0f, 0.0f));
			glm::quat qYaw = glm::quat(glm::vec3(0.0f, fYaw, 0.0f));

			// Reset pitch and yaw values for the current rotation
			fPitch = 0.0f;
			fYaw = 0.0f;

			// Update camera quaternion and normalise
			mQuaternion = qYaw * mQuaternion * qPitch;
			mQuaternion = glm::normalize(mQuaternion);

			// Build rotation matrix using the camera quaternion
			glm::mat4 matRotation = glm::mat4_cast(inverse(mQuaternion));

			// Build translation matrix
			glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f), -mPosition);

			// Update view matrix
			matView = matRotation * matTranslate;
		}

		// Private member variables

		// Camera quaternion and frame pitch and yaw
		glm::quat mQuaternion;
		GLfloat fPitch = 0.0f;
		GLfloat fYaw = 0.0f;

		// Camera position
		glm::vec3 mPosition;

		// Variables used for bookkeeping
		GLboolean resetMouse = true;
		GLboolean isMousePressed = false;
		GLboolean keysInUse[512];

		// Last cursor position
		GLfloat lastXPos = 0.0f;
		GLfloat lastYPos = 0.0f;

		// Camera settings
		GLfloat mMovementSpeed;
		GLfloat mMouseSensitivity;

		// View matrix
		glm::mat4 matView;
	};
}

#endif