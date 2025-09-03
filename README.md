# A*알고리즘 시각화
>Windows Console를 이용해 A* 알고리즘을 시각화해본 프로젝트 입니다.<br>
>마우스 입력을 통해 간편하게 여러 케이스를 테스트해 볼 수 있습니다.<br>
>대표적인 세 가지 휴라스틱 함수를 비교 할 수 있도록 만들어보았습니다.

---

## 🖼️ 데모 / 스크린샷

### 1️⃣ 유클리드 거리<br>
![Image](https://github.com/user-attachments/assets/c511b95d-11b6-4530-9094-a29ad18921da)<br>
### 2️⃣ 맨해튼 거리<br>
![Image](https://github.com/user-attachments/assets/1c6eaa7a-c090-4a80-9ee1-023f8154ae2f)<br>
### 3️⃣ 체비쇼프 거리<br>
![Image](https://github.com/user-attachments/assets/a9fa4cd3-d018-4546-942a-c97243dac4ed)

---

## 🏃🏾A* 알고리즘
![Image](https://github.com/user-attachments/assets/ce68299c-9534-4856-b3a9-1b96c7d01a58)

---

## 🤓 휴리스틱 함수 분석

### 1. 유클리드 거리
- 점과 점 사이 직선 거리 사용
- 제곱근 연산으로 약간 느리지만 가장 여러 상황에서 사용가능한 무난한 방법

### 2. 맨해튼 거리
- 대각선을 고려하지 않고 상하좌우 상황에서 최적의 알고리즘.
- 계산이 더하기, 절댓값 연산이라 빠름.
- 대각선에 사용시 hCost 과대평가로 최단경로를 못찾을 수 있지만 근사치를 빠르게 찾을 수 있다는 이점이 있음.

### 3. 체비쇼프 거리
- 대각선의 cost를 1로 책정하는 알고리즘. 비교 연산으로 빠른 편.
- 대각선의 value가 높아 최대한 대각선으로 이동하고 수직,수평으로 남은거리를 이동하려고 함.
- 대각선 cost가 √2일시 hCost를 과소평가하게됨. 최단경로를 찾을 수는 있지만 필요없는 노드까지 탐색해 비효율적.

---

## ⚙️ 개발 환경

- 개발 도구: Visual Studio 2022  
- 프로그래밍 언어: C++  
- 운영체제: Windows 11

---

## 🛠️ 설치 방법
OS: Windows 콘솔/터미널 환경 필요<br><br>
아래 링크에서 설치 후 Game 폴더의 Game.exe 관리자 권한으로 실행<br>
https://github.com/Sangyun1117/AStarAlgorithmVisualization/releases/download/v1.0.0/AStarAlgorithmVisualization.zip <br>

## 📌 동작 방법
- Q/W/E 또는 UI버튼 클릭으로 생성할 액터를 정합니다. 

- Q는 🐰토끼 입니다. 마우스 좌클릭을 통해 위치를 변경합니다. A* 알고리즘의 시작점이 됩니다.

- W는 🧱벽 입니다. 마우스 좌클릭 드래그를 통해 설치하고 우클릭 드래그로 삭제합니다. A* 알고리즘의 장애물이 됩니다.

- E는 🥕당근 입니다. 마우스 좌클릭을 통해 위치를 변경합니다. A* 알고리즘의 도착점이 됩니다.

- A/S/D 또는 UI버튼 클릭으로 휴리스틱 함수를 정합니다.

- R 또는 UI버튼 클릭으로 알고리즘을 실행 합니다. 토끼에서 시작해 탐색한 영역을 빨간색으로 칠하고 당근을 발견하면 최단경로를 파란색으로 칠합니다.

- 최단경로를 발견하면 토끼는 당근까지 움직이고 당근에 도착하면 새로운 위치에 당근이 재생성 됩니다.

- 하단 UI에 탐색한 영역의 수(Count)와 걸린 시간(Time)

## 📄 프로젝트 문서 (Notion)
[🔗 노션 페이지](https://unmarred-iguanodon-dea.notion.site/A-25a3bd2b36e280eeb0a7c763e3c9fd37?source=copy_link)
