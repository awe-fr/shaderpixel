#include "./../headers/Player.hpp"

Player::Player() {
	this->_projection = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
	this->_view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

glm::mat4 Player::getProjection() {
	return (this->_projection);
}

glm::mat4 Player::getView() {
	return (this->_view);
}

void Player::computeMovement(GLFWwindow *window, float deltaTime) {
	static glm::vec3 position{0.0f, 0.0f, 5.0f};
	// std::cout << "x : " << position.x << " y : " << position.y << " z : " << position.z << std::endl;
	static float horizontalAngle = M_PI;
	static float verticalAngle = 0.0f;
	static float speed = 3.0f;
	static float cameraSpeed = 1.5f;

	glm::vec3 direction;
	direction.x = cos(0) * sin(M_PI);
	direction.y = sin(0);
	direction.z = cos(0) * cos(M_PI);

	glm::vec3 right;
	right.x = sin(M_PI - M_PI_2);
	right.y = 0;
	right.z = cos(M_PI - M_PI_2);

	glm::vec3 up;
	up = glm::cross(right, direction);
	// up = vecCross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position = position + ((up * deltaTime) * speed);
		// position = vecAddition(position, vecMultiplication(vecMultiplication(up, this->_deltaTime), speed));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position = position - ((up * deltaTime) * speed);
		// position = vecSubstract(position, vecMultiplication(vecMultiplication(up, this->_deltaTime), speed));
	}

	direction.x = cos(0) * sin(horizontalAngle);
	direction.z = cos(0) * cos(horizontalAngle);

	right.x = sin(horizontalAngle - M_PI_2);
	right.z = cos(horizontalAngle - M_PI_2);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position = position + ((direction * deltaTime) * speed);
		// position = vecAddition(position, vecMultiplication(vecMultiplication(direction, this->_deltaTime), speed));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position = position - ((direction * deltaTime) * speed);
		// position = vecSubstract(position, vecMultiplication(vecMultiplication(direction, this->_deltaTime), speed));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position = position + ((right * deltaTime) * speed);
		// position = vecAddition(position, vecMultiplication(vecMultiplication(right, this->_deltaTime), speed));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position = position - ((right * deltaTime) * speed);
		// position = vecSubstract(position, vecMultiplication(vecMultiplication(right, this->_deltaTime), speed));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		verticalAngle += cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		verticalAngle -= cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		horizontalAngle += cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		horizontalAngle -= cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 30;
	else
		speed = 3;

	direction.x = cos(verticalAngle) * sin(horizontalAngle);
	direction.y = sin(verticalAngle);
	direction.z = cos(verticalAngle) * cos(horizontalAngle);

	right.x = sin(horizontalAngle - M_PI_2);
	right.z = cos(horizontalAngle - M_PI_2);

	up = glm::cross(right, direction);

	this->_view = glm::lookAt(position,position + direction, up);
	// this->_view = viewMat(position, vecAddition(position, direction), up);
}