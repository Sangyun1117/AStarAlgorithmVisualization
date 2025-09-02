#include "Node.h"

Node::Node(int x, int y, Node* parentNode)
	: position(x, y), parent(parentNode)
{
}
Node::Node(const Vector2& position, Node* parentNode)
	: position(position), parent(parentNode)
{
}

bool Node::operator==(const Node& other) const
{
	return position.x == other.position.x
		&& position.y == other.position.y;
}