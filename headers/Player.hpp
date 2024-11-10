#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "./main.h"

class Player {
	private:
		glm::mat4	_projection;
		glm::mat4	_view;
		
	public:
		Player();
		void	computeMovement(GLFWwindow *window, float deltaTime);
		glm::mat4	getProjection();
		glm::mat4	getView();
		
};

#endif