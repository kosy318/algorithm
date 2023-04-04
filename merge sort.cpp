#include <iostream>
#include <string>
#include <vector>

using namespace std;

void merge_sort(vector<string>& arr);
bool compare(string str1, string str2);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<string> words(N);
		for (int i = 0; i < N; i++) {
			cin >> words[i];
		}

		// sorting 작업
		merge_sort(words);
		
		cout << "#" << t << "\n";

		string prev = ""; // 같은 이름은 나오면 안된다.
		for (int i = 0; i < N; i++) {
			if (prev != words[i]) {
				cout << words[i] << "\n";
			}

			prev = words[i];
		}
	}
}

void merge_sort(vector<string>& arr) {
	if (arr.size() == 1) { // 배열의 크기가 1이면 sorting 할 것이 없기때문에 return
		return;
	}

	int center = arr.size() / 2;
	vector<string> head(arr.begin(), arr.begin() + center);
	vector<string> tail(arr.begin() + center, arr.end());

	// head와 tail도 merge_sort를 해준다.
	merge_sort(head);
	merge_sort(tail);

	// head_ptr과 tail_ptr은 각 배열에서 비교된 마지막 index를 기록
	int head_ptr = 0;
	int tail_ptr = 0;
	int idx = 0; // arr 배열에 삽입된 원소의 개수를 기록

	// head와 tail을 정렬하고 병합하는 과정
	// head와 tail 배열의 원소들을 앞에서부터 하나씩 비교해가며, 비교한 결과에 따라 arr 배열의 index 위치에 값을 삽입
	while (idx < arr.size()) {
		// head 배열 또는 tail 배열의 모든 원소가 arr 배열에 삽입된 경우(즉, head_ptr 또는 tail_ptr이 각 배열의 길이와 같아진 경우)
		// 다른 배열의 남은 원소들을 차례로 arr 배열의 끝에 추가해줍니다.
		if (head_ptr == head.size()) {
			while (tail_ptr != tail.size()) {
				arr[idx] = tail[tail_ptr];

				idx += 1;
				tail_ptr += 1;
			}
			break;
		}
		else if (tail_ptr == tail.size()) {
			while (head_ptr != head.size()) {
				arr[idx] = head[head_ptr];

				idx += 1;
				head_ptr += 1;
			}
			break;
		}
		// head 배열의 head_ptr 인덱스와 tail 배열의 tail_ptr 인덱스를 비교하여 더 큰 원소를 arr 배열의 index 위치에 추가해줍니다.
		else {
			if (compare(head[head_ptr], tail[tail_ptr])) { // head가 더 앞이 맞으면 true
				arr[idx] = head[head_ptr];
				head_ptr += 1;
			}
			else {
				arr[idx] = tail[tail_ptr];
				tail_ptr += 1;
			}
		}

		idx += 1;
	}
}

bool compare(string str1, string str2) {
	if (str1.size() != str2.size()) {
		return str1.size() < str2.size();
	}

	return str1 < str2; // 사전순으로 str1이 str2보다 앞이 맞으면 true가 리턴됨.
}