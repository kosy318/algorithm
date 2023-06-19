#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int N;
vector<int> parents;
vector<int> cnt;
map<string, int> match;

int find_parent(int node){
    if(parents[node] == node) return node;

    return parents[node] = find_parent(parents[node]);
}

bool union_network(int a, int b){
    int aRoot = find_parent(a);
    int bRoot = find_parent(b);

    if(aRoot == bRoot) return false; // 이미 한 그룹이라 union 불가

    /////////////// 틀린 부분 : parents[b] = aRoot 가 아니라... parents[bRoot] = aRoot임.. 제발 ㅠㅠㅠ
    parents[bRoot] = aRoot;
//    cout  << "cnt -------------" << "\n";
//    for (int i = 0; i < match.size(); i++) {
//        cout << cnt[i] << " ";
//    }
//    cout << "\n";
    cnt[aRoot] += cnt[bRoot];
    cnt[bRoot] = 0;

//    for (int i = 0; i < match.size(); i++) {
//        cout << cnt[i] << " ";
//    }
//    cout << "\n" << "cnt -------------" << "\n";
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        match.clear();
        parents.clear();
        cnt.clear();

        while (N--) {
            string name1, name2;
            cin >> name1 >> name2;

            if(match.find(name1) == match.end()){ // 못찾았으면
                match[name1] = match.size();

                parents.push_back(match[name1]);
                cnt.push_back(1);
            }
            if(match.find(name2) == match.end()){ // 못찾았으면
                cnt[match.size()] = 1;
                match[name2] = match.size();

                parents.push_back(match[name2]);
                cnt.push_back(1);
            }

            int num1 = match[name1], num2 = match[name2];

//            union_network(num1, num2);
            union_network(num1, num2);
            /////////////// 틀린 부분 : 시간 초과 endl -> "\n"으로 바꿔야함
            cout << cnt[find_parent(num1)] << "\n";

//            for (auto p: match) {
//                cout << p.first << " : " << p.second << "\n";
//            }
//            for (int i = 0; i < match.size(); i++) {
//                cout << parents[i] << " ";
//            }
//            cout << "\n";
        }

    }
}