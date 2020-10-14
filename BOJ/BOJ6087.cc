#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
const int INF = 987654321;
const int DIR_SIZE = 4;
int ROW,COL;
vector<string> map;
vector<vector<vector<int>>> dist;
vector<Pair> cPos;
queue<Pair> q;

bool isSafe(int y, int x)
{
    return (0 <= y && y < ROW && 0 <= x && x < COL);
}

void bfs()
{
    int mirrorCnt = 0;
    while (q.size())
    {
        int loop = q.size();
        mirrorCnt += 1;

        while (loop--)
        {
            Pair now = q.front(); q.pop();

            int nowY,nowX;
            tie(nowY,nowX) = now;

            for (int dir = 0; dir < DIR_SIZE; ++dir)
            {
                int ny = nowY + dy[dir];
                int nx = nowX + dx[dir];

                while (isSafe(ny,nx) && map[ny][nx] != '*')
                {
                    if (dist[dir][ny][nx] > mirrorCnt)
                    {
                        dist[dir][ny][nx] = mirrorCnt;
                        q.push(make_pair(ny,nx));
                    }
                    ny += dy[dir];
                    nx += dx[dir];
                }
            }
        }
    }
}
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> COL >> ROW;
    dist.resize(DIR_SIZE,vector<vector<int>>(ROW,vector<int>(COL,INF)));

    for (int i = 0; i < ROW; ++i)
    {
        string str;
        cin >> str;
        map.push_back(str);
    }

    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (map[i][j] == 'C')
            {
                cPos.push_back(make_pair(i,j));
            }
        }
    }

    //1st. 시작점에서 거울 안 쓰고 갈 수 있는 방향 INQUEUE
    int sy = cPos[0].Y;
    int sx = cPos[0].X;

    for (int dir = 0; dir < DIR_SIZE; ++dir)
    {
        dist[dir][sy][sx] = 0;
        q.push(make_pair(sy,sx));

        int ny = sy + dy[dir];
        int nx = sx + dx[dir];

        while (isSafe(ny,nx) && map[ny][nx] != '*')
        {
            dist[dir][ny][nx] = 0;
            q.push(make_pair(ny,nx));
            ny += dy[dir];
            nx += dx[dir];
        }
    }

    //2nd. BFS
    bfs();

    //3rd. printResult
    int ans = INF;
    for (int dir = 0; dir < DIR_SIZE; ++dir)
    {
        ans = min(ans,dist[dir][cPos[1].Y][cPos[1].X]);
    }
    
    cout << ans << "\n";

    return 0;
}