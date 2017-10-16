#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "AntisocialDLL.h"
#include "Time.h"


using antisocial::Time;

namespace antisocial {

	class
	#ifdef __WIN32__
	ANTISOCIAL_API
	#endif // __WIN32__
	Window
	{
	public:
		Window(const std::string title, int width, int height);
		~Window();

		bool IsClosed();
		void update();
		void clear(float r, float g, float b, float a);
		int getWidth();
		int getHeight();
		void setCursor(bool show);
		void setIcon(const std::string path);
		GLFWwindow* getContext() const { return _window; };

		bool isCursorActive();
		bool isMinimized();
		void close();

		void enableVSYNC(bool enable);
		void setFullScreen(bool doSet);
		void setResizable(bool resizable);

	private:
		bool init();
		friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend void window_iconify_callback(GLFWwindow* window, int iconified);
		friend void error_callback(int error, const char* description);

	private:
		GLFWwindow* _window;

		std::string _title;
		int _height;
		int _width;
		bool _cursorActive;
		bool _minimized;
		bool _isFullScreen;

		int _originalHeight;
		int _originalWidth;
	};

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void error_callback(int error, const char* description);

}

#endif // WINDOW_H
