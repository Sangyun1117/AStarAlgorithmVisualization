//당근, 경로탐색 알고리즘의 도착지이다.
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Carrot : public WordActor {
	RTTI_DECLARATIONS(Carrot, WordActor)
public:
	Carrot(const Vector2& position);
};