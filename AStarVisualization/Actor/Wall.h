//��, ��� Ž�� �˰����� ��ֹ��̴�.
#pragma once
#include "Actor/WordActor.h"
#include "Settings/ObjectDefines.h"

class Wall : public WordActor {
	RTTI_DECLARATIONS(Wall, WordActor)
public:
	Wall(const Vector2& position);
	//���ӷ���
	virtual void Tick(float deltaTime) override;
private:

};