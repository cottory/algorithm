#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

const int DIR_SIZE = 8;
const int dy[] = {-1,1,0,0,1,1,-1,-1};
const int dx[] = {0,0,-1,1,-1,1,1,-1};
int N,M,ans;
vector<vector<int>> board;
vector<vector<bool>> visited;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs(int y, int x)
{
    for (int i = 0; i < N; ++i)
        fill(visited[i].begin(), visited[i].end(), false);

    int dist = 0;
    queue<Pair> q;
    visited[y][x] = true;
    q.push(make_pair(y,x));

    while (q.size())
    {
        int loop = q.size();
        dist += 1;

        while (loop--)
        {
            Pair now = q.front(); q.pop();

            for (int dir = 0; dir < DIR_SIZE; ++dir)
            {
                int ny = now.Y + dy[dir];
                int nx = now.X + dx[dir];

                if (!isSafe(ny,nx)) continue;
                else if (visited[ny][nx]) continue;

                if (board[ny][nx])
                {
                    return dist;
                }
                else
                {
                    visited[ny][nx] = true;
                    q.push(make_pair(ny,nx));
                }
            }
        }
    }

    return dist;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    board.resize(N,vector<int>(M));
    visited.resize(N,vector<bool>(M,false));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> board[i][j];
        }
    }

    ans = -1;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (!board[i][j])
            {
                ans = max(ans,bfs(i,j));
            }
        }
    }

    cout << ans;

    return 0;
}