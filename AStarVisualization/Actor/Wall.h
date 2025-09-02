//벽, 경로 탐색 알고리즘의 장애물이다.
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Wall : public WordActor {
	RTTI_DECLARATIONS(Wall, WordActor)
public:
	Wall(const Vector2& position);
	//게임루프
	virtual void Tick(float deltaTime) override;
private:

};