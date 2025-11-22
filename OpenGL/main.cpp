#include "StandardIncludes.h"
#include "GameController.h"

int main()
{
	GameController::GetInstance().Initialize();
	GameController::GetInstance().RunGame();
}
