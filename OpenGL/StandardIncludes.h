#pragma once

#ifndef _STANDARDINCLUDES_H_
#define _STANDARDINCLUDES_H_

#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <cmath>
#include <list>
#include <map>

#define ERROR_INFO 0
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!_cond) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include "json.hpp"
static json::JSON LoadJson(const std::string & _file_name)
{
	std::ifstream inputStream(_file_name);
	std::string str((std::istreambuf_iterator<char>(inputStream)),
		std::istreambuf_iterator<char>());

	return json::JSON::Load(str);
}

static json::JSON Get(json::JSON& _json, const std::string& _key)
{
	if (_json.hasKey(_key)) {
		return _json[_key];
	}
	else
	{
#if ERROR_INFO == 1
		std::string err_msg = "Object does not have key: " + _key;
		M_ASSERT(0, err_msg.c_str());
#elif ERROR_INFO == 0
		json::JSON new_json{};
		return new_json;
#endif
	}
}

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Resolution.h"

#endif
