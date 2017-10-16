#ifndef TIME_H
#define TIME_H

#include "AntisocialDLL.h"

#include <GLFW/glfw3.h>

namespace antisocial
{

    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    Time
    {
    friend class Window;

    public:
        static float ElapsedTime();
        static float DeltaTime();
        static float LastFrame();

    private:
        static float _elapsedTime;
        static float _deltaTime;
        static float _lastFrame;

        static void update_time();
    };

}

#endif // TIME_H
