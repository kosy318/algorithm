// https://jolly-note.tistory.com/60?category=1025701

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int tc, num;
    cin >> tc;
    for(int i=0; i<tc; i++){
        int result = 0;
        for(int j=0; j<10; j++){
            cin >> num;
            result += num;
        }
        cout<<"#"<<i+1<<" "<<(int)round((double)result/10)<<endl;
    }
}
