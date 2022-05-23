// https://jolly-note.tistory.com/66?category=1025701

#include<iostream>
#include<vector>
#include<map>
using namespace std;

int main() {
	int dump, height;


	for (int tc = 0; tc < 10; tc++) {
		cin >> dump;
		map<int, int> box = {};
		for (int i = 0; i < 100; i++) {
			cin >> height;
			box[height]++;
		}
		
		for (int i = 0; i < dump; i++) {
			box.begin()->second--;
			box[box.begin()->first + 1]++;
			box.rbegin()->second--;
			box[box.rbegin()->first - 1]++;

			if (box.begin()->second == 0) box.erase(box.begin()->first);
			if (box.rbegin()->second == 0) box.erase(box.rbegin()->first);
			
			if (box.rbegin()->first - box.begin()->first <= 1) break;
		}
		cout<<"#"<<tc+1<<" "<<box.rbegin()->first - box.begin()->first<<endl;
	}
}