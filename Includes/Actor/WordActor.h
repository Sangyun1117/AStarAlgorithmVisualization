#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

// 전방 선언.
class Level;
class Engine_API WordActor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(WordActor, RTTI)

public:
	WordActor(const wchar_t *image, Color color, const Vector2& position );
	virtual ~WordActor();

	// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
	virtual void Tick(float deltaTime);

	// 그리기 함수.
	virtual void Render();

	// 위치 설정/값 읽는 함수.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	void SetColor(Color newColor);
	Vector2 GetPosition() const;

protected:
	// 개체의 위치.
	Vector2 position;
	const wchar_t *image;
	Color color;
};