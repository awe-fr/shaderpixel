#ifndef WINDOWAPP_HPP
# define WINDOWAPP_HPP

# include "./main.h"

class WindowApp {
	private:
		GLFWwindow *_window;
		double	_deltaTime;
	public:
		WindowApp();
		~WindowApp();

		bool	isClosed();
		void	deltaTime();

		double	getDeltaTime();
		GLFWwindow	*getWindow();
};

#endif