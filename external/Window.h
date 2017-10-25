#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "AntisocialDLL.h"
#include "Time.h"


using antisocial::Time;

namespace antisocial
{
	class
	#ifdef __WIN32__
	ANTISOCIAL_API
	#endif // __WIN32__
	Window
	{
	public:
		//Constructs a window class, and initializes glfw library
		Window(const std::string title, int width, int height);
		~Window();
		//Checks to see if window is closed and updates time class
		bool IsClosed();
		//Swaps front and back buffers. Checks for events.
		void update();
		/*
		r,g,b, and a set the default color(and alpha) values
		that buffers are set to once they are cleared. Passed values
		must be between 0 and 1. This method also
		clears the color and depth buffers.
		*/
		void clear(float r, float g, float b, float a);
		//Returns the window width
		int getWidth();
		//Returns the window height
		int getHeight();
		//If passed false cursor is disabled, and enabled if passed true
		void setCursor(bool show);
		//Uses image at passed path as the window icon
		void setIcon(const std::string path);
		//Returns the handle to this window context
		GLFWwindow* getContext() const { return _window; };

		//Returns true if the window has been resized this frame
		bool isResized();
		//Returns value of _cursorActive variable
		bool isCursorActive();
		//Returns value of _minimized variable
		bool isMinimized();
		//Closes window associated with this instance
		void close();

		/*
		Sets swap buffer interval to 0(false), or 1(true).
		This effectively enables or disables VSYNC.
		*/
		void enableVSYNC(bool enable);
		//sets full screen
		void setFullScreen(bool doSet);
		//Determines if screen is resizable
		void setResizable(bool resizable);

	private:
		//Initializes glfw and sets resizable to true
		bool init();
		friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend void window_iconify_callback(GLFWwindow* window, int iconified);
		friend void error_callback(int error, const char* description);

	private:
		//Handle to this window context
		GLFWwindow* _window;

		//Window title
		std::string _title;
		//Window height
		int _height;
		//Window width
		int _width;
		//True if window is resized
		bool _isResized;
		//True if cursor is active, false if not
		bool _cursorActive;
		//True if window is minimized, false if not
		bool _minimized;
		//True if window is full screen, false if not
		bool _isFullScreen;

		//Default height and width of window
		int _originalHeight;
		int _originalWidth;
	};

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void error_callback(int error, const char* description);
}

#endif // WINDOW_H
