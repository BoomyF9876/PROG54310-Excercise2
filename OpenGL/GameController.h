#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Font.h"
#include "Camera.h"
#include "TextController.h"

class GameController
{
public:
	static GameController& GetInstance()
	{
		static GameController instance;
		return instance;
	}

	void Initialize();
	void RunGame();
	void Load();

	Shader* GetShader(const char* shaderName)
	{
		auto itr = shaders.find(shaderName);
		assert(itr != shaders.end());
		return itr->second;
	}

	Font* GetFont(const char* fontName)
	{
		auto itr = fonts.find(fontName);
		assert(itr != fonts.end());
		return itr->second;
	}

	Mesh* GetLight()
	{
		if (lights.size() > 0)
		{
			return lights.front();
		}
		return nullptr;
	}

	void RenderMesh(std::string meshName);
	void RenderMouseEventListener(Mesh* mesh, GLFWwindow* window, std::string meshKey, std::string shaderKey, std::string displayText);

private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Font*> fonts;

	std::map<std::string, Mesh*> meshes;
	std::list<Mesh*> lights;
	std::list<Mesh*> tempMeshes;

	TextController* textController = nullptr;
	Camera* camera = nullptr;

	int meshCount = 100;
	json::JSON cubeJSON;
	GLuint vao;

	inline explicit GameController() = default;
	inline ~GameController() = default;
	inline explicit GameController(GameController const&) = delete;
	inline GameController& operator=(GameController const&) = delete;
};

#endif

