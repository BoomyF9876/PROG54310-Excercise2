#include "TextController.h"
#include "GameController.h"
#include "Font.h"

void TextController::Create(json::JSON& jsonData)
{
	M_ASSERT(jsonData.hasKey("Font"), "Font is required");
	font = GameController::GetInstance().GetFont(jsonData["Font"].ToString().c_str());
}

void TextController::RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color)
{
	font->RenderText(_text, _x, _y, _scale, _color);
}
