#pragma once

#include <vector>
#include <queue>
#include "Actor/WordActor.h"

// A* 길찾기 알고리즘을 처리하는 클래스.
class Node;
class AStar
{
	// 방향 처리를 위한 구조체.
	struct Direction
	{
		// 위치.
		int x = 0;
		int y = 0;

		// 이동 비용.
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();

	// 경로 탐색 함수.
	bool FindPath(
		std::vector<std::vector<WordActor*>>& grid
	);

	void ResetList(Node* startNode, Node* goalNode);
private:

	// 탐색을 마친 후에 경로를 조립해 반환하는 함수.
	// 목표 노드에서 부모 노드를 참조해 시작 노드까지 역추적 하면서 경로를 구함.
	void ConstructPath(Node* goalNode);

	// 탐색하려는 노드가 목표 노드인지 확인.
	bool IsDestination(const Node* node);

	// 그리드 안에 있는지 확인.
	bool IsInRange(int x, int y, const std::vector<std::vector<WordActor*>>& grid);

	// 이미 방문했는지 확인하는 함수.
	bool HasVisited(int x, int y, float gCost);

	// 현재 지점에서 목표 지점까지의 추정 비용 계산 함수.
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	//void DisplayGrid(std::vector<std::vector<int>>& grid);


private:
	// 열린 리스트(방문할 노드의 목록).
	std::vector<Node*> openList;

	// 닫힌 리스트(방문한 노드의 목록).
	std::vector<Node*> closedList;

	// 시작 노드.
	Node* startNode = nullptr;

	// 목표 노드.
	Node* goalNode = nullptr;

	// 상하좌우, 대각선 방향 및 비용.
	std::vector<Direction> directions =
	{
		// 하상우좌 이동.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// 대각선 이동.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};
public:
	std::queue<WordActor*> resultQueue;
	// 출력용 경로 배열
	std::vector<Node*> path;

	bool isFindPath = false;
};