#define GRAM 2
#define Tuple tuple<int,int,int,int>    //y, x state, time
#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 987654321;
const int NONE_SWORD = 0;
const int HAVE_SWORD = 1;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int N, M, T;

vector<vector<bool>> visited[2];
vector<vector<int>> board;

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs() {

    int result = INF;
    queue<Tuple> q;
    visited[NONE_SWORD][0][0] = true;
    q.push(make_tuple(NONE_SWORD,0,0,0));

    while (!q.empty())
    {
        Tuple now = q.front(); q.pop();
        int state,y,x,time;
        tie(state,y,x,time) = now;

        if (y == N-1 && x == M-1)
        {
            result = min(result,time);
            continue;
        }

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (!isSafe(ny,nx)) continue;
            if (visited[state][ny][nx]) continue;

            if (state == NONE_SWORD)
            {
                if (board[ny][nx] == 1) continue;
                else if (board[ny][nx] == GRAM) 
                {
                    visited[HAVE_SWORD][ny][nx] = true;
                    q.push(make_tuple(HAVE_SWORD,ny,nx,time+1));    
                }
                else 
                {
                    visited[state][ny][nx] = true;
                    q.push(make_tuple(state,ny,nx,time + 1));
                }
            }
            else 
            {
                //have a gram
                visited[state][ny][nx] = true;
                q.push(make_tuple(state,ny,nx,time + 1));
            }
        }
    }

    return result;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> T;

    for (int s = 0; s < 2; ++s)
        visited[s].resize(N,vector<bool>(M,false));

    board.resize(N,vector<int>(M));

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        cin >> board[i][j];

    int answer = bfs();

    if (answer > T)  cout << "Fail\n";
    else cout << answer << "\n";

    return 0;
}