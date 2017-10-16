#include <AntisocialDLL.h>
#include <Window.h>
#include <Shader.h>
#include <Texture2D.h>
#include <Input.h>
#include <Time.h>

#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>

using antisocial::Window;
using namespace antisocial::input;
using antisocial::Shader;
using antisocial::Texture2D;
using antisocial::Time;

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 1000, 750);
    Input::updateContext(w.getContext());

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");
    Texture2D bricks("../Data/Images/lightBricks.png");
    Texture2D scarJ("../Data/Images/scarlettjo.png");

    std::vector<float> vertices =
    {
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    GLuint vao, vbo;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 view;
    glm::mat4 projection;

    projection = glm::perspective(45.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

    shader.bind();
    shader.setInteger("tex", 0);
    shader.setInteger("tex2", 1);
    shader.setMatrix4("projection", glm::value_ptr(projection));

    bool drawWireframe = false;
    bool drawPoints = false;
    bool setFullScreen = false;

    std::vector<glm::vec3> positions =
    {
        glm::vec3(-2.0f, 0.0f, -3.0f),
        glm::vec3(2.0f, 0.0f, -1.5f),
        glm::vec3(0.0f, 2.0f, -4.5f),
        glm::vec3(0.0f, -2.0f, -2.5f)
    };

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

        view = glm::translate(view, viewDir * Time::DeltaTime() * 2.0f);
        shader.setMatrix4("view", glm::value_ptr(view));

        shader.setFloat("time", Time::ElapsedTime());

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        for (int i = 0; i < positions.size(); i++)
        {
            glm::mat4 model;

            model = glm::translate(model, positions[i]);
            model = glm::rotate(model, Time::ElapsedTime() * i, glm::vec3(0.0f, 1.0f, 1.0f));

            shader.setMatrix4("model", glm::value_ptr(model));

            bricks.bind(0);
            scarJ.bind(1);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        w.update();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    return 0;
}
