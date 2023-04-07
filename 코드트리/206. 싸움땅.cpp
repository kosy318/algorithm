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

int n; // ������ ũ��
int m; // �÷��̾��� ��
priority_queue<int> gun_board[20][20];
int player_board[20][20];
Player player[31]; // player ��ȣ 1���� ����
int score[31] = { 0, }; // player ��ȣ 1���� ����

void move();
void loser_move(int num);
void fight(int num);
void get_gun(int num);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	int round; // ���� ��
	cin >> n >> m >> round;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int gun;
			cin >> gun;

			if (gun > 0) { // �� ����
				gun_board[i][j].push(gun);
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y, d, s;
		cin >> x >> y >> d >> s;

		player[i] = Player(x-1, y-1, d, s); // ��ġ, ����, �ʱ� ��
		player_board[x-1][y-1] = i;
	}

	for (int k = 0; k < round; k++) {
		// 1. ���������� ������ ���ϰ� �ִ� ������ �� ĭ ��ŭ �̵�
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

	//////////////////////// TODO::k���带 �����ϸ鼭 �� �÷��̾���� ȹ���� ����Ʈ ��� ///////////////////////////
	for (int i = 1; i <= m; i++) {
		cout << score[i] << " ";
	}
}

void move() {
	for (int i = 1; i <= m; i++) {
		//cout << i << "�� player�� " << player[i].x << ", " << player[i].y << " ���� ";
		int nx = player[i].x + dx[player[i].dir];
		int ny = player[i].y + dy[player[i].dir];

		// ���ڸ� ����� ���, �� �ݴ�������� "������ �ٲپ" 1��ŭ �̵�
		if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
			//cout << player[i].dir << " ���� ";
			// ������ �ݴ��
			////////////////  Ʋ�� �κ� : %4�ε� 3���� ����..
			player[i].dir = (player[i].dir + 2) % 4;

			//cout << player[i].dir << "�� �ٲ�" << endl;
			nx = player[i].x + dx[player[i].dir];
			ny = player[i].y + dy[player[i].dir];
		}

		player_board[player[i].x][player[i].y] = 0;

		player[i].x = nx;
		player[i].y = ny;
		//cout << nx << ", " << ny << "�� �̵� �õ�\n";

		// player_board[player[i].x][player[i].y] = i; // �̰ܾ� �̵� ����

		// �̵��� ��ǥ�� ���� �۾� ����
		// 2. �̵��� ���⿡ �÷��̾ ���ٸ� ���� �ִ��� Ȯ��
		if (player_board[player[i].x][player[i].y] != 0) { // �÷��̾ ����
			//cout << "�ش� ��ǥ�� �ٸ� �÷��̾� " << player_board[player[i].x][player[i].y] << "�� ����\n";
			fight(i);
		}
		else if(!gun_board[player[i].x][player[i].y].empty()){ // �÷��̾ ���� ���� ����
			// player�� ��ġ���ѵ� ��
			player_board[player[i].x][player[i].y] = i;

			// ���� �ִ� ���, ���� ȹ��
			// ���� �̹� ������ �ִ� ���, ���ݷ��� �� �� ���� ȹ���ϰ�, ������ �ѵ��� �ش� ���ڿ� ��	
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

	// �ٸ� �÷��̾ �ְų� ���� ���� ���� ��� ���������� 90�� ȸ���Ͽ� ��ĭ�� ���̴� ���� �̵�
	//cout << player[num].dir << "����\n";
	while (nx < 0 || ny < 0 || nx >= n || ny >= n || player_board[nx][ny] != 0) {
		// 90�� ȸ��
		////////////////  Ʋ�� �κ� : %4�ε� 3���� ����..
		player[num].dir = (player[num].dir + 1) % 4;

		nx = player[num].x + dx[player[num].dir];
		ny = player[num].y + dy[player[num].dir];
		//cout << player[num].dir << "����\n";
	}

	player[num].x = nx;
	player[num].y = ny;

	player_board[player[num].x][player[num].y] = num; // �̵�
	//cout << "���� " << player[num].x << ", " << player[num].y << "�� ��� �Ϸ�\n";
	
	// �̵��� ��ǥ�� ���� �ִ��� Ȯ��
	// ���� ���� �ִٸ� ���� ���ݷ� ���� ���� ȹ���ϰ� ������ �ѵ��� ���ڿ� ��������
	if (!gun_board[player[num].x][player[num].y].empty()) { // ���� ����
		player[num].gun = gun_board[player[num].x][player[num].y].top();
		gun_board[player[num].x][player[num].y].pop();
	}
}

// �÷��̾ �ִ� ���, �ο�
void fight(int num) {
	Player player1 = player[num]; // ������ player
	Player player2 = player[player_board[player1.x][player1.y]]; // player1�� �ö� ��ġ�� �ִ� �ٸ� player

	int winner = 0;
	int loser = 0;
	int diff = 0;
	// �ʱ� �ɷ�ġ�� ������ �ִ� ���� ���ݷ��� ���� ���Ͽ� �� ū �÷��̾ �̱�
	if (player1.initial + player1.gun > player2.initial + player2.gun) { // player1 ��
		winner = num;
		loser = player_board[player1.x][player1.y];
		diff = (player1.initial + player1.gun) - (player2.initial + player2.gun);

		player_board[player1.x][player1.y] = winner;
	}
	else if (player1.initial + player1.gun < player2.initial + player2.gun) { // player2 ��
		winner = player_board[player1.x][player1.y];
		loser = num;
		diff = (player2.initial + player2.gun) - (player1.initial + player1.gun);

		player_board[player1.x][player1.y] = winner;
	}
	else { // ���� �ɷ�ġ�� ����
		// ��ġ�� ���� ��� �ʱ� �ɷ�ġ�� ���� �÷��̾ �¸�
		// ���� ��� ���� ����
		if (player1.initial > player2.initial) { // player1 ��
			winner = num;
			loser = player_board[player1.x][player1.y];

			player_board[player1.x][player1.y] = winner;
		}
		else if (player1.initial < player2.initial) { // player2 ��
			winner = player_board[player1.x][player1.y];
			loser = num;

			player_board[player1.x][player1.y] = winner;
		}
	}

	//cout << "���� " << winner << " \\ " << "���� " << loser << " \n";
	//cout << diff << "��ŭ ������ ����\n";
	// �̱� �÷��̾�� "�� �÷��̾���" �ʱ� �ɷ�ġ�� ������ �ִ� ���� ���ݷ��� ���� ���� ��ŭ ����Ʈ�� ȹ��
	score[winner] += diff;

	// �� �÷��̾�� ������ ������ �ִ� ���� ���ڿ� �������� ���� ������ �ִ� ������ ��ĭ �̵�
	if (player[loser].gun != 0) {
		// �� ��������
		gun_board[player[loser].x][player[loser].y].push(player[loser].gun);
		player[loser].gun = 0;
	}

	// ������ ��ĭ �̵�
	loser_move(loser);

	// �̱� �÷��̾�� �¸��� ĭ�� ������ �ִ� �ѵ�� ���� ����ִ� �� �� ���� ���ݷ��� ���� ���� ȹ��, �������� ��������
	///////////////////////////// Ʋ�� �κ� : winner�� �߾���ߴµ�,,,, num���� �� �Ф�
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