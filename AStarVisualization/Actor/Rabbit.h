//토끼, 경로탐색 알고리즘의 시작점이다.
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Rabbit : public WordActor {
	RTTI_DECLARATIONS(Rabbit, WordActor)
public:
	Rabbit(const Vector2& position);
	//게임루프
	virtual void Tick(float deltaTime) override;
private:

};