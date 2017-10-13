#include <AntisocialDLL.h>
#include <Windows.h>
#include <Window.h>
#include <Shader.h>
#include <Input.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using antisocial::Window;
using namespace antisocial::input;
using antisocial::Shader;

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 800, 600);
    Input::updateContext(w.getContext());

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");

    std::vector<float> vertices =
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    };

    GLuint vao, vbo;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    shader.bind();

    bool drawWireframe = false;

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

            glPolygonMode(GL_FRONT_AND_BACK, (drawWireframe ? GL_LINE : GL_FILL));
        }

        shader.setFloat("time", glfwGetTime());

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        w.update();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    return 0;
}
