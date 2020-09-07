#define Tuple tuple<int,int,int>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int N,M;
const int MAP_SIZE = 105;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
bool visited[MAP_SIZE][MAP_SIZE];

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs(vector<vector<int> >& maps)
{
    queue<Tuple> q;
    q.push(make_tuple(0,0,1));
    visited[0][0] = true;

    while (!q.empty())
    {
        Tuple now = q.front(); q.pop();
        int y,x,cnt;
        tie(y,x,cnt) = now;

        if (y == N-1 && x == M-1)
            return cnt;

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (!isSafe(ny,nx)) continue;
            if (visited[ny][nx]) continue;
            if (maps[ny][nx] == 0) continue;

            visited[ny][nx] = true;
            q.push(make_tuple(ny,nx,cnt + 1));
        }
    }

    return -1;
}

int solution(vector<vector<int> > maps)
{
    N = maps.size();
    M = maps[0].size();
    int answer = bfs(maps);
    return answer;
}