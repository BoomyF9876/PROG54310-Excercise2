#include "GameController.h"
#include "TextController.h"
#include "WindowController.h"
#include "EngineTime.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Font.h"

void GameController::RenderMesh(std::string meshName)
{
    meshes[meshName]->SetRotation(meshes[meshName]->GetRotation() + Time::Instance().DeltaTime() * glm::vec3(0.0f, meshes[meshName]->GetRotationRate(), 0.0f));
    meshes[meshName]->Render(camera->GetProjection() * camera->GetView(), lights, meshCount);
}

void GameController::RenderMouseEventListener(
    OpenGL::ToolWindow^ toolWindow,
    Mesh* mesh,
    GLFWwindow* window,
    std::string meshKey,
    std::string shaderKey,
    std::string displayText
)
{
    double xpos, ypos;
    glm::vec3 cursorPos, displayPos;
    std::string printMsg;
    Resolution res = WindowController::GetInstance().GetResolution();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &xpos, &ypos);

        cursorPos = glm::vec3(
            (xpos - res.width / 2) * Time::Instance().DeltaTime() * 0.01f,
            (res.height / 2 - ypos) * Time::Instance().DeltaTime() * 0.01f,
            0
        );

        mesh->SetPosition(mesh->GetPosition() + cursorPos);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &xpos, &ypos);

        cursorPos = glm::vec3(
            0,
            0,
            (res.height / 2 - ypos) * Time::Instance().DeltaTime() * -0.01f
        );

        mesh->SetPosition(mesh->GetPosition() + cursorPos);
    }

    if (toolWindow->isResetSuzClicked)
    {
        meshes[meshKey]->SetPosition(glm::vec3(0, 0, 0));
        toolWindow->isResetSuzClicked = false;
    }
    meshes[meshKey]->SetShader(shaders[shaderKey]);
    RenderMesh(meshKey);

    displayPos = mesh->GetPosition();
    printMsg = displayText + std::to_string(displayPos.x) + ", " + std::to_string(displayPos.y) + ", " + std::to_string(displayPos.z);
    textController->RenderText(printMsg, 20, 60, 0.5f, { 1.0f, 0.5f, 1.0f });
}

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
    Time::Instance().Initialize();
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
    toolWindow->Show();

    std::string printMsg;
    glm::vec3 newMeshPos;
    Mesh* newCube;
    do {
        Time::Instance().Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (toolWindow->moveLight || toolWindow->cubeToSphere)
        {
            if (toolWindow->isResetLightClicked)
            {
                GetLight()->SetPosition(glm::vec3(0, 0, 0));
                toolWindow->isResetLightClicked = false;
            }
            GetLight()->Render(camera->GetProjection() * camera->GetView(), lights);
        }
        
        if (toolWindow->moveLight) RenderMouseEventListener(toolWindow, GetLight(), window, "Suzanne", "Diffuse", "Light Position: ");
        if (toolWindow->posColor) RenderMouseEventListener(toolWindow, meshes["Suzanne"], window, "Suzanne", "PositionColor", "Suzanne Position: ");

        if (toolWindow->cubeToSphere)
        {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                newMeshPos = glm::vec3(-20 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20);

                newCube = new Mesh();
                newCube->Create(cubeJSON);
                newCube->SetPosition(newMeshPos);
                newCube->SetCameraPosition(camera->GetPosition());

                tempMeshes.push_back(newCube);
            }
            RenderMesh("Sphere");
            auto it = tempMeshes.begin();
            while (it != tempMeshes.end()) {
                if (glm::length((*it)->GetPosition()) > 0.1) {
                    (*it)->SetPosition((*it)->GetPosition() * (1 - Time::Instance().DeltaTime()));
                    (*it)->Render(camera->GetProjection() * camera->GetView(), lights);
                    ++it;
                }
                else {
                    delete (*it);
                    it = tempMeshes.erase(it);
                }
            }
            printMsg = "Total Cubes: " + std::to_string(tempMeshes.size());
            textController->RenderText(printMsg, 20, 60, 0.5f, { 1.0f, 1.0f, 0.0f });
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
    );

    for (auto& mesh : meshes)
    {
        delete mesh.second;
    }

    for (auto& tempMesh : tempMeshes)
    {
        delete tempMesh;
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
    for (auto& meshJSON : document.ObjectRange())
    {
        if (
            meshJSON.first == "Fonts" ||
            meshJSON.first == "TextController"
        ) continue;

        if (meshJSON.first == "Cube") cubeJSON = meshJSON.second;
        else
        {
            Mesh* mesh = new Mesh();
            mesh->Create(meshJSON.second);
            mesh->SetCameraPosition(camera->GetPosition());
            meshes.emplace(meshJSON.first, mesh);
        }
    }

    if (meshes.count("Light")) {
        lights.push_back(meshes["Light"]);
        meshes.erase("Light");
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
