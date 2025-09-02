//A*알고리즘에서 좌표 다루기 위한 클래스.
#pragma once
#include <iostream>
#include "Actor/WordActor.h"
#include "Math/Vector2.h"


class Node{
public:
	Node(int x, int y, Node* parentNode = nullptr);

	Node(const Vector2& position, Node* parentNode = nullptr);

	bool operator==(const Node& other) const;

public:
	Vector2 position;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parent = nullptr;
	bool visited = false;
};