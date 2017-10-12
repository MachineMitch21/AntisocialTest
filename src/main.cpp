#include <AntisocialDLL.h>
#include <Windows.h>
#include <Window.h>
#include <Input.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

using antisocial::Window;
using namespace antisocial::input;

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 800, 600);

    Input::updateContext(w.getContext());

    while(!w.IsClosed())
    {
        if (Input::mouseButtonDown(MouseButton::M_LEFT))
        {
            std::cout << "Clicked left mouse button" << std::endl;
        }

        if (Input::keyPressed(KeyCode::K_ESCAPE))
        {
            break;
        }

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        //** RENDER!! **//

        w.update();
    }
    return 0;
}
