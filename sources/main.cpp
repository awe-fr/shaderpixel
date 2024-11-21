#include "./../headers/main.h"

int main (void) {
	WindowApp *App = new WindowApp();
	Player *player = new Player();
	ObjectList *objectlist = ObjectList::getInstance();
	// test
	askObject("./models/skull.obj", "./models/skull.jpg", 1, 1, 4, 1);

	GLuint basicID = LoadShaders("./shaders/basic.vert", "./shaders/basic.frag");

	glUseProgram(basicID);

	GLuint ProjectionID = glGetUniformLocation(basicID, "Projection");
	GLuint ViewID = glGetUniformLocation(basicID, "View");
	GLuint ModelID = glGetUniformLocation(basicID, "Model");

	GLuint texture = glGetUniformLocation(basicID, "tex");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// test
	while (App->isClosed() == false) {
		//test
		App->deltaTime();
		player->computeMovement(App->getWindow(), App->getDeltaTime());
		std::vector<Object *> objList = objectlist->getList();
		// std::cout << (float)1 / App->getDeltaTime() << std::endl;
		//test
		for (int objCount = objList.size() - 1; objCount >= 0; objCount--) {
			glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &player->getProjection()[0][0]);
			glUniformMatrix4fv(ViewID, 1, GL_FALSE, &player->getView()[0][0]);
			glUniformMatrix4fv(ModelID, 1, GL_FALSE,  &objList[objCount]->getModel()[0][0]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, objList[objCount]->getTexture());
			glUniform1i(texture,0);

			glBindVertexArray(objList[objCount]->getVAO());
			glDrawElements(GL_TRIANGLES, objList[objCount]->getIBOSize(), GL_UNSIGNED_INT, (void *)0);
			glBindVertexArray(0);
		}
	}
	objectlist->cleanup();
	delete objectlist;
	delete App;
	return 0;
}