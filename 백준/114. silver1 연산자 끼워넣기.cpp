#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

int N;
int min_val = INT_MAX, max_val = INT_MIN;
vector<int> nums;

void dfs(int idx, int cal, vector<int> op, int used = -1) {
	if (idx == N) {
		min_val = min(min_val, cal);
		max_val = max(max_val, cal);
		return;
	}
	if (used >= 0) op[used] -= 1;
	for (int i = 0; i < 4; i++) {
		if (op[i] == 0) continue;
		switch (i) {
		case 0: // µ¡¼À
			dfs(idx + 1, cal + nums[idx], op, 0);
			break;
		case 1: // »¬¼À
			dfs(idx + 1, cal - nums[idx], op, 1);
			break;
		case 2: // °ö¼À
			dfs(idx + 1, cal * nums[idx], op, 2);
			break;
		case 3: // ³ª´°¼À
			dfs(idx + 1, cal / nums[idx], op, 3);
			break;
		default:
			break;
		}
	}
}

int main() {
	cin >> N;
	
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		nums.push_back(num);
	}

	vector<int> op(4);
	for (int i = 0; i < 4; i++) {
		cin >> op[i];
	}

	dfs(1, nums[0], op);

	cout << max_val << "\n" << min_val << "\n";
}