#include "./../headers/main.h"

int main (void) {
	WindowApp *App = new WindowApp();
	Player *player = new Player();
	// test
	std::vector<glm::vec3> vertex;
	vertex.push_back(glm::vec3 {-1.0f, -1.0f, 0.0f});
	vertex.push_back(glm::vec3 {1.0f, -1.0f, 0.0f});
	vertex.push_back(glm::vec3 {0.0f,  1.0f, 0.0f});
	Object *obj = new Object("./models/skull.obj");

	GLuint basicID = LoadShaders("./shaders/basic.vert", "./shaders/basic.frag");
	glUseProgram(basicID);
	GLuint ProjectionID = glGetUniformLocation(basicID, "Projection");
	GLuint ViewID = glGetUniformLocation(basicID, "View");
	GLuint ModelID = glGetUniformLocation(basicID, "Model");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// test
	while (App->isClosed() == false) {
		//test
		App->deltaTime();
		player->computeMovement(App->getWindow(), App->getDeltaTime());
		std::cout << (float)1 / App->getDeltaTime() << std::endl;

		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &player->getProjection()[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &player->getView()[0][0]);
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &obj->getModel()[0][0]);

		glBindVertexArray(obj->getVAO());
		glDrawElements(GL_TRIANGLES, obj->getIBOSize(), GL_UNSIGNED_INT, (void *)0);
		glBindVertexArray(0);
		//test
	}

	delete App;
	return 0;
}