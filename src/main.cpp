#include <AntisocialDLL.h>
#include <Windows.h>
#include <Window.h>
#include <Input.h>
#include <fstream>
#include <iostream>

using antisocial::Window;
using namespace antisocial::input;

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 800, 600);
    Input i;

    while(!w.IsClosed())
    {
        if (Input::mouseButtonDown(MouseButton::M_LEFT))
        {
            std::cout << "Clicked left mouse button" << std::endl;
        }

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        w.update();
    }
    return 0;
}
