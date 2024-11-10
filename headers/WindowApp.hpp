#ifndef WINDOWAPP_HPP
# define WINDOWAPP_HPP

# define WIDTH 1280
# define HEIGHT 720

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