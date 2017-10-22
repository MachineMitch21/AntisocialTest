#include <AntisocialDLL.h>
#include <Window.h>
#include <Shader.h>
#include <Texture2D.h>
#include <Input.h>
#include <Time.h>
#include <Vector3f.h>
#include <Mesh.h>
#include <ModelLoader.h>
#include <Camera.h>
#include <Skybox.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>

using namespace antisocial;
using namespace antisocial::input;

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

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount);

int main(int argv, char** argc)
{
    Window w("Hello, Antisocial", 1000, 750);

    Input::updateContext(w.getContext());
    Input::LookSensitivity = 0.15f;

    w.setCursor(true);

    Camera camera(45.0f, 0.0f, 0.0f, 0.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

    std::string skyboxName = "../Data/Images/skybox/cloudtop/cloudtop_";

    Skybox skybox(  skyboxName + std::string("ft.tga"),
                    skyboxName + std::string("bk.tga"),
                    skyboxName + std::string("up.tga"),
                    skyboxName + std::string("dn.tga"),
                    skyboxName + std::string("rt.tga"),
                    skyboxName + std::string("lf.tga")  );

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

    std::vector<glm::vec3> shuttleVertices;
    std::vector<glm::vec3> shuttleNormals;
    std::vector<glm::vec2> shuttleUVs;

    ModelLoader::loadObj("../Data/Models/cube.obj", shuttleVertices, shuttleNormals, shuttleUVs);

    Mesh shuttle(shuttleVertices, shuttleNormals, shuttleUVs);

    std::cout << "Mutant has " << mutant.getVertices().size() << std::endl;
    std::cout << "Derrick has " << derrick.getVertices().size() << std::endl;
    std::cout << "The City has " << city.getVertices().size() << std::endl;
    std::cout << "The shuttle has " << shuttle.getVertices().size() << std::endl;

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");
    Shader skyboxShader("../Data/Shaders/skybox.vert", "../Data/Shaders/skybox.frag");

    Texture2D mutantDiffuse("../Data/Images/Mutant_diffuse.png");
    Texture2D derrickDiffuse("../Data/Images/PoliceZombie_diffuse.png");

    Texture2D cityTex1("../Data/Images/ang1.jpg");
    Texture2D cityTex2("../Data/Images/cty1.jpg");
    Texture2D cityTex3("../Data/Images/cty2x.jpg");

    glm::mat4 view;
    glm::mat4 projection;

    GLuint vertexVBO, uvVBO;

    projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

    shader.bind();
    shader.setInteger("tex", 0);
    shader.setInteger("tex2", 1);
    shader.setInteger("tex3", 2);
    shader.setVector3("lightPos", 0.0f, 2.0f, 0.0f);
    shader.setVector3("lightColor", 0.25, 0.25, 0.25);
    shader.setFloat("specularStrength", .1f);
    shader.setVector3("ambientColor", .25f, .25f, .25f);
    shader.unbind();

    skyboxShader.bind();
    skyboxShader.setInteger("cubeTex", 0);
    skyboxShader.unbind();

    bool drawWireframe = false;
    bool drawPoints = false;
    bool setFullScreen = false;

    std::vector<glm::vec3> positions =
    {
        glm::vec3(1.1f, -1.5f, -1.0f),
        glm::vec3(-1.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, -40.5f, 0.0f),
        glm::vec3(0.0f, 15.0f, 0.0f)
    };

    glm::vec2 oldMousePos = Input::getCurrentCursorPos();

    float verticeOffset = 0.0f;

    float lastTimeCount = 0.0f;
    int nbFrames = 0;

    float ambientIntensity = 0.0f;

    int modelSelection = 0;


    while(!w.IsClosed())
    {
        camera.setAspectRatio((float)w.getWidth() / (float)w.getHeight());
        projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

        shader.bind();
        shader.setMatrix4("projection", glm::value_ptr(projection));
        shader.setVector3("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        shader.setFloat("ambientIntensity", ambientIntensity);

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

        if (Input::keyPressed(KeyCode::U))
        {
            positions[0].y += 2.5f * Time::DeltaTime();
            std::cout << positions[0].x << ", " << positions[0].y << ", " << positions[0].z << std::endl;
        }

        if (Input::keyPressed(KeyCode::J))
        {
            positions[0].y += -(2.5f * Time::DeltaTime());
            std::cout << positions[0].x << ", " << positions[0].y << ", " << positions[0].z << std::endl;
        }

        if (Input::keyPressed(KeyCode::K))
        {
            positions[1].x += 2.5f * Time::DeltaTime();
            std::cout << positions[1].x << ", " << positions[1].y << ", " << positions[1].z << std::endl;
        }

        if (Input::keyPressed(KeyCode::H))
        {
            positions[1].x += -(2.5f * Time::DeltaTime());
            std::cout << positions[1].x << ", " << positions[1].y << ", " << positions[1].z << std::endl;
        }

        if (Input::mouseButtonDown(MouseButton::M_LEFT))
        {
            std::cout << "Clicked left mouse button" << std::endl;
        }

        if (Input::keyPressed(KeyCode::K_UP))
        {
            ambientIntensity += .01f;
            if (ambientIntensity > 1.0f)
            {
                ambientIntensity = 1.0f;
            }
        }

        if (Input::keyPressed(KeyCode::K_DOWN))
        {
            ambientIntensity -= .01f;
            if (ambientIntensity < 0.0f)
            {
                ambientIntensity = 0.0f;
            }
        }

        if (Input::keyDown(KeyCode::V))
        {
            drawWireframe = !drawWireframe;
            shader.setBool("isWireframe", drawWireframe);
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

        if (Input::keyDown(KeyCode::ZERO))
        {
            modelSelection = 0;
        }

        if (Input::keyDown(KeyCode::ONE))
        {
            modelSelection = 1;
        }

        if (Input::keyDown(KeyCode::TWO))
        {
            modelSelection = 2;
        }

        if (Input::keyDown(KeyCode::N))
        {
            modelSelection = -1;
        }

        camera.move(camDirection, camSpeedMultiplier, xOffset, yOffset, Time::DeltaTime(), true);
		view = camera.getViewMatrix();

        shader.setMatrix4("view", glm::value_ptr(view));
        shader.setFloat("verticeOffset", verticeOffset);
        shader.setFloat("time", Time::ElapsedTime());
        shader.unbind();

        skyboxShader.bind();
        skyboxShader.setFloat("time", Time::ElapsedTime());

        glm::mat4 skyboxModel;
        skyboxModel = glm::translate(skyboxModel, glm::vec3(0.0f));

        skyboxShader.setMatrix4("view", glm::value_ptr(view));
        skyboxShader.setMatrix4("projection", glm::value_ptr(projection));
        skyboxShader.setMatrix4("model", glm::value_ptr(skyboxModel));

        skybox.draw();
        skyboxShader.unbind();

        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        shader.bind();
        shader.setVector3("objectColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 cityModel;
        cityModel = glm::translate(cityModel, positions[2]);

        glm::mat4 mutantModel;
        mutantModel = glm::translate(mutantModel, positions[0]);

        for (int i = 0; i < positions.size(); i++)
        {
            glm::mat4 model;

            if (i != 2 || i != 0)
            {
                model *= mutantModel;
                model = glm::translate(model, positions[i]);
                //model = glm::rotate(model, Time::ElapsedTime(), glm::vec3(0.0f, 1.0f, 1.0f));

                shader.setMatrix4("model", glm::value_ptr(model));

                shader.setBool("usingUnit1", false);
                shader.setBool("usingUnit2", false);
            }

            if (i == 0)
            {
                shader.setMatrix4("model", glm::value_ptr(mutantModel));
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
                shader.setMatrix4("model", glm::value_ptr(cityModel));
                shader.setBool("usingUnit1", true);
                shader.setBool("usingUnit2", true);
                cityTex1.bind(0);
                cityTex2.bind(1);
                cityTex3.bind(2);
                city.draw();
            }
            else if (i == 3)
            {
                cityTex1.bind(0);
                shuttle.draw();
            }
        }
        shader.unbind();

        w.update();
        nbFrames++;
        // printFPSandMilliSeconds(nbFrames, lastTimeCount);
    }
    return 0;
}

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount)
{
	if (Time::ElapsedTime() - lastTimeCount >= 1.0f)
	{
		std::cout << "Milliseconds: " << 1000.0f / nbFrames << std::endl;
		std::cout << "Frames Per Second: " << nbFrames << std::endl;

		nbFrames = 0;
		lastTimeCount += 1.0f;
	}
}
