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
    // �ð� ������� ����� ���̱� ������ ���� ������ �ʿ� ���� ���� �湮�� �ְ� ���� ���� ����
    // visited[i][j] := ȭ�鿡 i�� �ְ� clipboard�� j�� �ִ� ���
    vector<vector<bool>> visited(2000, vector<bool>(2000, false));

    queue<Emoji> que;
    que.emplace(0, 1, 0);
    visited[1][0] = true;

    while(!que.empty()) {
        Emoji emoji = que.front(); que.pop();
        if(emoji.screen == target) return emoji.time;

        // ȭ�鿡 �ִ� �̸�Ƽ���� ��� �����ؼ� Ŭ�����忡 ����
        if(!visited[emoji.screen][emoji.screen]) {
            que.push(emoji.copy());
            visited[emoji.screen][emoji.screen] = true;
        }
        // Ŭ�����忡 �ִ� ��� �̸�Ƽ���� ȭ�鿡 �ٿ��ֱ�
        if(emoji.screen + emoji.clipboard < 2000 && !visited[emoji.screen + emoji.clipboard][emoji.clipboard]) {
            que.push(emoji.paste());
            visited[emoji.screen + emoji.clipboard][emoji.clipboard] = true;
        }
        // ȭ�鿡 �ִ� �̸�Ƽ�� �� �ϳ��� ����
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