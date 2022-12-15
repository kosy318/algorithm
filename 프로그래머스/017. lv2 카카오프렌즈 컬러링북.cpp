#include <vector>
#include <queue>

using namespace std;

vector<vector<bool>> visit;
int nb_area;
vector<int> x_dir;
vector<int> y_dir;

int find_area(int i, int j, vector<vector<int>> picture) {
    nb_area++;

    queue<pair<int, int>> que;
    que.push({ i, j });
    visit[i][j] = true;
    int cnt = 0;
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        cnt++;

        for (int k = 0; k < 4; k++) {
            if (x + x_dir[k] >= 0 && x + x_dir[k] < picture.size() && y + y_dir[k] >= 0 && y + y_dir[k] < picture[0].size()
                && picture[x][y] == picture[x + x_dir[k]][y + y_dir[k]] && visit[x + x_dir[k]][y + y_dir[k]] == false) {
                que.push({ x + x_dir[k], y + y_dir[k] });
                visit[x + x_dir[k]][y + y_dir[k]] = true;
            }
        }
    }

    return cnt;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    nb_area = 0;
    int max = 0;

    x_dir = { -1, 1, 0, 0 };
    y_dir = { 0, 0, -1, 1 };

    visit = vector<vector<bool>>(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (picture[i][j] != 0 && visit[i][j] == false) {
                int temp = find_area(i, j, picture);
                if (temp > max) max = temp;
            }
        }
    }

    return { nb_area, max };
}