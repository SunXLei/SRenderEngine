#pragma once
#include "glm/glm.hpp"



enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 60.0f;


class Camera
{
//#define MAX_SPEED 40.0f
//#define ROTATION_SENSITIVITY 0.1f
//#define MAX_FOV 45.0f

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = YAW, float pitch = PITCH);
	~Camera();

	float GetCameraFov();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

private:
	void UpdateCameraVectors();


public:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// Euler Angles
	float m_Yaw;
	float m_Pitch;

	float m_MouseSensitivity;
	float m_MovementSpeed;
	float m_FOV;

	bool m_CanRotate;
};