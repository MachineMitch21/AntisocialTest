#include <AntisocialDLL.h>
#include <Window.h>
#include <Shader.h>
#include <Texture2D.h>
#include <Input.h>
#include <Time.h>
#include <Vector4f.h>
#include <Mesh.h>
#include <ModelLoader.h>
#include <Camera.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>

using namespace antisocial::input;
using namespace antisocial::math;
using antisocial::Window;
using antisocial::Shader;
using antisocial::Texture2D;
using antisocial::Time;
using antisocial::Mesh;
using antisocial::ModelLoader;
using antisocial::Camera;

void print_std_vector(std::string message, std::vector<glm::vec3> v)
{
    std::cout << message << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i].x << ", " << v[i].y << ", " << v[i].z << std::endl;
    }
}

void print_std_vector(std::string message, std::vector<glm::vec2> v)
{
    std::cout << message << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i].x << ", " << v[i].y << std::endl;
    }
}

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 1000, 750);
    Input::updateContext(w.getContext());

    w.setCursor(false);

    Camera camera(45.0f, 0.0f, 0.0f, 0.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

    std::vector<glm::vec3> objVertices;
    std::vector<glm::vec3> objNormals;
    std::vector<glm::vec2> objUVs;

    ModelLoader::loadObj("../Data/Models/derrick.obj", objVertices, objNormals, objUVs);

    // print_std_vector("printing vertices", objVertices);
    // print_std_vector("printing normals", objNormals);
    // print_std_vector("printing uvs", objUVs);

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");
    Texture2D diffuse("../Data/Images/PoliceZombie_diffuse.png");
    Texture2D normal("../Data/Images/PoliceZombie_normal.png");

    std::vector<float> vertices =
    {
        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f
    };

    Mesh objMesh(objVertices, objNormals, objUVs);

    glm::mat4 view;
    glm::mat4 projection;

    GLuint vertexVBO, uvVBO;

    projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

    shader.bind();
    shader.setInteger("tex", 0);
    // shader.setInteger("tex2", 1);
    shader.setMatrix4("projection", glm::value_ptr(projection));

    bool drawWireframe = false;
    bool drawPoints = false;
    bool setFullScreen = false;

    std::vector<glm::vec3> positions =
    {
        glm::vec3(0.0f, -1.5f, -1.0f)
    };

    glm::vec2 oldMousePos = Input::getCurrentCursorPos();

    float xOffset;
    float yOffset;

    while(!w.IsClosed())
    {
        xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
        yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;

        oldMousePos = Input::getCurrentCursorPos();

        std::cout << xOffset << std::endl;
        std::cout << yOffset << std::endl;

        glm::vec3 camDirection;
        float camSpeedMultiplier = 1.0f;


        if (Input::keyPressed(KeyCode::K_ESCAPE))
        {
            break;
        }

        if (Input::keyDown(KeyCode::C))
        {
            w.setCursor(!w.isCursorActive());
        }

        if (Input::keyPressed(KeyCode::W))
        {
            camDirection += camera.getFront();
        }

        if (Input::keyPressed(KeyCode::S))
        {
            camDirection += -camera.getFront();
        }

        if (Input::keyPressed(KeyCode::A))
        {
            camDirection += -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
        }

        if (Input::keyPressed(KeyCode::D))
        {
            camDirection += glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
        }

        if (Input::keyPressed(KeyCode::Q))
        {
            camDirection += -camera.getUp();
        }

        if (Input::keyPressed(KeyCode::E))
        {
            camDirection += camera.getUp();
        }

        if (Input::keyPressed(KeyCode::LEFT_SHIFT) || Input::keyPressed(KeyCode::RIGHT_SHIFT))
        {
            camSpeedMultiplier = 2.5f;
        }

        if (Input::keyPressed(KeyCode::LEFT_CTRL))
        {
            camSpeedMultiplier = 0.5f;
        }


        if (Input::mouseButtonDown(MouseButton::M_LEFT))
        {
            std::cout << "Clicked left mouse button" << std::endl;
        }


        if (Input::keyDown(KeyCode::V))
        {
            drawWireframe = !drawWireframe;
            drawPoints = false;
            glPolygonMode(GL_FRONT_AND_BACK, (drawWireframe ? GL_LINE : GL_FILL));
        }

        if (Input::keyDown(KeyCode::P))
        {
            drawPoints = !drawPoints;
            drawWireframe = false;
            glPolygonMode(GL_FRONT_AND_BACK, (drawPoints ? GL_POINT : GL_FILL));
        }

        if (Input::keyDown(KeyCode::F11))
        {
            setFullScreen = !setFullScreen;
            w.setFullScreen(setFullScreen);
        }

        glm::vec3 viewDir(0.0f);

        if (Input::keyPressed(KeyCode::K_UP))
        {
            viewDir += glm::vec3(0.0f, 0.0f, 1.0f);
        }

        if (Input::keyPressed(KeyCode::K_DOWN))
        {
            viewDir += glm::vec3(0.0f, 0.0f, -1.0f);
        }

        std::cout << Time::DeltaTime() << std::endl;

        camera.move(camDirection, camSpeedMultiplier, xOffset, yOffset, Time::DeltaTime(), true);
		view = camera.getViewMatrix();
        shader.setMatrix4("view", glm::value_ptr(view));

        shader.setFloat("time", Time::ElapsedTime());

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        for (int i = 0; i < positions.size(); i++)
        {
            glm::mat4 model;

            model = glm::translate(model, positions[i]);
            //model = glm::rotate(model, Time::ElapsedTime(), glm::vec3(0.0f, 1.0f, 1.0f));

            shader.setMatrix4("model", glm::value_ptr(model));

            diffuse.bind(0);
            normal.bind(1);
            objMesh.draw();
        }
        w.update();
    }
    return 0;
}
