// https://jolly-note.tistory.com/42

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool continuous_0(vector<int>& stones, int mid, int k) {
    int zeros = 0;
    for (auto stone : stones) {
        if (stone - mid > 0) {
            zeros = 0;
        }
        else zeros++;

        if (zeros >= k) return true;
    }
    return false;
}

int solution(vector<int> stones, int k) {
    int answer = 0;
    int min = 1, max = *max_element(stones.begin(), stones.end());

    while (min <= max) {
        int mid = (max + min) / 2;

        if (continuous_0(stones, mid, k)) {
            max = mid - 1;
        }
        else min = mid + 1;
    }
    return min;
}