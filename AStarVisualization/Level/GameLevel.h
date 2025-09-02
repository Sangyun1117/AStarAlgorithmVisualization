// ���ӷ����� ������ ���� ����Ǵ� �ٽ����� �����Դϴ�.
// �� �ϴ��� ��ư�� ���� ��ġ�� ������Ʈ�� ���ų� ����� �޸���ƽ �Լ��� �� �� �ֽ��ϴ�.
// �ʿ� ���콺 ��Ŭ�� �ϸ� ���õ� ������Ʈ�� �ش� ��ġ�� ��ġ�˴ϴ�.
// �䳢�� ����� �ʿ� �ϳ��� �����ϸ� ���� ������ ���簡���մϴ�.
// ���� ���콺 ��Ŭ�� �巡���ؼ� ��ġ �����ϸ�, ��Ŭ�� �巡�׷� ������ �����մϴ�.
// Start ��ư�� ������ ������ �޸���ƽ �Լ��� �̿��� �䳢�� ��ֹ��� ���� ����� �Խ��ϴ�.
// �䳢�� ����� �Դµ� �����ϸ� ������ ��ġ�� ���ο� ����� ����ϴ�.
// ȭ�� �ϴ� UI�� Count�� Ž���� ��� ��, Time�� Ž�� �ð��Դϴ�.
// esc�� ������ Ȩ������ �̵��մϴ�.
#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Actor/Carrot.h"
#include "Actor/Rabbit.h"
#include "Math/AStar.h"
#include <vector>
#include <string>

class GameLevel : public Level {
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();
	~GameLevel();

	// ���� ���� �ܰ躰 �������̵� �Լ�
	virtual void BeginPlay() override; //�ʱ�ȭ �� ȣ��
	virtual void Tick(float deltaTime) override; //�� ������ ȣ��
	virtual void Render() override; //ȭ�� ������

private:
	void SettingBackground();
	void RestartPath();
	void CarrotRandomRespawn();
private:
	AStar* aStar;
	Carrot* carrot = nullptr;
	Rabbit* rabbit = nullptr;
	int nowMouseLevel = SELECT_CARROT;
	std::vector<std::vector<WordActor*>> wordActors;
	std::vector<std::vector<WordActor*>> pathMap;

	bool isPathCheck = false;
	bool isPathPrint = false;
	bool isRun = false;
	bool isPathDelete = false;

	Color selectedTextColor = Color::Green;
	Color selectedBagroundColor = Color::Blue;
	//������ ���� �ȵ��� �� ����
	Color unselectedTextColor = Color::White;
	Color unselectedBagroundColor = Color::Gray;
	//UI ��ġ
	Vector2 rabbitButtonLeftTopXY;
	Vector2 rabbitButtonRightBottomXY;
	Vector2 wallButtonLeftTopXY;
	Vector2 wallButtonRightBottomXY;
	Vector2 carrotButtonLeftTopXY;
	Vector2 carrotButtonRightBottomXY;
	Vector2 startButtonLeftTopXY;
	Vector2 startButtonRightBottomXY;
	Vector2 findTextXY;
	int findCount = 0;
	Vector2 findTimeTextXY;
	float findTime = 0.0f;
	Vector2 euclidButtonLeftTopXY;
	Vector2 euclidButtonRightBottomXY;
	Vector2 manhattanButtonLeftTopXY;
	Vector2 manhattanButtonRightBottomXY;
	Vector2 chebyshevButtonLeftTopXY;
	Vector2 chebyshevButtonRightBottomXY;
	//���õ� �޸���ƽ �Լ�
	int heuristicSelect = SELECT_EUCLID;
};