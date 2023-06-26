#include <iostream>
#include <vector>

using namespace std;

int sudoku[9][9];

//////////// Ʋ�� �κ� : �ʱ�ȭ�� ������ ����
vector<vector<bool>> row(9, vector<bool>(10, false)); // row[i][j] := i��° �࿡ j���ڰ� �����ϴ���
vector<vector<bool>> col(9, vector<bool>(10, false)); // col[i][j] := i��° ���� j���ڰ� �����ϴ���
vector<vector<bool>> square(9, vector<bool>(10, false)); // square[i][j] := i��° �簢���� j���ڰ� �����ϴ���

pair<int, int> square_idx[] = {{0, 0}, {0, 3}, {0, 6},
                               {3, 0}, {3, 3}, {3, 6},
                               {6, 0}, {6, 3}, {6, 6}};
int square_num(int x, int y){
    for (int i = 0; i < 9; i++) {
        if(x >= square_idx[i].first && y >= square_idx[i].second
            && x < square_idx[i].first + 3 && y < square_idx[i].second + 3)
            return i;
    }
    return -1;
}

bool check(int x, int y, int num){
    return !row[x][num] && !col[y][num] && !square[square_num(x, y)][num];
}

vector<pair<int, int>> blank;

void fill_sudoku(int cnt = 0){ // blank[cnt] �κ� ä���
    if(cnt == blank.size()){
        for (auto & i : sudoku) {
            for (int j : i) {
                cout << j << " ";
            }
            cout << "\n";
        }

        exit(0);
    }

    int x = blank[cnt].first;
    int y = blank[cnt].second;

    for (int num = 1; num <= 9; num++) {
        if (check(x, y, num)) {
            sudoku[x][y] = num;
            row[x][num] = true;
            col[y][num] = true;
            square[square_num(x, y)][num] = true;

            fill_sudoku(cnt + 1);

            sudoku[x][y] = 0;
            row[x][num] = false;
            col[y][num] = false;
            square[square_num(x, y)][num] = false;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];

            if(sudoku[i][j] == 0) {
                blank.emplace_back(i, j);
            }

            row[i][sudoku[i][j]] = true;
            col[j][sudoku[i][j]] = true;
        }
    }
    for (int k = 0; k < 9; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                square[k][sudoku[square_idx[k].first + i][square_idx[k].second + j]] = true;
            }
        }
    }

    fill_sudoku();
}