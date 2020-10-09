#define Y first
#define X second
#define Pair pair<int,int>
#define Tuple tuple<int,int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

//PASSENGER idx는 2부터 시작하므로 destinations idx와 맞춰주기 위해 -2씩
//e.g.
//PASSENGER = 2,3,4,5,6,...
//idx       = 0,1,2,3,4,...
const int PASSENGER_OFFSET = 2;
const int IMPOSSIBLE = 987654321;
const int DIR_SIZE = 4;
const int EMPTY = 0;
const int WALL = 1;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int N, M, GAS, PASSENGER;
int sy,sx;

vector<vector<int>> graph;
vector<vector<bool>> visited;
vector<Pair> destinations;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

Tuple bfs(int startY, int startX)
{
    if (graph[startY][startX] != EMPTY && graph[startY][startX] != WALL)
        return Tuple(0,startY,startX);

    queue<Pair> q;
    q.push(make_pair(startY, startX));
    visited[startY][startX] = true;

    int dist = 0;
    vector<Pair> passengers;

    while (q.size())
    {
        int loop = q.size();
        bool isFind = false;
        passengers.clear();

        dist += 1;

        while (loop--)
        {
            Pair now = q.front(); q.pop();

            for (int dir = 0; dir < DIR_SIZE; ++dir)
            {
                int ny = now.Y + dy[dir];
                int nx = now.X + dx[dir];

                if (!isSafe(ny,nx)) continue;
                if (visited[ny][nx]) continue;
                if (graph[ny][nx] == WALL) continue;

                if (graph[ny][nx] != EMPTY)
                {
                    isFind = true;
                    passengers.push_back(make_pair(ny,nx));
                }
                
                visited[ny][nx] = true;
                q.push(make_pair(ny,nx));
            }
        }

        if (isFind)
        {
            break;
        }
    }

    sort(passengers.begin(), passengers.end());

    if (passengers.size() == 0)
    {
        return Tuple(IMPOSSIBLE,0,0);
    }
    else 
    {
        return Tuple(dist,passengers[0].Y,passengers[0].X);
    }
}

Tuple movePassenger(int srcY, int srcX, int dstY, int dstX)
{
    queue<Tuple> q;
    q.push(Tuple(0,srcY,srcX));
    visited[srcY][srcX] = true;

    while (!q.empty())
    {
        Tuple now = q.front(); q.pop();
        int nowDist,nowY,nowX;
        tie(nowDist,nowY,nowX) = now;

        if (nowY == dstY && nowX == dstX)
            return now;

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = nowY + dy[dir];
            int nx = nowX + dx[dir];

            if (!isSafe(ny,nx)) continue;
            if (visited[ny][nx]) continue;
            if (graph[ny][nx] == WALL) continue;

            visited[ny][nx] = true;
            q.push(Tuple(nowDist + 1, ny, nx));
        }
    }

    return Tuple(IMPOSSIBLE,0,0);
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> GAS;

    graph.resize(N,vector<int>(N,EMPTY));
    visited.resize(N,vector<bool>(N,false));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> graph[i][j];
        }
    }

    cin >> sy >> sx;
    sy--; sx--;

    PASSENGER = 2;

    for (int i = 0; i < M; ++i)
    {
        //출발지의 행과 열 번호, 목적지의 행과 열 번호
        int srcY, srcX, dstY, dstX;
        cin >> srcY >> srcX >> dstY >> dstX;
        srcY--; srcX--; dstY--; dstX--;
        graph[srcY][srcX] = PASSENGER;

        destinations.push_back(make_pair(dstY,dstX));
        PASSENGER++;
    }

    int movePassengerCount = 0;

    while (movePassengerCount != M)
    {
        for (int i = 0; i < N; ++i)
            fill(visited[i].begin(), visited[i].end(), false);

        //bfs로 승객 찾기
        Tuple nxtPosition = bfs(sy,sx);
        int nxtDist,nxtY,nxtX;
        tie(nxtDist,nxtY,nxtX) = nxtPosition;
        
        //불가능
        if (nxtDist > GAS)
        {
            break;
        }
        else 
        {
            GAS -= nxtDist;
        }

        sy = nxtY;
        sx = nxtX;
        int idx = graph[nxtY][nxtX];
        graph[nxtY][nxtX] = EMPTY;

        idx -= PASSENGER_OFFSET;
        int dstY = destinations[idx].Y;
        int dstX = destinations[idx].X;

        for (int i = 0; i < N; ++i)
            fill(visited[i].begin(), visited[i].end(), false);

        //승객 목적지에 태워주기
        nxtPosition = movePassenger(sy,sx,dstY,dstX);
        tie(nxtDist,nxtY,nxtX) = nxtPosition;
        
        if (nxtDist > GAS)
        {
            break;
        }
        else 
        {
            GAS += nxtDist;
        }

        sy = nxtY;
        sx = nxtX;

        movePassengerCount++;
    }

    if (movePassengerCount == M)
        cout << GAS << "\n";
    else
        cout << -1 << "\n";

    return 0;
}