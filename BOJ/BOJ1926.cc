#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};
int N, M, maxv;
vector<vector<int>> board;
vector<vector<bool>> trip;
queue<pii> q;

bool safe(int y, int x) {
    return (0<=y&&y<N&&0<=x&&x<M);
}
int bfs(int y, int x) 
{
    int ret = 1;
    q.push({y,x});

    while (!q.empty()) {

        pii now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (safe(ny,nx) && !trip[ny][nx] && board[ny][nx]) {
                q.push({ny,nx});
                trip[ny][nx] = true;
                ret += 1;
            }
        }
    }

    return ret;
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    board.resize(N,vector<int>(M,0));
    trip.resize(N,vector<bool>(M,false));

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        cin >> board[i][j];

    int cnt = 0;
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {

        if (!trip[i][j] && board[i][j]) {
            trip[i][j] = true;
            cnt += 1;
            maxv = max(maxv,bfs(i,j));
        }
    }
    
    cout << cnt << "\n" << maxv << "\n";
    return 0;
}