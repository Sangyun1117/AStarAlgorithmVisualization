#include "WordActor.h"
#include "Engine.h"

WordActor::WordActor(const wchar_t *image, Color color, const Vector2& position) : image(image), color(color), position(position)
{
}

WordActor::~WordActor()
{
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void WordActor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
void WordActor::Render()
{
	//���ۿ� ����
	Engine::Get().WriteToWcharBuffer(position, image, color, Color::Green);
}


void WordActor::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}
void WordActor::SetPosition(int x, int y) {
	position = { x,y };
}
void WordActor::SetColor(Color newColor)
{
	color = newColor;
}


Vector2 WordActor::GetPosition() const
{
	return position;
}
