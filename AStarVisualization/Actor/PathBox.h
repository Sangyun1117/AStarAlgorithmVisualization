//A* �˰����� ���
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class PathBox : public WordActor {
	RTTI_DECLARATIONS(PathBox, WordActor)
public:
	PathBox(const Vector2& position);
	//���ӷ���
	virtual void Tick(float deltaTime) override;
private:

};