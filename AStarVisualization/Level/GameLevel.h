// 게임레벨은 게임이 실제 진행되는 핵심적인 레벨입니다.
// 맵 하단의 버튼을 통해 설치할 오브젝트를 고르거나 사용할 휴리스틱 함수를 고를 수 있습니다.
// 맵에 마우스 좌클릭 하면 선택된 오브젝트가 해당 위치에 설치됩니다.
// 토끼와 당근은 맵에 하나만 존재하면 벽은 여러개 존재가능합니다.
// 벽은 마우스 좌클릭 드래그해서 설치 가능하며, 우클릭 드래그로 삭제도 가능합니다.
// Start 버튼을 누르면 정해진 휴리스틱 함수를 이용해 토끼가 장애물을 피해 당근을 먹습니다.
// 토끼가 당근을 먹는데 성공하면 랜덤한 위치에 새로운 당근이 생깁니다.
// 화면 하단 UI의 Count는 탐색한 노드 수, Time은 탐색 시간입니다.
// esc를 누르면 홈레벨로 이동합니다.
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

	bool isPathCheck = false;
	bool isPathPrint = false;
	bool isRun = false;
	bool isPathDelete = false;

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
	//선택된 휴리스틱 함수
	int heuristicSelect = SELECT_EUCLID;
};