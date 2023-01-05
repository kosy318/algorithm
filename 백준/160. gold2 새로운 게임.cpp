#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>

using namespace std;

struct Node {
	int num;
	int x, y;
	int dir;

	Node(int num, int x, int y, int dir) :num{ num }, x{ x }, y{ y }, dir{ dir }{};
};

int N; // 체스판 크기
int K; // 사용하는 말의 개수
int color[12][12]; // 체스판; 0: 흰색, 1: 빨간색, 2:파란색
int board[12][12]; // 가장 아래에 놓인 체스말의 번호 표시
map<int, vector<Node>> pieces; // 체스말

int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

void print_board() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int move() {
	int turn = 0;

	while (turn <= 1000) {
		set<int> erase;
		turn += 1;
		// 1번부터 K번 말까지 순서대로 이동(위에 올려져 있는 말도 함께 이동, 가장 아래에 있는 말만 이동 가능)
		for (auto& piece : pieces) {
			int num = piece.second[0].num;
			int x = piece.second[0].x;
			int y = piece.second[0].y;
			int dir = piece.second[0].dir;

			// 다음에 이동하려는 칸
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			// A번 말의 이동하려는 칸이 체스판을 벗어나는 경우이거나 파란색인 경우
			if ((nx < 0 || ny < 0 || nx >= N || ny >= N) || color[nx][ny] == 2) {
				// 이동 방향을 반대로 하고 한 칸 이동하려고 하는데...
				if (dir == 1 || dir == 3)
					dir += 1;
				else dir -= 1;

				// 다음에 이동하려는 칸 반대로 바꿈
				nx = x + dx[dir];
				ny = y + dy[dir];

				// 이동하려는 칸이 파란색인 경우 이동하지 않고 방향만 반대로 바꾼다.
				if ((nx < 0 || ny < 0 || nx >= N || ny >= N) || color[nx][ny] == 2) {
					if (dir == 1 || dir == 3)
						dir += 1;
					else dir -= 1;

					// 방향 바꾸고 끝
					piece.second[0].dir = dir;
					continue;
				}

				// 방향 바꿈
				piece.second[0].dir = dir;
				// 파란색이 아닌 경우 나가서 빨간색인지 흰 색인지 확인
			}

			// A번 말의 이동하려는 칸이 흰색인 경우
			if (color[nx][ny] == 0) {
				// 해당 칸으로 이동하려고 하는데...
				// 이미 말이 있는 경우
				if (board[nx][ny] != 0) {
					// A번 말을 위에 쌓는다(순서대로)
					pieces[board[nx][ny]].insert(pieces[board[nx][ny]].end(), piece.second.begin(), piece.second.end());

					// A번 말이 맨 아래에 있지 않기 때문에 A번 말을 map에서 삭제하기 위해 기록
					erase.insert(num);

					// nx, ny 위치에 맨 아래에 있는 말 번호 바꿈
					num = board[nx][ny];
				}
				else { // 해당 칸이 비어있는 경우
				   // A번 말을 이동시켜준다.
				   // board에서 이동, nx, ny 위치에 맨 아래에 있는 말 번호가 바뀜
					board[nx][ny] = num;

					// A번 말의 정보 수정(위치 이동)
					piece.second[0].x = nx;
					piece.second[0].y = ny;
				}
				// A번 말이 이동했기 때문에 기존 위치에서 제외해준다.
				board[x][y] = 0;
			}
			else if (color[nx][ny] == 1) { // A번 말의 이동하려는 칸이 빨간색인 경우
			   // 해당 칸으로 이동하려고 하는데...
			   // A번 말과 그 위에 있는 모든 말의 쌓여있는 순서를 반대로 바꾼다.
				reverse(piece.second.begin(), piece.second.end());

				// A번 말이 맨 아래에 있지 않기 때문에 A번 말을 map에서 삭제하고
				erase.insert(num);
				// 맨 아래에 있는 말 번호가 바꼈으므로 갱신
				num = piece.second[0].num;

				if (board[nx][ny] == 0) { // 해당 칸이 비어있는 경우
					// A번 말을 이동시켜준다.
					// board에서 이동
					board[nx][ny] = num;

					// A번 말의 정보 수정
					piece.second[0].x = nx;
					piece.second[0].y = ny;

					// 뒤집었기 때문에 맨 아래 말 번호에 대한 정보를 새로 입력해줘야함
					// 맨 아래에 있는 말 번호가 얹고 있는 말 벡터 입력
					pieces[num] = piece.second;

					// 전에 맨 밑에 있던 말 번호는 맨 위로 올라갔으므로 정보 삭제
					erase.erase(num);
				}
				else if (board[nx][ny] != 0) { // 이미 말이 있는 경우
					// A번 말을 위에 쌓는다(순서대로)
					pieces[board[nx][ny]].insert(pieces[board[nx][ny]].end(), piece.second.begin(), piece.second.end());

					// 있던 말들의 맨 아래 번호
					num = board[nx][ny];
				}
				// A번 말이 이동했기 때문에 board에서 제외해준다.
				board[x][y] = 0;
			}

			// 말이 4개 이상 쌓이는 순간 게임 종료
			if (pieces[num].size() >= 4) return turn;
		}

		// 지웠어야 할 정보 지움
		for (int i : erase) {
			pieces.erase(i);
		}

		//print_board();
	}

	/// TODO:: 게임이 종료되는 턴의 번호
	return -1;
}

int main() {
	// 입력
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> color[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int x, y, dir;

		cin >> x >> y >> dir;

		pieces[i].push_back(Node(i, x - 1, y - 1, dir));
		board[x - 1][y - 1] = i;
	}

	//print_board();

	// 이동
	int turn = move();

	if (turn > 1000)
		cout << "-1";
	else
		cout << turn;
}