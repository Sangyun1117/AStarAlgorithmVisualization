#include "AStar.h"
#include "Actor/Wall.h"
#include "Actor/Carrot.h"
#include "Actor/Rabbit.h"
#include "Actor/PathBox.h"
#include "Node.h"
#include <Windows.h>
#include <queue>
#include <algorithm>

AStar::AStar(int x, int y)
{
	map = std::vector<std::vector<Node*>>(y, std::vector<Node*>(x, nullptr));
}

AStar::~AStar()
{

	// 메모리 해제.
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (auto& row : map) {
		for (Node*& node : row) {
			SafeDelete(node);
		}
		row.clear();
	}
	map.clear();

	while (!resultQueue.empty())
	{
		SafeDelete(resultQueue.front());
		resultQueue.pop();
	}


}

bool AStar::FindPath(std::vector<std::vector<WordActor*>>& grid, int heuristicSelect)
{

	// 방문.
	if (openList.empty()) {
		SafeDelete(goalNode);
		goalNode = nullptr;
		return false;
	}

	Node* lowestNode = openList[0];
	for (Node* node : openList)
	{
		if (node->fCost < lowestNode->fCost)
		{
			lowestNode = node;
		}
	}

	// fCost가 가장 낮은 노드를 현재 노드로 설정.
	Node* currentNode = lowestNode;

	// 현재 노드가 목표 노드인지 확인.
	if (IsDestination(currentNode))
	{
		SafeDelete(goalNode);
		goalNode = nullptr;
		// 목표 노드라면, 지금까지의 경로를 계산해서 반환.
		ConstructPath(currentNode);
		return true;
	}

	// 닫힌 목록에 추가. (열린 목록에서는 제거).
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		// 위치 비교.
		if (*openList[ix] == *currentNode)
		{
			// iterator를 활용해 동적 배열에서 노드 제거.
			openList.erase(openList.begin() + ix);
			break;
		}
	}

	// 현재 노드를 닫힌 목록에 추가.
	// 이미 있으면 추가 안하고, 없으면 추가.
	// 방문 했으면 아래 단계 건너뛰기.
	if (currentNode->visited)
	{
		return true;
	}
	currentNode->visited = true;
	map[currentNode->position.y][currentNode->position.x] = currentNode;

	std::vector<Direction> nowDirection;

	// 휴리스틱 비용 계산 함수 호출.
	if (heuristicSelect == SELECT_EUCLID) {
		nowDirection = euclidDirections;
	}
	else if (heuristicSelect == SELECT_MANHATTAN) {
		nowDirection = manhattanDirections;
	}
	else {
		nowDirection = chebyshevdirections;
	}


	// 이웃노드 방문.
	for (const Direction& direction : nowDirection)
	{
		// 다음에 이동할 위치 설정.
		int newX = currentNode->position.x + direction.x;
		int newY = currentNode->position.y + direction.y;

		// 그리드 밖인지 확인.
		if (!IsInRange(newX, newY, grid))
		{
			// 그리드 밖이면 무시.
			continue;
		}

		// 장애물인지 확인.
		if (grid[newY][newX] != nullptr && grid[newY][newX]->Is(Wall::TypeIdClass()))
		{

			continue;
		}
		// 대각선 여부 확인
		if (abs(direction.x) == 1 && abs(direction.y) == 1)
		{
			if (grid[currentNode->position.y][currentNode->position.x + direction.x] != nullptr &&
				grid[currentNode->position.y + direction.y][currentNode->position.x] != nullptr)
			{
				continue;
			}
		}

		// 이미 방문 했어도 무시.
		// 이미 방문했는지 확인하는 함수 호출.
		float gCost = currentNode->gCost + direction.cost;
		if (HasVisited(newX, newY, gCost))
		{
			continue;
		}

		// 방문을 위한 노드 생성.
		// 비용도 계산.
		Node* neighborNode = new Node(newX, newY, currentNode);
		neighborNode->gCost = currentNode->gCost + direction.cost;
		// 휴리스틱 비용 계산 함수 호출.
		if (heuristicSelect == SELECT_EUCLID) {
			neighborNode->hCost = CalculateEuclidHeuristic(neighborNode, goalNode);
		}
		else if (heuristicSelect == SELECT_MANHATTAN) {
			neighborNode->hCost = CalculateManhattanHeuristic(neighborNode, goalNode);
		}
		else {
			neighborNode->hCost = CalculateChebyshevHeuristic(neighborNode, goalNode);
		}

		neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

		// 이웃 노드가 열린 리스트에 있는지 확인.
		Node* openListNode = nullptr;
		for (Node* node : openList)
		{
			if (*node == *neighborNode)
			{
				openListNode = node;
				break;
			}
		}

		// 노드가 목록에 없거나 비용이 싸면, 새 노드 추가.
		if (openListNode == nullptr || openListNode->fCost > neighborNode->fCost)
		{
			// 방문할 노드를 PathBox 값으로 설정.
			//grid[newY][newX] = new PathBox({ newX * WORD_WIDTH, newY });
			resultQueue.push(new PathBox({ newX * WORD_WIDTH, newY }));
			openList.emplace_back(neighborNode);
		}
		else
		{
			SafeDelete(neighborNode);
		}
	}
	return true;
}

void AStar::ConstructPath(Node* goalNode)
{
	// 경로 반환.
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// 지금까지의 경로는 목표 -> 시작 노드 방향.
	// 따라서 이 순서를 뒤집어야 함.
	std::reverse(path.begin(), path.end());

	isFindPath = true;
}

bool AStar::IsDestination(const Node* node)
{
	// 노드가 목표 노드와 위치가 같은지 비교.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<WordActor*>>& grid)
{
	// x, y 범위가 벗어나면 false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// 벗어나지 않았으면 true.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{

	// 열린 리스트나 닫힌 리스트에 이미 해당 노드가 있으면 방문한 것으로 판단.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// 위치가 같고, 비용도 더 크면 방문할 이유 없음.
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	if (map[y][x]!=nullptr && map[y][x]->visited) {
		if (map[y][x]->gCost <= gCost)
			return true;
		else {
			SafeDelete(map[y][x]);
		}
	}

	// 목록에 없다고 확인되면 방문하지 않은 것으로 판단.
	return false;
}

// 유클리드 거리 (직선 거리)
float AStar::CalculateEuclidHeuristic(Node* currentNode, Node* goalNode)
{
	// 단순 거리 계산으로 휴리스틱 비용으로 활용.
	Vector2 diff = currentNode->position - goalNode->position;

	// 대각선 길이 구하기. 
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
	//return (float)(diff.x * diff.x + diff.y * diff.y);
}

// 맨해튼 거리 (상하좌우 이동 전용)
float AStar::CalculateManhattanHeuristic(Node* currentNode, Node* goalNode)
{
	Vector2 diff = currentNode->position - goalNode->position;
	return (float)(std::abs(diff.x) + std::abs(diff.y));
}

// 체비쇼프 거리 (대각선 이동 가능할 때 유리)
float AStar::CalculateChebyshevHeuristic(Node* currentNode, Node* goalNode)
{
	Vector2 diff = currentNode->position - goalNode->position;
	return (float)std::fmax(std::abs(diff.x), std::abs(diff.y));
}


void AStar::ResetList(Node* startNode, Node* goalNode)
{
	//큐 메모리 해제.
	while (!resultQueue.empty())
	{
		SafeDelete(resultQueue.front());
		resultQueue.pop();
	}

	this->startNode = startNode;
	this->goalNode = goalNode;
	if (!openList.empty()) {
		for (Node* node : openList)
		{
			SafeDelete(node);
		}
		openList.clear();
	}
	for (auto& row : map) {
		for (Node*& node : row) {
			SafeDelete(node);
		}
	}

	openList.emplace_back(startNode);

	isFindPath = false;
}
