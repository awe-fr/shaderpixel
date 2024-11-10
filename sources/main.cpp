#include "./../headers/main.h"

int main (void) {
	WindowApp *App = new WindowApp();
	Player *player = new Player();
	// test
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint basicID = LoadShaders("./shaders/basic.vert", "./shaders/basic.frag");
	glUseProgram(basicID);
	// test
	while (App->isClosed() == false) {
		//test
		glBindVertexArray(VAO);
		// 1 time needed ?
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLuint ProjectionID = glGetUniformLocation(basicID, "Projection");
		GLuint ViewID = glGetUniformLocation(basicID, "View");
		GLuint ModelID = glGetUniformLocation(basicID, "Model");
		//except that
		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &player->getProjection()[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &player->getView()[0][0]);
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//except that
		
		glDisableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 1 time needed ?
		glBindVertexArray(0);
		//test
	}

	delete App;
	return 0;
}