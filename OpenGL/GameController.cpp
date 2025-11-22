#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "EngineTime.h"

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    
    M_ASSERT(glewInit() == GLEW_OK, "Unable");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Load();
}

void GameController::RunGame()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    
    Time::Instance().Initialize();

    do {
        Time::Instance().Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && meshCount < 1000)
        {
            meshCount++;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && meshCount > 1)
        {
            meshCount--;
        }
        
        for (auto& light: lights)
        {
            light->Render(camera->GetProjection() * camera->GetView(), lights);
        }
        
        for (auto& mesh : meshes)
        {
            mesh->SetRotation(mesh->GetRotation() + Time::Instance().DeltaTime() * glm::vec3(0.0f, mesh->GetRotationRate(), 0.0f));
            mesh->Render(camera->GetProjection() * camera->GetView(), lights, meshCount);
        }

        textController->RenderText(std::to_string(Time::Instance().FPS()), 20, 60, 0.5f, {1.0f, 0.5f, 1.0f});

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
    );

    for (auto& mesh : meshes)
    {
        delete mesh;
    }

    for (auto& light: lights)
    {
        delete light;
    }

    for (auto& shader : shaders)
    {
        delete shader.second;
    }

    for (auto& font : fonts)
    {
        delete font.second;
    }

    if (textController != nullptr)
    {
        delete textController;
    }

    delete camera;
}

void GameController::Load()
{
#pragma region Settings
    std::ifstream inputStream("../Assets/settings.json");
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);
#pragma endregion

#pragma region Clear Color
    glm::vec3 ClearColor{ 0, 0, 0 };
    json::JSON& jsonClearColor = Get(document, "ClearColor");
    ClearColor.x = Get(jsonClearColor, "r").ToFloat();
    ClearColor.y = Get(jsonClearColor, "g").ToFloat();
    ClearColor.z = Get(jsonClearColor, "b").ToFloat();
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 0.0f);
#pragma endregion

#pragma region Camera
    float _fov, _near, _far;
    glm::vec3 CameraPosition{ 1, 0, 0 };
    glm::vec3 CameraLookAt{ 0, 0, 0 };
    
    json::JSON& jsonCamera = Get(document, "Camera");
    json::JSON& jsonCameraPos = Get(jsonCamera, "Position");
    CameraPosition.x = Get(jsonCameraPos, "x").ToFloat();
    CameraPosition.y = Get(jsonCameraPos, "y").ToFloat();
    CameraPosition.z = Get(jsonCameraPos, "z").ToFloat();

    json::JSON& jsonCameraLookAt = Get(jsonCamera, "LookAt");
    CameraLookAt.x = Get(jsonCameraLookAt, "x").ToFloat();
    CameraLookAt.y = Get(jsonCameraLookAt, "y").ToFloat();
    CameraLookAt.z = Get(jsonCameraLookAt, "z").ToFloat();

    _fov = Get(jsonCamera, "fov").ToFloat();
    _near = Get(jsonCamera, "near").ToFloat();
    _far = Get(jsonCamera, "far").ToFloat();
    
    if (!_fov) _fov = 45.0f;
    if (!_near) _near = 0.1f;
    if (!_far) _far = 1000.0f;
    
    camera = new Camera(
        WindowController::GetInstance().GetResolution(),
        CameraPosition, CameraLookAt, { 0, 1, 0 },
        _fov, _near, _far
    );
#pragma endregion

#pragma region Shader
    json::JSON& shadersJSON = Get(document, "Shaders");
    for (auto& shaderJSON : shadersJSON.ArrayRange())
    {
        assert(shaderJSON.hasKey("name"));
        assert(shaderJSON.hasKey("vertex"));
        assert(shaderJSON.hasKey("fragment"));
        Shader* shaderColor = new Shader();
        shaderColor->LoadShaders(shaderJSON["vertex"].ToString().c_str(), shaderJSON["fragment"].ToString().c_str());
        shaders.emplace(shaderJSON["name"].ToString().c_str(), shaderColor);
    }
#pragma endregion

#pragma region Scene
    M_ASSERT(document.hasKey("DefaultFile"), "Settings requires a default file");
    std::string defaultFile = document["DefaultFile"].ToString();

    document = LoadJson(defaultFile);
    
    json::JSON& lightsJSON = Get(document, "Lights");
    for (auto& lightJSON : lightsJSON.ArrayRange())
    {
        Mesh* light = new Mesh();
        light->Create(lightJSON);
        light->SetCameraPosition(camera->GetPosition());
        lights.push_back(light);
    }

    json::JSON& meshesJSON = Get(document, "Meshes");
    for (auto& meshJSON : meshesJSON.ArrayRange())
    {
        Mesh* mesh = new Mesh();
        mesh->Create(meshJSON);
        mesh->SetCameraPosition(camera->GetPosition());
        meshes.push_back(mesh);
    }
#pragma endregion

#pragma region Fonts
    if (document.hasKey("Fonts"))
    {
        json::JSON& fontsJSON = document["Fonts"];
        for (auto& fontJSON : fontsJSON.ArrayRange())
        {
            M_ASSERT(fontJSON.hasKey("Name"), "Font requires a name");
            std::string fontName = fontJSON["Name"].ToString();

            M_ASSERT(fontJSON.hasKey("Font"), "Font requires a Font node");

            Font* font = new Font();
            font->Create(fontJSON["Font"]);
            fonts.emplace(fontName, font);
        }
    }
#pragma endregion

#pragma region TextController
    if (document.hasKey("TextController"))
    {
        textController = new TextController();
        textController->Create(document["TextController"]);
    }
#pragma endregion

}
