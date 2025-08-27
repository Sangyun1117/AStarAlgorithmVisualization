#include "WordActor.h"
#include "Engine.h"

WordActor::WordActor(const wchar_t *image, Color color, const Vector2& position) : image(image), color(color), position(position)
{
}

WordActor::~WordActor()
{
}

// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
void WordActor::Tick(float deltaTime)
{
}

// 그리기 함수.
void WordActor::Render()
{
	//버퍼에 저장
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
