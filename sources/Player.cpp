#include "./../headers/Player.hpp"

Player::Player() {
	this->projection = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
	this->view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

glm::mat4 Player::getProjection() {
	return (this->projection);
}

glm::mat4 Player::getView() {
	return (this->view);
}