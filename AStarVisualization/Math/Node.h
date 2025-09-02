#pragma once

#include <iostream>
#include "Actor/WordActor.h"
#include "Math/Vector2.h"
// ��ǥ �ٷ�� ���� ����ü.
// c++ ��Ģ�� struct/class ���̰� ����.
// ���� ������(������/visibility) struct public/class private �⺻.
// �ڵ� ǥ��(struct - ������ ���� / class ��ü).
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