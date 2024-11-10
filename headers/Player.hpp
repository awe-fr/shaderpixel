#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "./main.h"

class Player {
	private:
		glm::mat4	projection;
		glm::mat4	view;
	public:
		Player();
		glm::mat4 getProjection();
		glm::mat4 getView();
};

#endif