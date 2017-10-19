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
#include <thread>

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

    w.setCursor(true);

    Camera camera(45.0f, 0.0f, 0.0f, 0.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

    std::vector<glm::vec3> mutantVertices;
    std::vector<glm::vec3> mutantNormals;
    std::vector<glm::vec2> mutantUVs;

    ModelLoader::loadObj("../Data/Models/mutant.obj", mutantVertices, mutantNormals, mutantUVs);

    Mesh mutant(mutantVertices, mutantNormals, mutantUVs);

    std::vector<glm::vec3> derrickVertices;
    std::vector<glm::vec3> derrickNormals;
    std::vector<glm::vec2> derrickUVs;

    ModelLoader::loadObj("../Data/Models/derrick.obj", derrickVertices, derrickNormals, derrickUVs);

    Mesh derrick(derrickVertices, derrickNormals, derrickUVs);

    std::vector<glm::vec3> cityVertices;
    std::vector<glm::vec3> cityNormals;
    std::vector<glm::vec2> cityUVs;

    ModelLoader::loadObj("../Data/Models/The City.obj", cityVertices, cityNormals, cityUVs);

    Mesh city(cityVertices, cityNormals, cityUVs);

    // print_std_vector("printing vertices", objVertices);
    // print_std_vector("printing normals", objNormals);
    // print_std_vector("printing uvs", objUVs);

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");
    Texture2D mutantDiffuse("../Data/Images/Mutant_diffuse.png");
    Texture2D derrickDiffuse("../Data/Images/PoliceZombie_diffuse.png");

    Texture2D city1("../Data/Images/ang1.jpg");
    Texture2D city2("../Data/Images/cty1.jpg");
    Texture2D city3("../Data/Images/cty2x.jpg");

    glm::mat4 view;
    glm::mat4 projection;

    GLuint vertexVBO, uvVBO;

    projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

    shader.bind();
    shader.setInteger("tex", 0);
    shader.setInteger("tex2", 1);
    shader.setInteger("tex3", 2);

    bool drawWireframe = false;
    bool drawPoints = false;
    bool setFullScreen = false;

    std::vector<glm::vec3> positions =
    {
        glm::vec3(1.1f, -1.5f, -1.0f),
        glm::vec3(-1.1f, -1.5f, -1.0f),
        glm::vec3(0.0f, -75.0f, 0.0f)

    };

    glm::vec2 oldMousePos = Input::getCurrentCursorPos();

    float verticeOffset = 0.0f;

    while(!w.IsClosed())
    {
        camera.setAspectRatio((float)w.getWidth() / (float)w.getHeight());
        projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());
        shader.setMatrix4("projection", glm::value_ptr(projection));

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
        yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;

        oldMousePos = Input::getCurrentCursorPos();

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

        if (Input::keyPressed(KeyCode::K_UP))
        {
            verticeOffset += .01f;
            if (verticeOffset > 1.0f)
            {
                verticeOffset = 1.0f;
            }
        }

        if (Input::keyPressed(KeyCode::K_DOWN))
        {
            verticeOffset -= .01f;
            if (verticeOffset < 0.0f)
            {
                verticeOffset = 0.0f;
            }
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

        camera.move(camDirection, camSpeedMultiplier, xOffset, yOffset, Time::DeltaTime(), true);
		view = camera.getViewMatrix();
        shader.setMatrix4("view", glm::value_ptr(view));
        shader.setFloat("verticeOffset", verticeOffset);
        shader.setFloat("time", Time::ElapsedTime());

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        for (int i = 0; i < positions.size(); i++)
        {
            glm::mat4 model;

            model = glm::translate(model, positions[i]);
            //model = glm::rotate(model, Time::ElapsedTime(), glm::vec3(0.0f, 1.0f, 1.0f));

            shader.setMatrix4("model", glm::value_ptr(model));

            if (i == 0)
            {
                mutantDiffuse.bind(0);
                mutant.draw();
            }
            else if (i == 1)
            {
                derrickDiffuse.bind(0);
                derrick.draw();
            }
            else if (i == 2)
            {
                city1.bind(0);
                city2.bind(1);
                city3.bind(2);
                city.draw();
            }
        }
        w.update();
    }
    return 0;
}
