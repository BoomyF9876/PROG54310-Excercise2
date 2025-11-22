#ifndef _TEXTCONTROLLER_H_
#define _TEXTCONTROLLER_H_

#include "StandardIncludes.h"

class Font;

class TextController
{
public:
	void Create(json::JSON& jsonData);
	void RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color);

private:
	Font* font = nullptr;
};


#endif
