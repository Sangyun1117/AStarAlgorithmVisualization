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

	// �޸� ����.
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

	// �湮.
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

	// fCost�� ���� ���� ��带 ���� ���� ����.
	Node* currentNode = lowestNode;

	// ���� ��尡 ��ǥ ������� Ȯ��.
	if (IsDestination(currentNode))
	{
		SafeDelete(goalNode);
		goalNode = nullptr;
		// ��ǥ �����, ���ݱ����� ��θ� ����ؼ� ��ȯ.
		ConstructPath(currentNode);
		return true;
	}

	// ���� ��Ͽ� �߰�. (���� ��Ͽ����� ����).
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		// ��ġ ��.
		if (*openList[ix] == *currentNode)
		{
			// iterator�� Ȱ���� ���� �迭���� ��� ����.
			openList.erase(openList.begin() + ix);
			break;
		}
	}

	// ���� ��带 ���� ��Ͽ� �߰�.
	// �̹� ������ �߰� ���ϰ�, ������ �߰�.
	// �湮 ������ �Ʒ� �ܰ� �ǳʶٱ�.
	if (currentNode->visited)
	{
		return true;
	}
	currentNode->visited = true;
	map[currentNode->position.y][currentNode->position.x] = currentNode;

	std::vector<Direction> nowDirection;

	// �޸���ƽ ��� ��� �Լ� ȣ��.
	if (heuristicSelect == SELECT_EUCLID) {
		nowDirection = euclidDirections;
	}
	else if (heuristicSelect == SELECT_MANHATTAN) {
		nowDirection = manhattanDirections;
	}
	else {
		nowDirection = chebyshevdirections;
	}


	// �̿���� �湮.
	for (const Direction& direction : nowDirection)
	{
		// ������ �̵��� ��ġ ����.
		int newX = currentNode->position.x + direction.x;
		int newY = currentNode->position.y + direction.y;

		// �׸��� ������ Ȯ��.
		if (!IsInRange(newX, newY, grid))
		{
			// �׸��� ���̸� ����.
			continue;
		}

		// ��ֹ����� Ȯ��.
		if (grid[newY][newX] != nullptr && grid[newY][newX]->Is(Wall::TypeIdClass()))
		{

			continue;
		}
		// �밢�� ���� Ȯ��
		if (abs(direction.x) == 1 && abs(direction.y) == 1)
		{
			if (grid[currentNode->position.y][currentNode->position.x + direction.x] != nullptr &&
				grid[currentNode->position.y + direction.y][currentNode->position.x] != nullptr)
			{
				continue;
			}
		}

		// �̹� �湮 �߾ ����.
		// �̹� �湮�ߴ��� Ȯ���ϴ� �Լ� ȣ��.
		float gCost = currentNode->gCost + direction.cost;
		if (HasVisited(newX, newY, gCost))
		{
			continue;
		}

		// �湮�� ���� ��� ����.
		// ��뵵 ���.
		Node* neighborNode = new Node(newX, newY, currentNode);
		neighborNode->gCost = currentNode->gCost + direction.cost;
		// �޸���ƽ ��� ��� �Լ� ȣ��.
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

		// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
		Node* openListNode = nullptr;
		for (Node* node : openList)
		{
			if (*node == *neighborNode)
			{
				openListNode = node;
				break;
			}
		}

		// ��尡 ��Ͽ� ���ų� ����� �θ�, �� ��� �߰�.
		if (openListNode == nullptr || openListNode->fCost > neighborNode->fCost)
		{
			// �湮�� ��带 PathBox ������ ����.
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
	// ��� ��ȯ.
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// ���ݱ����� ��δ� ��ǥ -> ���� ��� ����.
	// ���� �� ������ ������� ��.
	std::reverse(path.begin(), path.end());

	isFindPath = true;
}

bool AStar::IsDestination(const Node* node)
{
	// ��尡 ��ǥ ���� ��ġ�� ������ ��.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<WordActor*>>& grid)
{
	// x, y ������ ����� false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// ����� �ʾ����� true.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{

	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 ������ �湮�� ������ �Ǵ�.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// ��ġ�� ����, ��뵵 �� ũ�� �湮�� ���� ����.
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

	// ��Ͽ� ���ٰ� Ȯ�εǸ� �湮���� ���� ������ �Ǵ�.
	return false;
}

// ��Ŭ���� �Ÿ� (���� �Ÿ�)
float AStar::CalculateEuclidHeuristic(Node* currentNode, Node* goalNode)
{
	// �ܼ� �Ÿ� ������� �޸���ƽ ������� Ȱ��.
	Vector2 diff = currentNode->position - goalNode->position;

	// �밢�� ���� ���ϱ�. 
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
	//return (float)(diff.x * diff.x + diff.y * diff.y);
}

// ����ư �Ÿ� (�����¿� �̵� ����)
float AStar::CalculateManhattanHeuristic(Node* currentNode, Node* goalNode)
{
	Vector2 diff = currentNode->position - goalNode->position;
	return (float)(std::abs(diff.x) + std::abs(diff.y));
}

// ü����� �Ÿ� (�밢�� �̵� ������ �� ����)
float AStar::CalculateChebyshevHeuristic(Node* currentNode, Node* goalNode)
{
	Vector2 diff = currentNode->position - goalNode->position;
	return (float)std::fmax(std::abs(diff.x), std::abs(diff.y));
}


void AStar::ResetList(Node* startNode, Node* goalNode)
{
	//ť �޸� ����.
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
