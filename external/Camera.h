#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "AntisocialDLL.h"
#include "Input.h"
#include <math.h>
#include "MathUtils.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Matrix.h"

using namespace antisocial::math;

namespace antisocial
{
    namespace graphics
    {
        enum MOVEMENT_DIRECTION
        {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        class ANTISOCIAL_API Camera
        {
        public:
            Camera(float fov, float x, float y, float z, float aspectRatio, float nearClip, float farClip);
            ~Camera();

            Matrix getViewMatrix();

            void setFOV(float fov);
            void setAspectRatio(float aspectRatio);
            void setNearClip(float nearClip);
            void setFarClip(float farClip);

            float getFOV();
            float getAspectRatio();
            float getNearClip();
            float getFarClip();

            inline Vector3f getPosition() const { return _position; };

            inline Vector3f getFront() const { return _front; };
            inline Vector3f getUp() const { return _up; };
            inline Vector3f getRight() const { return _right; };

            void move(Vector3f direction, float speedMultiplier, float xOffset, float yOffset, float deltaTime, bool constrain);

        private:
            Vector3f _position;
            Vector3f _rotation;
            Vector3f _front;
            Vector3f _up;
            Vector3f _right;
            Vector3f _worldUp;

            float _fov;
            float _aspectRatio;
            float _nearClip;
            float _farClip;

            float _yaw;
            float _pitch;

            float _movementSpeed;
        };
    }

}

#endif // __CAMERA_H__
