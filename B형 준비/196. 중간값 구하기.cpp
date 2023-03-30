#include <iostream>
#include <queue>

using namespace std;

#define MOD 20171109;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        // c++ priority_queue default는 max_heap
        priority_queue<int, vector<int>, greater<>> min_h; // min heap ( 큰 숫자들을 가지고 있음, 작은 숫자를 top에서 뽑아냄 )
        priority_queue<int> max_h; // max heap ( 작은 숫자들을 가지고 있음, 큰 숫자를 top에서 뽑아냄 )

        int N, A; // A := 처음에 넣은 자연수
        cin >> N >> A;

        // min heap에 처음 한개 넣음. 중간값은 min heap에 존재
        min_h.push(A);
        int answer = 0;

        for (int i = 0; i < N; i++) {
            int num1, num2;
            cin >> num1 >> num2;

            // 작은 수를 max heap에, 큰 수를 min heap
            if (num1 > num2) {
                min_h.push(num1);
                max_h.push(num2);
            } else {
                min_h.push(num2);
                max_h.push(num1);
            }

            // max heap 보다 min heap이 더 크거나 같기 위해 교환 반복
            while (min_h.top() < max_h.top()) {
                int min_val = min_h.top(); min_h.pop();
                int max_val = max_h.top(); max_h.pop();

                min_h.push(max_val);
                max_h.push(min_val);
            }

            // min heap의 최소가 중간값 보유
            answer = (min_h.top() + answer) % MOD;
        }

        cout << "#" << t << " " << answer << "\n";
    }
}