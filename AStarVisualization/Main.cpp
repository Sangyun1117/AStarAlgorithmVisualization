#include <iostream>
#include "Engine.h"
#include "Game/Game.h"

int main() {
	//메모리릭 검출코드
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.Run();
}