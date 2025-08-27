#pragma once
#include "Engine.h"
#include "Settings/ObjectDefines.h"

class Level; //전방선언
class Game :public Engine {
public:
	Game();
	~Game();
	//레벨 변경 함수
	void ChangeLevel(int changeLevel);
	virtual void CleanUp() override;
	//레벨 종료 함수
	void QuitLevel(int deleteLevel, int nextLevel);
	// Getter 함수
	Level* GetHomeLevel() const { return homeLevel; }
	Level* GetGameLevel() const { return gameLevel; }

private:
	//레벨
	Level* homeLevel = nullptr;
	Level* gameLevel = nullptr;

	int nowLevel = LEVEL_NUM_GAME;
};