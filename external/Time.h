#ifndef TIME_H
#define TIME_H

#include "AntisocialDLL.h"

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

    private:
        static float _elapsedTime;
        static float _deltaTime;
        static float _lastFrame;
    };

}

#endif // TIME_H
