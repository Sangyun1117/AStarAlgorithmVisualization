#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

// ���� ����.
class Level;
class Engine_API WordActor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(WordActor, RTTI)

public:
	WordActor(const wchar_t *image, Color color, const Vector2& position );
	virtual ~WordActor();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	void SetColor(Color newColor);
	Vector2 GetPosition() const;

protected:
	// ��ü�� ��ġ.
	Vector2 position;
	const wchar_t *image;
	Color color;
};