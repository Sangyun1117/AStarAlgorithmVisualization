// A* ��ã�� �˰����� ó���ϴ� Ŭ����.
#pragma once
#include <vector>
#include <queue>
#include "Actor/WordActor.h"
#include "Node.h"

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
	AStar(int x, int y);
	~AStar();

	// ��� Ž�� �Լ�.
	bool FindPath(
		std::vector<std::vector<WordActor*>>& grid, int heuristicSelect
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
	float CalculateEuclidHeuristic(Node* currentNode, Node* goalNode);
	float CalculateManhattanHeuristic(Node* currentNode, Node* goalNode);
	float CalculateChebyshevHeuristic(Node* currentNode, Node* goalNode);

private:
	// ���� ����Ʈ(�湮�� ����� ���).
	std::vector<Node*> openList;

	// ���� ����Ʈ(�湮�� ����� ���).
	std::vector<std::vector<Node*>> map;

	// ���� ���.
	Node* startNode = nullptr;

	// ��ǥ ���.
	Node* goalNode = nullptr;

	int findCount = 0;

	// �����¿�, �밢�� ���� �� ���.
	std::vector<Direction> euclidDirections =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};
	std::vector<Direction> manhattanDirections =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },
		// �밢�� �̵�.
		//{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};
	std::vector<Direction> chebyshevdirections =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1}, { 1, -1,1}, { -1, 1, 1}, { -1, -1, 1},
		//{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};
public:
	std::queue<WordActor*> resultQueue;
	// ��¿� ��� �迭
	std::vector<Node*> path;

	bool isFindPath = false;
};