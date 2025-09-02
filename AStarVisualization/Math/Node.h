#pragma once

#include <iostream>
#include "Actor/WordActor.h"
#include "Math/Vector2.h"
// 좌표 다루기 위한 구조체.
// c++ 원칙상 struct/class 차이가 없음.
// 접근 한정자(제한자/visibility) struct public/class private 기본.
// 코딩 표준(struct - 데이터 전용 / class 객체).
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