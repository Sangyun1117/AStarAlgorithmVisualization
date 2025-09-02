//게임레벨은 게임이 실제 진행되는 핵심적인 레벨입니다.
//방향키로 플레이어를 이동시키고 마우스 왼쪽버튼으로 공격,건축 등이 가능합니다.
//숫자키 0~9를 누르면 아이템을 변경합니다.
//esc를 누르면 메뉴레벨로 이동합니다.
#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Actor/Carrot.h"
#include "Actor/Rabbit.h"
#include "Math/AStar.h"
//#include "Actor/Player.h"
#include <vector>
#include <string>
class GameLevel : public Level {
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();
	~GameLevel();

	// 게임 루프 단계별 오버라이드 함수
	virtual void BeginPlay() override; //초기화 시 호출
	virtual void Tick(float deltaTime) override; //매 프레임 호출
	virtual void Render() override; //화면 렌더링

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
	//std::vector<Node*> path;
	bool isPathCheck = false;
	bool isPathPrint = false;
	bool isRun = false;
	bool isPathDelete = false;


	//ui버튼
	//bool isHoverRabbit = false;
	//bool isHoverWall = false;
	//bool isHoverCarrot = false;
	//bool isHoverStart = false;
	Color selectedTextColor = Color::Green;
	Color selectedBagroundColor = Color::Blue;
	//아이템 선택 안됐을 때 색상
	Color unselectedTextColor = Color::White;
	Color unselectedBagroundColor = Color::Gray;
	//UI 위치
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
	int heuristicSelect = SELECT_EUCLID;
};