#define Tuple tuple<int,int,int,int>
#include <tuple>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

const int INF = 987654321;
const int DIR_SIZE = 4;
const int isBroken = 0;
const int isNotBroken = 1;
int N, M,ans;
vector<string> board;
vector<vector<bool>> trip[2];

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs() {
    
    int ret = INF;

    //isBroken, y, x, dist;
    queue<Tuple> q;

    q.push(make_tuple(isNotBroken, 0, 0, 1));
    trip[isNotBroken][0][0] = true;
    
    while (!q.empty())
    {
        Tuple now = q.front(); q.pop();
        int state, y,x,dist;
        tie(state,y,x,dist) = now;

        if (y == N-1 && x == M-1) {
            ret = min(dist,ret);
            break;
        }

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (!isSafe(ny,nx) || trip[state][ny][nx]) 
                continue;

            if (state == isNotBroken && board[ny][nx] == '1') {
                trip[isBroken][ny][nx] = true;
                q.push(make_tuple(isBroken,ny,nx,dist+1));
            }

            //state == isBroken
            if (board[ny][nx] == '0') 
            {
                trip[state][ny][nx] = true;
                q.push(make_tuple(state,ny,nx,dist + 1));    
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

    board.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> board[i];
    }

    for (int i = 0; i < 2; ++i) {
        trip[i].resize(N,vector<bool>(M,false));
    }
    
    ans = bfs();
    if (ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";
    return 0;
}