#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Carrot : public WordActor {
	RTTI_DECLARATIONS(Carrot, WordActor)
public:
	Carrot(const Vector2& position);
};