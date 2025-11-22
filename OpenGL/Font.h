#ifndef FONT_H
#define FONT_H

#include "StandardIncludes.h"

class Shader;

struct Character
{
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Font
{
public:
	~Font();

	void Create(json::JSON& jsonData);
	void RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color);

private:
	Shader* shader = nullptr;
	FT_Library library = nullptr;
	FT_Face face = nullptr;
	std::map<char, Character> characters;
	GLuint vertexBuffer = 0;
	glm::mat4 orthoProj = {};

	void Initialize(std::string _fileName, FT_UInt _size);
	void CreateCharacters();
	void AllocateBuffers();
};

#endif