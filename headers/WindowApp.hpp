#ifndef WINDOWAPP_HPP
# define WINDOWAPP_HPP

# include "./main.h"

class WindowApp {
	private:
		GLFWwindow *_window;
	public:
		WindowApp();
		~WindowApp();

		bool isClosed();
};

#endif