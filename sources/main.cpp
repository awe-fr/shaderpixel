#include "./../headers/main.h"

int main (void) {
	WindowApp *App = new WindowApp();

	while (App->isClosed() == false) {
		
	}

	delete App;
	return 0;
}