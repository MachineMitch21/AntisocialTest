#include <AntisocialDLL.h>
#include <Window.h>

using antisocial::Window;

int main(int argv, char** argc)
{
    HINSTANCE hinstDLL;

    hinstDLL = LoadLibrary("libantisocial.dll");

    if (hinstDLL != NULL)
    {
        Window w("Hello, Antisocial", 800, 600);

        while(!w.IsClosed())
        {
            w.clear(0.1f, 0.1f, 0.1f, 1.0f);

            w.update();
        }
    }
    return 0;
}
