#include "Wall.h"
#include "Engine.h"
#include "Core/ImageManager.h"
#include "Utils/Utils.h"

Wall::Wall(const Vector2& position) : WordActor(L"🧱", Color::BrightRed, position) {

}

void Wall::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}