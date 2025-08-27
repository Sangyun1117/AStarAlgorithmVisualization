#include "Rabbit.h"
#include "Engine.h"
#include "Core/ImageManager.h"
#include "Utils/Utils.h"

Rabbit::Rabbit(const Vector2& position) : WordActor(L"🐰", Color::White, position) {

}

void Rabbit::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}