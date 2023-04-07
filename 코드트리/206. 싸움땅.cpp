#include <iostream>
#include <queue>

using namespace std;

struct Player {
	int x, y;
	int dir;
	int initial, gun;

	Player(int x = 0, int y = 0, int dir = 0, int initial = 0, int gun = 0) :x(x), y(y), dir(dir), initial(initial), gun(gun) {}
};

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int n; // 격자의 크기
int m; // 플레이어의 수
priority_queue<int> gun_board[20][20];
int player_board[20][20];
Player player[31]; // player 번호 1부터 시작
int score[31] = { 0, }; // player 번호 1부터 시작

void move();
void loser_move(int num);
void fight(int num);
void get_gun(int num);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	int round; // 라운드 수
	cin >> n >> m >> round;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int gun;
			cin >> gun;

			if (gun > 0) { // 총 있음
				gun_board[i][j].push(gun);
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y, d, s;
		cin >> x >> y >> d >> s;

		player[i] = Player(x-1, y-1, d, s); // 위치, 방향, 초기 값
		player_board[x-1][y-1] = i;
	}

	for (int k = 0; k < round; k++) {
		// 1. 순차적으로 본인이 향하고 있는 방향대로 한 칸 만큼 이동
		move();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				//cout << player_board[i][j] << " ";
			}
			//cout << endl;
		}
		//cout << "score ";
		for (int i = 1; i <= m; i++) {
			//cout << score[i] << " ";
		}
		//cout << endl;
	}

	//////////////////////// TODO::k라운드를 진행하면서 각 플레이어들이 획득한 포인트 출력 ///////////////////////////
	for (int i = 1; i <= m; i++) {
		cout << score[i] << " ";
	}
}

void move() {
	for (int i = 1; i <= m; i++) {
		//cout << i << "번 player가 " << player[i].x << ", " << player[i].y << " 에서 ";
		int nx = player[i].x + dx[player[i].dir];
		int ny = player[i].y + dy[player[i].dir];

		// 격자를 벗어나는 경우, 정 반대방향으로 "방향을 바꾸어서" 1만큼 이동
		if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
			//cout << player[i].dir << " 에서 ";
			// 방향을 반대로
			////////////////  틀린 부분 : %4인데 3으로 적음..
			player[i].dir = (player[i].dir + 2) % 4;

			//cout << player[i].dir << "로 바꿈" << endl;
			nx = player[i].x + dx[player[i].dir];
			ny = player[i].y + dy[player[i].dir];
		}

		player_board[player[i].x][player[i].y] = 0;

		player[i].x = nx;
		player[i].y = ny;
		//cout << nx << ", " << ny << "로 이동 시도\n";

		// player_board[player[i].x][player[i].y] = i; // 이겨야 이동 가능

		// 이동한 좌표에 대해 작업 수행
		// 2. 이동한 방향에 플레이어가 없다면 총이 있는지 확인
		if (player_board[player[i].x][player[i].y] != 0) { // 플레이어가 존재
			//cout << "해당 좌표에 다른 플레이어 " << player_board[player[i].x][player[i].y] << "가 존재\n";
			fight(i);
		}
		else if(!gun_board[player[i].x][player[i].y].empty()){ // 플레이어가 없고 총이 있음
			// player를 위치시켜도 됨
			player_board[player[i].x][player[i].y] = i;

			// 총이 있는 경우, 총을 획득
			// 총을 이미 가지고 있는 경우, 공격력이 더 쎈 총을 획득하고, 나머지 총들은 해당 격자에 둠	
			get_gun(i);
		}
		else {
			player_board[player[i].x][player[i].y] = i;
		}
	}
}

void loser_move(int num) {
	int nx = player[num].x + dx[player[num].dir];
	int ny = player[num].y + dy[player[num].dir];

	// 다른 플레이어가 있거나 격자 범위 밖인 경우 오른쪽으로 90도 회전하여 빈칸이 보이는 순간 이동
	//cout << player[num].dir << "방향\n";
	while (nx < 0 || ny < 0 || nx >= n || ny >= n || player_board[nx][ny] != 0) {
		// 90도 회전
		////////////////  틀린 부분 : %4인데 3으로 적음..
		player[num].dir = (player[num].dir + 1) % 4;

		nx = player[num].x + dx[player[num].dir];
		ny = player[num].y + dy[player[num].dir];
		//cout << player[num].dir << "방향\n";
	}

	player[num].x = nx;
	player[num].y = ny;

	player_board[player[num].x][player[num].y] = num; // 이동
	//cout << "패자 " << player[num].x << ", " << player[num].y << "에 등록 완료\n";
	
	// 이동한 좌표에 총이 있는지 확인
	// 만약 총이 있다면 가장 공격력 높은 총을 획득하고 나머지 총들은 격자에 내려놓음
	if (!gun_board[player[num].x][player[num].y].empty()) { // 총이 있음
		player[num].gun = gun_board[player[num].x][player[num].y].top();
		gun_board[player[num].x][player[num].y].pop();
	}
}

// 플레이어가 있는 경우, 싸움
void fight(int num) {
	Player player1 = player[num]; // 움직인 player
	Player player2 = player[player_board[player1.x][player1.y]]; // player1이 올라갈 위치에 있는 다른 player

	int winner = 0;
	int loser = 0;
	int diff = 0;
	// 초기 능력치와 가지고 있는 총의 공격력의 합을 비교하여 더 큰 플레이어가 이김
	if (player1.initial + player1.gun > player2.initial + player2.gun) { // player1 승
		winner = num;
		loser = player_board[player1.x][player1.y];
		diff = (player1.initial + player1.gun) - (player2.initial + player2.gun);

		player_board[player1.x][player1.y] = winner;
	}
	else if (player1.initial + player1.gun < player2.initial + player2.gun) { // player2 승
		winner = player_board[player1.x][player1.y];
		loser = num;
		diff = (player2.initial + player2.gun) - (player1.initial + player1.gun);

		player_board[player1.x][player1.y] = winner;
	}
	else { // 둘의 능력치가 같음
		// 수치가 같은 경우 초기 능력치가 높은 플레이어가 승리
		// 따로 얻는 점수 없음
		if (player1.initial > player2.initial) { // player1 승
			winner = num;
			loser = player_board[player1.x][player1.y];

			player_board[player1.x][player1.y] = winner;
		}
		else if (player1.initial < player2.initial) { // player2 승
			winner = player_board[player1.x][player1.y];
			loser = num;

			player_board[player1.x][player1.y] = winner;
		}
	}

	//cout << "승자 " << winner << " \\ " << "패자 " << loser << " \n";
	//cout << diff << "만큼 점수를 얻음\n";
	// 이긴 플레이어는 "각 플레이어의" 초기 능력치와 가지고 있는 총의 공격력의 합의 차이 만큼 포인트로 획득
	score[winner] += diff;

	// 진 플레이어는 본인이 가지고 있는 총을 격자에 내려놓고 원래 가지고 있던 방향대로 한칸 이동
	if (player[loser].gun != 0) {
		// 총 내려놓음
		gun_board[player[loser].x][player[loser].y].push(player[loser].gun);
		player[loser].gun = 0;
	}

	// 방향대로 한칸 이동
	loser_move(loser);

	// 이긴 플레이어는 승리한 칸에 떨어져 있는 총들과 원래 들고있던 총 중 가장 공격력이 높은 총을 획득, 나머지는 내려놓음
	///////////////////////////// 틀리 부분 : winner로 했어야했는데,,,, num으로 함 ㅠㅠ
	if(!gun_board[player[winner].x][player[winner].y].empty())
		get_gun(winner);
}

void get_gun(int num){
	if (player[num].gun < gun_board[player[num].x][player[num].y].top()) {
		gun_board[player[num].x][player[num].y].push(player[num].gun);
		player[num].gun = gun_board[player[num].x][player[num].y].top();
		gun_board[player[num].x][player[num].y].pop();
	}
}