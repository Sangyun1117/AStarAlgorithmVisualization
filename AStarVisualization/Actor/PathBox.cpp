#include "PathBox.h"
#include "Engine.h"
#include "Core/ImageManager.h"
#include "Utils/Utils.h"

PathBox::PathBox(const Vector2& position) : WordActor(L"🟫", Color::Red, position) {

}

void PathBox::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}