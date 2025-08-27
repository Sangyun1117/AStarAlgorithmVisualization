#pragma once

#include <vector>
#include <queue>
#include "Actor/WordActor.h"

// A* ��ã�� �˰����� ó���ϴ� Ŭ����.
class Node;
class AStar
{
	// ���� ó���� ���� ����ü.
	struct Direction
	{
		// ��ġ.
		int x = 0;
		int y = 0;

		// �̵� ���.
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();

	// ��� Ž�� �Լ�.
	bool FindPath(
		std::vector<std::vector<WordActor*>>& grid
	);

	void ResetList(Node* startNode, Node* goalNode);
private:

	// Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�.
	// ��ǥ ��忡�� �θ� ��带 ������ ���� ������ ������ �ϸ鼭 ��θ� ����.
	void ConstructPath(Node* goalNode);

	// Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��.
	bool IsDestination(const Node* node);

	// �׸��� �ȿ� �ִ��� Ȯ��.
	bool IsInRange(int x, int y, const std::vector<std::vector<WordActor*>>& grid);

	// �̹� �湮�ߴ��� Ȯ���ϴ� �Լ�.
	bool HasVisited(int x, int y, float gCost);

	// ���� �������� ��ǥ ���������� ���� ��� ��� �Լ�.
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	//void DisplayGrid(std::vector<std::vector<int>>& grid);


private:
	// ���� ����Ʈ(�湮�� ����� ���).
	std::vector<Node*> openList;

	// ���� ����Ʈ(�湮�� ����� ���).
	std::vector<Node*> closedList;

	// ���� ���.
	Node* startNode = nullptr;

	// ��ǥ ���.
	Node* goalNode = nullptr;

	// �����¿�, �밢�� ���� �� ���.
	std::vector<Direction> directions =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};
public:
	std::queue<WordActor*> resultQueue;
	// ��¿� ��� �迭
	std::vector<Node*> path;

	bool isFindPath = false;
};