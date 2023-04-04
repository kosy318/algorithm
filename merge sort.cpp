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

		// sorting �۾�
		merge_sort(words);
		
		cout << "#" << t << "\n";

		string prev = ""; // ���� �̸��� ������ �ȵȴ�.
		for (int i = 0; i < N; i++) {
			if (prev != words[i]) {
				cout << words[i] << "\n";
			}

			prev = words[i];
		}
	}
}

void merge_sort(vector<string>& arr) {
	if (arr.size() == 1) { // �迭�� ũ�Ⱑ 1�̸� sorting �� ���� ���⶧���� return
		return;
	}

	int center = arr.size() / 2;
	vector<string> head(arr.begin(), arr.begin() + center);
	vector<string> tail(arr.begin() + center, arr.end());

	// head�� tail�� merge_sort�� ���ش�.
	merge_sort(head);
	merge_sort(tail);

	// head_ptr�� tail_ptr�� �� �迭���� �񱳵� ������ index�� ���
	int head_ptr = 0;
	int tail_ptr = 0;
	int idx = 0; // arr �迭�� ���Ե� ������ ������ ���

	// head�� tail�� �����ϰ� �����ϴ� ����
	// head�� tail �迭�� ���ҵ��� �տ������� �ϳ��� ���ذ���, ���� ����� ���� arr �迭�� index ��ġ�� ���� ����
	while (idx < arr.size()) {
		// head �迭 �Ǵ� tail �迭�� ��� ���Ұ� arr �迭�� ���Ե� ���(��, head_ptr �Ǵ� tail_ptr�� �� �迭�� ���̿� ������ ���)
		// �ٸ� �迭�� ���� ���ҵ��� ���ʷ� arr �迭�� ���� �߰����ݴϴ�.
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
		// head �迭�� head_ptr �ε����� tail �迭�� tail_ptr �ε����� ���Ͽ� �� ū ���Ҹ� arr �迭�� index ��ġ�� �߰����ݴϴ�.
		else {
			if (compare(head[head_ptr], tail[tail_ptr])) { // head�� �� ���� ������ true
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

	return str1 < str2; // ���������� str1�� str2���� ���� ������ true�� ���ϵ�.
}