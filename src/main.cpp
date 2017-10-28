#include <AntisocialDLL.h>
#include <Window.h>
#include <Shader.h>
#include <Texture2D.h>
#include <Input.h>
#include <Time.h>
#include <Vector2f.h>
#include <Vector3f.h>
#include <Vector4f.h>
#include <Matrix.h>
#include <MathUtils.h>
#include <Sprite.h>
#include <Mesh.h>
#include <ModelLoader.h>
#include <Camera.h>
#include <Skybox.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace antisocial;
using namespace antisocial::input;
using namespace antisocial::math;
using namespace antisocial::graphics;

Window w("Hello, Antisocial", 1000, 750);

Vector2f sprite1Pos(0.0f, 1.0f * w.getHeight());
Vector2f sprite2Pos(1.0f * w.getWidth(), 1.0f * w.getHeight());
Vector2f sprite3Pos(1.0f * w.getWidth(), 0.0f);
Vector2f sprite4Pos(0.0f, 0.0f);

float sprite1Width = .1f * w.getWidth();
float sprite1Height = -.1f * w.getHeight();
float sprite2Width = -.1f * w.getWidth();
float sprite2Height = -.1f * w.getHeight();
float sprite3Width = -.1f * w.getWidth();
float sprite3Height = .1f * w.getHeight();
float sprite4Width = .1f * w.getWidth();
float sprite4Height = .1f * w.getHeight();

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount);
void updateSpriteData(Window& w);

int main(int argv, char** argc)
{
    Vector4f col1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4f col2(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4f col3(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4f col4(1.0f, 2.0f, 3.0f, 4.0f);

    Matrix view(1.0f);
    Matrix projection(1.0f);

    Input::updateContext(w.getContext());
    Input::LookSensitivity = 0.15f;

    w.setCursor(true);

    Camera camera(60.0f, 0.0f, 0.0f, 0.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

    std::string skyboxName = "../Data/Images/skybox/stormydays/stormydays_";

    Skybox skybox(  skyboxName + std::string("ft.tga"),
                    skyboxName + std::string("bk.tga"),
                    skyboxName + std::string("up.tga"),
                    skyboxName + std::string("dn.tga"),
                    skyboxName + std::string("rt.tga"),
                    skyboxName + std::string("lf.tga")  );

    Skybox skybox2D("../Data/Images/skybox/skybox_texture.jpg");

    Mesh* mutant    = ModelLoader::loadObj("../Data/Models/mutant.obj");
    Mesh* derrick   = ModelLoader::loadObj("../Data/Models/derrick.obj");
    Mesh* city      = ModelLoader::loadObj("../Data/Models/The City.obj");
    Mesh* cube      = ModelLoader::loadObj("../Data/Models/cube.obj");



    Sprite sprite1(sprite1Pos, sprite1Width, sprite1Height);
    Sprite sprite2(sprite2Pos, sprite2Width, sprite2Height);
    Sprite sprite3(sprite3Pos, sprite3Width, sprite3Height);
    Sprite sprite4(sprite4Pos, sprite4Width, sprite4Height);

    Shader shader("../Data/Shaders/shader.vert", "../Data/Shaders/shader.frag");
    Shader skyboxShader("../Data/Shaders/skybox.vert", "../Data/Shaders/skybox.frag");
    Shader spriteShader("../Data/Shaders/sprite.vert", "../Data/Shaders/sprite.frag");

    Texture2D mutantDiffuse("../Data/Images/Mutant_diffuse.png");
    Texture2D derrickDiffuse("../Data/Images/PoliceZombie_diffuse.png");

    Texture2D cityTex1("../Data/Images/ang1.jpg");
    Texture2D cityTex2("../Data/Images/cty1.jpg");
    Texture2D cityTex3("../Data/Images/cty2x.jpg");

    Texture2D scarJ("../Data/Images/scarlettjo.png");

    shader.bind();
    shader.setInteger("tex", 0);
    shader.setInteger("tex2", 1);
    shader.setInteger("tex3", 2);
    shader.setVector3("lightPos", 0.0f, 2.0f, 0.0f);
    shader.setVector3("lightColor", 0.25, 0.25, 0.25);
    shader.setFloat("specularStrength", .1f);
    shader.setVector3("ambientColor", 1.0f, 1.0f, 1.0f);
    shader.unbind();

    skyboxShader.bind();
    skyboxShader.setInteger("cubeTex", 0);
    skyboxShader.setInteger("cubeTex2D", 1);
    skyboxShader.unbind();

    Vector2f oldMousePos = Input::getCurrentCursorPos();

    float lastTimeCount = 0.0f;
    int nbFrames = 0;

    float ambientIntensity = .75f;

    bool usingCubeMap = false;
    bool drawWireframe = false;
    bool drawPoints = false;
    bool setFullScreen = false;

    std::vector<Vector3f> positions =
    {
        Vector3f(1.1f, -1.5f, -1.0f),
        Vector3f(-1.5f, 0.0f, 0.0f),
        Vector3f(0.0f, -40.5f, 0.0f),
        Vector3f(0.0f, 5.0f, 0.0f)
    };

    MAG_FILTER magFilter = MAG_FILTER::MAG_LINEAR;
    MIN_FILTER minFilter = MIN_FILTER::MIN_LINEAR;

    bool doLinearFilter = true;

    while(!w.IsClosed())
    {
        w.clear(0.1f, 0.1f, 0.1f, 1.0f);

        camera.setAspectRatio((float)w.getWidth() / (float)w.getHeight());
        projection = Matrix::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

        shader.bind();
        shader.setMatrix4("projection", projection.valueOf());
        shader.setVector3("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        shader.setFloat("ambientIntensity", ambientIntensity);

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
        yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;

        oldMousePos = Input::getCurrentCursorPos();

        Vector3f camDirection;
        float camSpeedMultiplier = 1.0f;

        if (Input::keyPressed(KeyCode::K_ESCAPE))
        {
            break;
        }

        if (Input::keyDown(KeyCode::X))
        {
            usingCubeMap = !usingCubeMap;
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
            camDirection += -Vector3f::normalize(Vector3f::cross(camera.getFront(), camera.getUp()));
        }

        if (Input::keyPressed(KeyCode::D))
        {
            camDirection += Vector3f::normalize(Vector3f::cross(camera.getFront(), camera.getUp()));
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

        if (Input::keyDown(KeyCode::T))
        {
            doLinearFilter = !doLinearFilter;

            if (doLinearFilter)
            {
                minFilter = MIN_FILTER::MIN_LINEAR;
                magFilter = MAG_FILTER::MAG_LINEAR;

                std::cout << "Using linear filtering on mutant texture" << std::endl;
            }
            else
            {
                minFilter = MIN_FILTER::MIN_NEAREST;
                magFilter = MAG_FILTER::MAG_NEAREST;

                std::cout << "Using nearest filtering on mutant texture" << std::endl;
            }

            mutantDiffuse.setMinFilter(minFilter);
            mutantDiffuse.setMagFilter(magFilter);
        }

        camera.move(camDirection, camSpeedMultiplier, xOffset, yOffset, Time::DeltaTime(), true);
		view = camera.getViewMatrix();

        shader.setMatrix4("view", view.valueOf());
        shader.setFloat("time", Time::ElapsedTime());
        shader.unbind();

        skyboxShader.bind();
        skyboxShader.setFloat("time", Time::ElapsedTime());

        Matrix skyboxModel(1.0f);
        skyboxModel = Matrix::translate(skyboxModel, camera.getPosition());
        skyboxModel = Matrix::scale(skyboxModel, Vector3f(100.0f, 100.0f, 100.0f));

        skyboxShader.setMatrix4("view", view.valueOf());
        skyboxShader.setMatrix4("projection", projection.valueOf());
        skyboxShader.setMatrix4("model", skyboxModel.valueOf());
        skyboxShader.setBool("usingCubeMap", usingCubeMap);

        if (usingCubeMap)
        {
            skybox.draw();
        }
        else
        {
            skybox2D.draw();
        }
        skyboxShader.unbind();

        shader.bind();
        shader.setVector3("objectColor", 1.0f, 1.0f, 1.0f);

        Matrix cityModel(1.0f);
        cityModel = Matrix::translate(cityModel, positions[2]);

        Matrix mutantModel(1.0f);
        mutantModel = Matrix::translate(mutantModel, positions[0]);
        mutantModel = Matrix::rotate(mutantModel, Vector3f(0.0f, 1.0f, 0.0f), MathUtils::to_radians(Time::ElapsedTime() * 10.0f));

        for (unsigned int i = 0; i < positions.size(); i++)
        {
            Matrix model(1.0f);

            if (i != 2 || i != 0)
            {
                model *= mutantModel;
                model = Matrix::translate(model, positions[i]);

                shader.setMatrix4("model", model.valueOf());

                shader.setBool("usingUnit1", false);
                shader.setBool("usingUnit2", false);
            }

            if (i == 0)
            {
                shader.setMatrix4("model", mutantModel.valueOf());
                mutantDiffuse.bind(0);

                if (mutant)
                    mutant->draw();
            }
            else if (i == 1)
            {
                derrickDiffuse.bind(0);

                if (derrick)
                    derrick->draw();
            }
            else if (i == 2)
            {
                shader.setMatrix4("model", cityModel.valueOf());
                shader.setBool("usingUnit1", true);
                shader.setBool("usingUnit2", true);
                cityTex1.bind(0);
                cityTex2.bind(1);
                cityTex3.bind(2);

                if (city)
                    city->draw();
            }
            else if (i == 3)
            {
                cityTex1.bind(0);

                if (cube)
                    cube->draw();
            }
        }
        shader.unbind();

        projection = Matrix::orthographic(0.0f, (float)w.getWidth(), (float)w.getHeight(), 0.0f, -1.0f, 1.0f);

        if (w.isResized())
        {
            std::cout << "Window is resizing, sprites are adjusting positions and dimensions" << std::endl;
            updateSpriteData(w);

            sprite1.setPosition(sprite1Pos);
            sprite1.setWidth(sprite1Width);
            sprite1.setHeight(sprite1Height);

            sprite2.setPosition(sprite2Pos);
            sprite2.setWidth(sprite2Width);
            sprite2.setHeight(sprite2Height);

            sprite3.setPosition(sprite3Pos);
            sprite3.setWidth(sprite3Width);
            sprite3.setHeight(sprite3Height);

            sprite4.setPosition(sprite4Pos);
            sprite4.setWidth(sprite4Width);
            sprite4.setHeight(sprite4Height);
        }

        spriteShader.bind();
        spriteShader.setMatrix4("projection", projection.valueOf());

        spriteShader.setVector4("color", 1.0f, 0.5f, 0.75f, 0.5f);
        sprite1.draw();

        spriteShader.setVector4("color", 0.5f, 1.0f, 0.75f, 0.5f);
        sprite2.draw();

        spriteShader.setVector4("color", 0.75f, 0.5f, 1.0f, 0.5f);
        sprite3.draw();

        spriteShader.setVector4("color", 0.5f, 0.25f, 0.75f, 0.5f);
        sprite4.draw();

        spriteShader.unbind();

        w.update();
        nbFrames++;
        // printFPSandMilliSeconds(nbFrames, lastTimeCount);
    }

    delete mutant;
    delete derrick;
    delete city;
    delete cube;

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

void updateSpriteData(Window& w)
{
    sprite1Pos = Vector2f(0.0f, 1.0f * w.getHeight());
    sprite2Pos = Vector2f(1.0f * w.getWidth(), 1.0f * w.getHeight());
    sprite3Pos = Vector2f(1.0f * w.getWidth(), 0.0f);
    sprite4Pos = Vector2f(0.0f, 0.0f);

    sprite1Width = .1f * w.getWidth();
    sprite1Height = -.1f * w.getHeight();
    sprite2Width = -.1f * w.getWidth();
    sprite2Height = -.1f * w.getHeight();
    sprite3Width = -.1f * w.getWidth();
    sprite3Height = .1f * w.getHeight();
    sprite4Width = .1f * w.getWidth();
    sprite4Height = .1f * w.getHeight();
}
