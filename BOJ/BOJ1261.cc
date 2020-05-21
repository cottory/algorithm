#define INF 987654321
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

typedef struct Tok {
    int y, x, broken;
    Tok(int yy, int xx ,int b) : 
        y(yy), x(xx), broken(b) {}
}Tok;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N, M;   //N: 세로, M: 가로
vector<string> board;
vector<vector<int>> trip;
queue<Tok> q;

bool safe(int y, int x) {
    return (0<=y&&y<N && 0 <= x && x < M);
}

int bfs() {

    int minv = INF;
    q.push(Tok(0,0,0));

    while (!q.empty()) {
        Tok now = q.front(); q.pop();

        if (now.y == N-1 && now.x == M-1) {
            if (now.broken < minv) {
                minv = now.broken;
            }
        }
        else {

            for (int dir = 0; dir < 4; ++dir) {
                int ny = now.y + dy[dir];
                int nx = now.x + dx[dir];

                if (!safe(ny,nx)) continue;

                if (board[ny][nx] == '0') {
                    if (now.broken < trip[ny][nx]) {
                        trip[ny][nx] = now.broken;
                        q.push(Tok(ny,nx,now.broken));
                    }
                }
                else if (board[ny][nx] == '1') {
                    if (now.broken + 1 < trip[ny][nx]) {
                        trip[ny][nx] = now.broken + 1;
                        q.push(Tok(ny,nx,now.broken + 1));
                    }
                }
            }
        }
    }

    return minv;
}
int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> M >> N;
    board.resize(N);
    trip.resize(N, vector<int>(M,INF));

    for (int i = 0; i < N; ++i) 
        cin>> board[i];

    cout << bfs() << "\n";
    
    return 0;
}