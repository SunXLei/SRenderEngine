#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
	m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_MovementSpeed(SPEED),
	m_MouseSensitivity(SENSITIVITY),
	m_FOV(FOV)
{
	m_Position = position;
	m_WorldUp = up;
	m_Yaw = yaw;
	m_Pitch = pitch;
	m_CanRotate = false;
	UpdateCameraVectors();
}

Camera::~Camera()
{

}

float Camera::GetCameraFov()
{
	return m_FOV;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	if (direction == FORWARD)
		m_Position += m_Front * velocity;
	if (direction == BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == LEFT)
		m_Position -= m_Right * velocity;
	if (direction == RIGHT)
		m_Position += m_Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	m_FOV -= (float)yoffset;
	if (m_FOV < 1.0f)
		m_FOV = 1.0f;
	if (m_FOV > 60.0f)
		m_FOV = 60.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);

	// be careful that m_Front is negative z-axis
	m_Right = glm::cross(m_Front, m_WorldUp);
	m_Up = glm::cross(m_Right, m_Front);
}

