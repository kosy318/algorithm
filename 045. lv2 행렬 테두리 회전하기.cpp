#include <string>
#include <vector>

using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    vector<vector<int>> matrix;
    int cnt = 1;
    for(int i=0; i<rows; i++){
        vector<int> temp;
        for(int j=0; j<columns; j++){
            temp.push_back(cnt);
            cnt++;
        }
        matrix.push_back(temp);
    }

    vector<int> dir_x = {0, 1, 0, -1};
    vector<int> dir_y = {1, 0, -1, 0};

    for(auto q: queries){
        int x1 = q[0]-1, y1 = q[1]-1, x2 = q[2]-1, y2 = q[3]-1;
        int i = x1, j = y1;
        int min_val = matrix[x1+1][y1];
        int bf = matrix[x1+1][y1];
        int temp, idx = 0;

        while(idx<4){
            temp = matrix[i][j];
            matrix[i][j] = bf;
            bf = temp;
            if(min_val > bf) min_val = bf;

            if(i+dir_x[idx] > x2 || i+dir_x[idx] < x1 ||
              j+dir_y[idx] > y2 || j+dir_y[idx] < y1) idx++;

            i += dir_x[idx];
            j += dir_y[idx];
        }

        answer.push_back(min_val);
    }

    return answer;
}
