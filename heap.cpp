/*
 * Heap? - MaxHeap(c++ default), MinHeap(java default)
 * 완전이진트리 형태
 * 모든 정점에 대해서 부모와 자식간 특정 조건을 만족해야함
 *
 */

#include <iostream>

using namespace std;

struct Heap{
    int* arr;
    int cnt = 0;

    Heap(){arr = new int[100001];}

    void add(int data){
        arr[++cnt] = data;
        int now = cnt;

        while(now > 1){
            int parent = get_parent(now);
            if(arr[now] > arr[parent]){
                int temp = arr[parent];
                arr[parent] = arr[now];
                arr[now] = temp;
                now = parent;
            } else {
                break;
            }
        }
    }

    int get_parent(int child){
        return child / 2;
    }

    int poll(){
        int max = arr[1];
        arr[1] = arr[cnt];
        arr[cnt] = 0;
        cnt--;
        heapify();
        return max;
    }

    void heapify(){
        int now = 1;
        while(get_right(now) <= cnt){
            int larger = now;
            int left = get_left(now);
            int right = get_right(now);
            if(arr[left] > arr[larger]){
                larger = left;
            }
            if(arr[right] > arr[larger]){
                larger = right;
            }
            if(larger != now) {
                int temp = arr[now];
                arr[now] = arr[larger];
                arr[larger] = temp;
                now = larger;
            } else {
                break;
            }
        }
    }

    int get_left(int parent){
        return parent * 2;
    }

    int get_right(int parent){
        return parent * 2 + 1;
    }

    bool is_empty(){
        return cnt == 0;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "#" << t << " ";
        int N;
        cin >> N;
        Heap heap;

        for (int i = 0; i < N; i++) {
            int order;
            cin >> order;
            if(order == 1){ // 힙에 추가
                int num;
                cin >> num;
                heap.add(num);
            } else {
                if (heap.is_empty()) {
                    cout << "-1 ";
                } else {
                    cout << heap.poll() << " ";
                }
            }
        }

        cout << "\n";
    }
}