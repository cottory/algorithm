#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

typedef struct Token {
    int state, y, x, cnt;
    Token(int ss, int yy, int xx, int ccnt) : state(ss), y(yy), x(xx), cnt(ccnt) {}
}Token;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N, M, st_y, st_x;
bool trip[64][50][50];

vector<string> map;

bool safe(int y, int x) {
    return (0<=y && y < N && 0 <=x && x < M);
}

bool isPossible(int state, char target) {
    int idx = target - 'A';
    int ret = state & (1 << idx);
    if (ret) return true;
    else return false;
}
int bfs(int y, int x) {
    
    int ret = 0;
    queue<Token> q;

    q.push(Token(0,y,x,0));
    
    while (!q.empty()) {
        Token now = q.front(); q.pop();

        if (map[now.y][now.x] == '1') {
            return now.cnt;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.y + dy[dir];
            int nx = now.x + dx[dir];

            if (!safe(ny,nx)) continue;
            if (trip[now.state][ny][nx]) continue;
            if (map[ny][nx] == '#') continue;

            if ('a' <= map[ny][nx] && map[ny][nx] <= 'f') {
                int idx = map[ny][nx] - 'a';
                int newState = now.state | (1 << idx);
                trip[newState][ny][nx] = true;
                q.push(Token(newState, ny, nx, now.cnt + 1));
            }
            else if ('A' <= map[ny][nx] && map[ny][nx] <= 'F') {
                if (isPossible(now.state, map[ny][nx])) {
                    trip[now.state][ny][nx] = true;
                    q.push(Token(now.state, ny, nx, now.cnt + 1));
                }
            }
            else {
                //0 또는 1
                trip[now.state][ny][nx] = true;
                q.push(Token(now.state, ny, nx, now.cnt + 1));
            }
        }
    }

    return -1;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    map.resize(N);
    
    for (int i = 0; i < 64; ++i)
    for (int j = 0; j < 50; ++j)
        fill(trip[i][j], trip[i][j] + 50, false);

    for (int i = 0; i < N; ++i) 
        cin >> map[i];

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        if (map[i][j] == '0') {
            st_y = i;
            st_x = j;
        } 
    }

    cout << bfs(st_y, st_x) << "\n";
    return 0;
}