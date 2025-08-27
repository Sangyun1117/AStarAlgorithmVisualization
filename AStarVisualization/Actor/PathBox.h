//경로. 경로탐색
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class PathBox : public WordActor {
	RTTI_DECLARATIONS(PathBox, WordActor)
public:
	PathBox(const Vector2& position);
	//게임루프
	virtual void Tick(float deltaTime) override;
private:

};