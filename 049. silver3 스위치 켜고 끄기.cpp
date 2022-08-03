#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> state(1);
	for (int i = 0; i < n; i++) {
		int s;
		cin >> s;
		state.push_back(s);
	}

	int students_cnt;
	cin >> students_cnt;
	for (int i = 0; i < students_cnt; i++) {
		int sex, num;
		cin >> sex >> num;
		
		if (sex == 1) {
			for (int j = num; j <= n; j += num)
				state[j] = 1 - state[j];
		}
		else if (sex == 2) {
			state[num] = 1 - state[num];
			for (int interval = 1; num - interval > 0 && num + interval <= n; interval++) {
				if (state[num - interval] != state[num + interval]) break;
				state[num - interval] = 1 - state[num - interval];
				state[num + interval] = 1 - state[num + interval];
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << state[i];
		if (i % 20 != 0) cout << " ";
		else cout << endl;
	}
}