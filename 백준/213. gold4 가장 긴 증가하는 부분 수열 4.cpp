#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N; // 수열 A의 크기
    cin >> N;

    int* arr = new int[N];
    vector<pair<int, vector<int>>> lcs(N);

    int max_idx = -1;
    int max = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];

        if(i == 0){
            lcs[i] = {1, {arr[i]}};
        } else {
            int idx = -1;
            for(int j=0; j<i; j++){
                if(arr[j] < arr[i] && (idx == -1 || lcs[idx].first < lcs[j].first)){
                    idx = j;
                }
            }
            if(idx != -1) {
                vector<int> list(lcs[idx].second);
                list.push_back(arr[i]);
                lcs[i] = {lcs[idx].first + 1, list};
            } else {
                lcs[i] = {1, {arr[i]}};
            }
        }

        if(lcs[i].first > max){
            max = lcs[i].first;
            max_idx = i;
        }
    }

    cout << max << "\n";
    for(int num : lcs[max_idx].second){
        cout << num << " ";
    }
}