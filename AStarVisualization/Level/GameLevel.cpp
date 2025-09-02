#include "GameLevel.h"
#include "Game/Game.h"
#include "Core/Engine.h"
#include "Settings/ObjectDefines.h"
#include "Actor/Wall.h"
#include "Actor/PathBox.h"
#include "Core/Core.h"
#include "Math/Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
GameLevel::GameLevel()
{
	//콘솔창 크기 정보를 가져와 맵 생성
	wordActors = std::vector<std::vector<WordActor*>>(GAME_HEIGHT, std::vector<WordActor*>(GAME_WIDTH / WORD_WIDTH, nullptr));
	pathMap = std::vector<std::vector<WordActor*>>(GAME_HEIGHT, std::vector<WordActor*>(GAME_WIDTH / WORD_WIDTH, nullptr));

	aStar = new AStar(wordActors[0].size(), wordActors.size());

	//토끼, 당근 추가
	rabbit = new Rabbit({ 0, 5 });
	wordActors[5][0] = rabbit;

	CarrotRandomRespawn();

	//오브젝트 버튼 기본 문자열
	const wchar_t* startLine = L"🐰 RABBIT [Q]";

	//오브젝트 버튼 중앙 좌표 계산
	int textLength = static_cast<int>(wcslen(startLine));
	int startX = 1;
	int startY = Engine::Get().GetScreenHeight() - 1;

	//오브젝트 버튼 좌표 저장
	rabbitButtonLeftTopXY = { startX, startY };
	rabbitButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 2;
	wallButtonLeftTopXY = { startX, startY };
	wallButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 2;
	carrotButtonLeftTopXY = { startX, startY };
	carrotButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 2;
	startButtonLeftTopXY = { startX, startY };
	startButtonRightBottomXY = { startX + textLength, startY };

	const wchar_t* euclidText = L"Euclid[A]";
	const wchar_t* manhattanText = L"Manhattan[S]";
	const wchar_t* chebyshevText = L"Chebyshev[D]";
	const wchar_t* findText = L"Count: 500";

	//휴리스틱 함수 버튼 
	startX = 1;
	--startY;
	textLength = static_cast<int>(wcslen(euclidText));
	euclidButtonLeftTopXY = { startX, startY };
	euclidButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 1;
	textLength = static_cast<int>(wcslen(manhattanText));
	manhattanButtonLeftTopXY = { startX, startY };
	manhattanButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 1;
	textLength = static_cast<int>(wcslen(chebyshevText));
	chebyshevButtonLeftTopXY = { startX, startY };
	chebyshevButtonRightBottomXY = { startX + textLength, startY };
	startX += textLength + 1;
	textLength = static_cast<int>(wcslen(findText));
	findTextXY = { startX, startY };
	startX += textLength + 1;
	findTimeTextXY = { startX, startY };

}

GameLevel::~GameLevel()
{
	for (auto& row : wordActors) {
		for (auto& wordPtr : row) {
			SafeDelete(wordPtr);
		}
		row.clear();
	}
	wordActors.clear();
	for (auto& row : pathMap) {
		for (auto& pathPtr : row) {
			SafeDelete(pathPtr);
		}
		row.clear();
	}

	pathMap.clear();
	carrot = nullptr;
	rabbit = nullptr;

	SafeDelete(aStar);
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//탐색시간 갱신
	if (isPathCheck || isPathPrint || isRun) {
		findTime += deltaTime;
	}
	//경로 탐색
	if (isPathCheck) {
		bool check = aStar->FindPath(wordActors, heuristicSelect);
		if (!check) { //경로 없음
			isPathCheck = false;
			for (auto& row : pathMap) {
				for (auto& pathPtr : row) {
					SafeDelete(pathPtr); 
				}
			}
		}

		while (!aStar->resultQueue.empty()) {
			WordActor* pb = aStar->resultQueue.front(); aStar->resultQueue.pop();
			if (!pathMap[pb->GetPosition().y][pb->GetPosition().x / WORD_WIDTH]) {
				pathMap[pb->GetPosition().y][pb->GetPosition().x / WORD_WIDTH] = pb;
				++findCount;
			}
			else {
				SafeDelete(pb);
			}
		}
		if (aStar->isFindPath) {//경로 찾았으면 종료하고 경로 출력
			isPathCheck = false;
			isPathPrint = true;
		}
		//}
		return;
	}

	//경로 출력
	if (isPathPrint) {

		for (Node* node : aStar->path) {
			if (pathMap[node->position.y][node->position.x])
				pathMap[node->position.y][node->position.x]->SetColor(Color::Cyan);
		}
		isPathPrint = false;
		isRun = true;
		std::reverse(aStar->path.begin(), aStar->path.end()); //Run에서 앞에서부터 삭제하면 시간복잡도가 크기 때문에 미리 바꿔놈
	}

	//시작점에서 도착점까지 이동
	if (isRun) {
		if (!aStar->path.empty()) {
			int pathX = aStar->path.back()->position.x;
			int pathY = aStar->path.back()->position.y;
			wordActors[rabbit->GetPosition().y][rabbit->GetPosition().x / WORD_WIDTH] = nullptr;
			rabbit->SetPosition(pathX * WORD_WIDTH, pathY);

			wordActors[pathY][pathX] = rabbit;
			if (carrot->GetPosition() == rabbit->GetPosition()) {
				CarrotRandomRespawn();
				for (auto& row : pathMap) {
					for (auto& pathPtr : row) {
						SafeDelete(pathPtr);
					}
				}

			}
			aStar->path.erase(aStar->path.end() - 1);
		}
		else {
			isRun = false;
		}
	}

	//오브젝트 버튼 선택
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(rabbitButtonLeftTopXY, rabbitButtonRightBottomXY))
	{
		nowMouseLevel = SELECT_RABBIT;
	}

	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(wallButtonLeftTopXY, wallButtonRightBottomXY))
	{
		nowMouseLevel = SELECT_WALL;
	}
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(carrotButtonLeftTopXY, carrotButtonRightBottomXY))
	{
		nowMouseLevel = SELECT_CARROT;
	}
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(startButtonLeftTopXY, startButtonRightBottomXY))
	{
		RestartPath();
		isPathCheck = true;
	}

	//휴리스틱 버튼 선택
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(euclidButtonLeftTopXY, euclidButtonRightBottomXY))
	{
		heuristicSelect = SELECT_EUCLID;
	}

	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(manhattanButtonLeftTopXY, manhattanButtonRightBottomXY))
	{
		heuristicSelect = SELECT_MANHATTAN;
	}
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(chebyshevButtonLeftTopXY, chebyshevButtonRightBottomXY))
	{
		heuristicSelect = SELECT_CHEBYSHEV;
	}

	//게임 맵 마우스 좌클릭 (토끼, 당근)
	if (Input::Get().GetMouseLeftDown()) {
		Vector2 nowMousePosition = Input::Get().GetMousePosition();
		int xValue = nowMousePosition.x / WORD_WIDTH;
		int yValue = nowMousePosition.y;
		// --- 범위 체크 ---
		if (xValue < 0 || xValue >= (int)wordActors[0].size()) return;
		if (yValue < 0 || yValue >= (int)wordActors.size()) return;

		if (nowMousePosition.y < GAME_HEIGHT) {
			if (nowMouseLevel == SELECT_CARROT) {
				if (!wordActors[yValue][xValue]) {
					wordActors[carrot->GetPosition().y][carrot->GetPosition().x / WORD_WIDTH] = nullptr;
					carrot->SetPosition({ xValue * WORD_WIDTH, yValue });
					wordActors[yValue][xValue] = carrot;
				}
			}
			else if (nowMouseLevel == SELECT_RABBIT) {
				if (!wordActors[yValue][xValue]) {
					wordActors[rabbit->GetPosition().y][rabbit->GetPosition().x / WORD_WIDTH] = nullptr;
					rabbit->SetPosition({ xValue * WORD_WIDTH, yValue });
					wordActors[yValue][xValue] = rabbit;
				}
			}
		}
	}

	//게임 맵 마우스 좌클릭 드래그 (벽 설치)
	if (Input::Get().GetMouseLeft()) {  // 눌린 상태 감지
		Vector2 nowMousePosition = Input::Get().GetMousePosition();
		int xValue = nowMousePosition.x / WORD_WIDTH;
		int yValue = nowMousePosition.y;

		// 범위 체크
		if (xValue < 0 || xValue >= (int)wordActors[0].size()) return;
		if (yValue < 0 || yValue >= (int)wordActors.size()) return;

		if (nowMousePosition.y < GAME_HEIGHT && nowMouseLevel == SELECT_WALL) {
			if (!wordActors[yValue][xValue]) {
				Wall* w = new Wall({ xValue * WORD_WIDTH, yValue });
				wordActors[yValue][xValue] = w;
			}
		}
	}
	//게임 맵 마우스 우클릭 드래그(벽 삭제)
	if (Input::Get().GetMouseRight()) {  // 눌린 상태 감지
		Vector2 nowMousePosition = Input::Get().GetMousePosition();
		int xValue = nowMousePosition.x / WORD_WIDTH;
		int yValue = nowMousePosition.y;

		// 범위 체크
		if (xValue < 0 || xValue >= (int)wordActors[0].size()) return;
		if (yValue < 0 || yValue >= (int)wordActors.size()) return;

		if (nowMousePosition.y < GAME_HEIGHT && nowMouseLevel == SELECT_WALL) {
			if (wordActors[yValue][xValue]) {
				delete wordActors[yValue][xValue];  // 메모리 해제
				wordActors[yValue][xValue] = nullptr;
			}
		}
	}

	//키보드 입력
	if (Input::Get().GetKeyDown('Q')) {
		nowMouseLevel = SELECT_RABBIT;
	}
	if (Input::Get().GetKeyDown('W')) {
		nowMouseLevel = SELECT_WALL;
	}
	if (Input::Get().GetKeyDown('E')) {
		nowMouseLevel = SELECT_CARROT;
	}
	if (Input::Get().GetKeyDown('R')) {
		RestartPath();
		isPathCheck = true;
	}
	if (Input::Get().GetKeyDown('A')) {
		heuristicSelect = SELECT_EUCLID;
	}
	if (Input::Get().GetKeyDown('S')) {
		heuristicSelect = SELECT_MANHATTAN;
	}
	if (Input::Get().GetKeyDown('D')) {
		heuristicSelect = SELECT_CHEBYSHEV;
	}

	//esc 누르면 홈레벨로 이동
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ChangeLevel(LEVEL_NUM_HOME);
	}
}

void GameLevel::Render()
{
	SettingBackground();

	for (auto pathRow : pathMap) {
		for (WordActor* path : pathRow) {
			if (path != nullptr)
				path->Render();
		}
	}

	for (auto wordRow : wordActors) {
		for (WordActor* word : wordRow) {
			if (word != nullptr)
				word->Render();
		}
	}


	// 메뉴 아이템 렌더링.
	const wchar_t* rabbitText = L"🐰 RABBIT [Q]";
	const wchar_t* wallText = L" 🧱 Wall [W] ";
	const wchar_t* carrotText = L"🥕 CARROT [E]";
	const wchar_t* startText = L"🎮 START [R] ";

	Color buttonTextColor = nowMouseLevel == SELECT_RABBIT ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ rabbitButtonLeftTopXY.x, rabbitButtonLeftTopXY.y },
		rabbitText, buttonTextColor, Color::BrightYellow
	);

	buttonTextColor = nowMouseLevel == SELECT_WALL ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ wallButtonLeftTopXY.x, wallButtonLeftTopXY.y },
		wallText, buttonTextColor, Color::BrightYellow
	);

	buttonTextColor = nowMouseLevel == SELECT_CARROT ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ carrotButtonLeftTopXY.x, carrotButtonLeftTopXY.y },
		carrotText, buttonTextColor, Color::BrightYellow
	);

	buttonTextColor = isPathCheck || isPathPrint || isRun ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ startButtonLeftTopXY.x, startButtonLeftTopXY.y },
		startText, buttonTextColor, Color::BrightYellow
	);

	// 메뉴 아이템 렌더링.
	const wchar_t* euclidText = L"Euclid[A]";
	const wchar_t* manhattanText = L"Manhattan[S] ";
	const wchar_t* chebyshevText = L"Chebyshev[D]";

	buttonTextColor = heuristicSelect == SELECT_EUCLID ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ euclidButtonLeftTopXY.x, euclidButtonRightBottomXY.y },
		euclidText, buttonTextColor, Color::BrightYellow
	);

	buttonTextColor = heuristicSelect == SELECT_MANHATTAN ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ manhattanButtonLeftTopXY.x, manhattanButtonRightBottomXY.y },
		manhattanText, buttonTextColor, Color::BrightYellow
	);

	buttonTextColor = heuristicSelect == SELECT_CHEBYSHEV ? Color::Red : Color::Black;
	Engine::Get().WriteToWcharBuffer(
		{ chebyshevButtonLeftTopXY.x, chebyshevButtonRightBottomXY.y },
		chebyshevText, buttonTextColor, Color::BrightYellow
	);

	//텍스트 UI 렌더링
	wchar_t buffer[32];   // 출력용 임시 버퍼
	// 문자열 포맷팅
	swprintf(buffer, 32, L"Count: %d ", findCount);
	Engine::Get().WriteToWcharBuffer(
		{ findTextXY.x, findTextXY.y },
		buffer, Color::Black, Color::BrightYellow
	);
	wchar_t buffer2[32];   // 출력용 임시 버퍼
	// 문자열 포맷팅
	swprintf(buffer2, 32, L"Time: %.2f", findTime);
	Engine::Get().WriteToWcharBuffer(
		{ findTimeTextXY.x, findTimeTextXY.y },
		buffer2, Color::Black, Color::BrightYellow
	);
}

//월드y값 기준 배경색 세팅
void GameLevel::SettingBackground()
{
	WORD gameColor = BACKGROUND_GREEN;// 초록색 배경
	WORD uiColor = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;// 노란색 배경

	int screenWidth = Engine::Get().GetScreenWidth();
	int screenHeight = Engine::Get().GetScreenHeight();
	int groundLine = GAME_HEIGHT;
	for (int y = 0; y < Engine::Get().GetScreenHeight(); ++y)
	{
		for (int x = 0; x < screenWidth; ++x)
		{
			CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + x];
			buffer.Char.UnicodeChar = ' ';
			buffer.Attributes = y < groundLine ? gameColor : uiColor;
		}

		// 각 줄 끝에 개행 문자 추가.
		CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + screenWidth];
		buffer.Char.UnicodeChar = '\n';
		buffer.Attributes = y < groundLine ? gameColor : uiColor;
	}

	// 마지막에 널 문자 추가.
	CHAR_INFO& buffer = Engine::Get().imageBuffer[(screenWidth)*screenHeight];
	buffer.Char.UnicodeChar = '\0';
	buffer.Attributes = gameColor;
}

//초기화 후 다시 경로 탐색
void GameLevel::RestartPath()
{
	findCount = 0;
	findTime = 0.0f;
	Node* startNode = new Node({ rabbit->GetPosition().x / WORD_WIDTH, rabbit->GetPosition().y });
	Node* goalNode = new Node({ carrot->GetPosition().x / WORD_WIDTH, carrot->GetPosition().y });
	aStar->ResetList(startNode, goalNode);
}

//랜덤한 위치에 당근 생성
void GameLevel::CarrotRandomRespawn()
{
	if (carrot != nullptr)
		delete carrot;

	int x, y;
	do {
		x = rand() % 30;
		y = rand() % 20;
	} while (rabbit->GetPosition().x / WORD_WIDTH == x && rabbit->GetPosition().y == y);

	if (wordActors[y][x] != nullptr) {
		SafeDelete(wordActors[y][x]);
	}
	carrot = new Carrot({ x * WORD_WIDTH, y });
	wordActors[y][x] = carrot;
}
