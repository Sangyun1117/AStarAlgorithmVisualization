//�䳢, ���Ž�� �˰����� �������̴�.
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Rabbit : public WordActor {
	RTTI_DECLARATIONS(Rabbit, WordActor)
public:
	Rabbit(const Vector2& position);
	//���ӷ���
	virtual void Tick(float deltaTime) override;
private:

};