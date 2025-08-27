#pragma once
#include "Engine.h"
#include "Settings/ObjectDefines.h"

class Level; //���漱��
class Game :public Engine {
public:
	Game();
	~Game();
	//���� ���� �Լ�
	void ChangeLevel(int changeLevel);
	virtual void CleanUp() override;
	//���� ���� �Լ�
	void QuitLevel(int deleteLevel, int nextLevel);
	// Getter �Լ�
	Level* GetHomeLevel() const { return homeLevel; }
	Level* GetGameLevel() const { return gameLevel; }

private:
	//����
	Level* homeLevel = nullptr;
	Level* gameLevel = nullptr;

	int nowLevel = LEVEL_NUM_GAME;
};