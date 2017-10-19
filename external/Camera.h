#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "AntisocialDLL.h"
#include "Input.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace antisocial
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

        // *******************************************************************
        // Camera class will not rely on a VECTOR3 of a certain type as of yet
        // since we do not want to keep glm forever.  This constructor will be
        // implemented when our math library is functional.
        // *******************************************************************
        // Camera(float fov, Vector3 position, Vector3 rotation);

        ~Camera();

        glm::mat4 getViewMatrix();

        void setFOV(float fov);
        void setAspectRatio(float aspectRatio);
        void setNearClip(float nearClip);
        void setFarClip(float farClip);

        float getFOV();
        float getAspectRatio();
        float getNearClip();
        float getFarClip();

        inline glm::vec3 getPosition() const { return _position; };

        inline glm::vec3 getFront() const { return _front; };
        inline glm::vec3 getUp() const { return _up; };
        inline glm::vec3 getRight() const { return _right; };

        void move(glm::vec3 direction, float speedMultiplier, float xOffset, float yOffset, float deltaTime, bool constrain);

    private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;

        float _fov;
        float _aspectRatio;
        float _nearClip;
        float _farClip;

        float _yaw;
        float _pitch;

        float _movementSpeed;
    };

}

#endif // __CAMERA_H__
