#include "UIElement.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <iostream>
#include <vector>

UIElement::UIElement(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs)
	: imageLink(imageLink), position(position), asciiImages(images), bgs(bgs), fgs(fgs) {
}


UIElement::~UIElement() {

}

void UIElement::Tick(float deltaTime)
{
}

void UIElement::Render() {
	if (position.x >= Engine::Get().GetScreenWidth() || position.y >= Engine::Get().GetScreenHeight())
		return;
	Engine::Get().WriteToBuffer(position, asciiImages, fgs, bgs);
}

void UIElement::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}
void UIElement::SetPosition(int x, int y) {
	position = { x,y };
}
Vector2 UIElement::GetPosition() const
{
	return position;
}

void UIElement::SetOwner(Level* newOwner) {
	owner = newOwner;
}

Level* UIElement::GetOwner()
{
	return owner;
}