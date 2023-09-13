#include <iostream>
#include <queue>

using namespace std;

int target;

struct Emoji {
    int time;
    int screen;
    int clipboard;

    Emoji(int time, int screen, int clipboard): time(time), screen(screen), clipboard(clipboard) {}

    Emoji copy() {
        return Emoji(this->time + 1, this->screen, this->screen);
    }
    Emoji paste() {
        return Emoji(this->time + 1, this->screen + this->clipboard, this->clipboard);
    }
    Emoji deleteOne() {
        return Emoji(this->time + 1, this->screen - 1, this->clipboard);
    }

    friend ostream &operator<<(ostream &os, const Emoji &emoji) {
        os << "time: " << emoji.time << " screen: " << emoji.screen << " clipboard: " << emoji.clipboard;
        return os;
    }
};

int bfs(){
    // 시간 순서대로 진행될 것이기 때문에 값을 저장할 필요 없이 먼저 방문한 애가 제일 빠른 애임
    // visited[i][j] := 화면에 i개 있고 clipboard에 j개 있는 경우
    vector<vector<bool>> visited(2000, vector<bool>(2000, false));

    queue<Emoji> que;
    que.emplace(0, 1, 0);
    visited[1][0] = true;

    while(!que.empty()) {
        Emoji emoji = que.front(); que.pop();
        if(emoji.screen == target) return emoji.time;

        // 화면에 있는 이모티콘을 모두 복사해서 클립보드에 저장
        if(!visited[emoji.screen][emoji.screen]) {
            que.push(emoji.copy());
            visited[emoji.screen][emoji.screen] = true;
        }
        // 클립보드에 있는 모든 이모티콘을 화면에 붙여넣기
        if(emoji.screen + emoji.clipboard < 2000 && !visited[emoji.screen + emoji.clipboard][emoji.clipboard]) {
            que.push(emoji.paste());
            visited[emoji.screen + emoji.clipboard][emoji.clipboard] = true;
        }
        // 화면에 있는 이모티콘 중 하나를 삭제
        if(emoji.screen - 1 >= 0 && !visited[emoji.screen - 1][emoji.clipboard]) {
            que.push(emoji.deleteOne());
            visited[emoji.screen - 1][emoji.clipboard] = true;
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target;

    cout << bfs();
}