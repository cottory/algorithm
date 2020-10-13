#define Y first
#define X second
#define Tuple tuple<int,int,int>
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 987654321;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
int N, M;
vector<vector<int>> board;
vector<vector<int>> graph;
vector<vector<bool>> visited;
vector<int> parent;

int find(int node)
{
    if (node == parent[node]) return node;
    else return parent[node] = find(parent[node]);
}
void _union(int c1, int c2)
{
    parent[c2] = c1;
}

int kruskal(int componentSize)
{
    priority_queue<Tuple> pq;

    int cSize = componentSize;  
    parent.resize(cSize+1,INF);

    for (int i = 0; i <= cSize; ++i)
        parent[i] = i;

    for (int i = 1; i <= cSize; ++i)
    {
        for (int j = 1; j <= cSize; ++j)
        {
            if (i < j && graph[i][j] != INF)
            {
                pq.push(make_tuple(-graph[i][j], i, j));
            }
        }
    }

    int result = 0;
    int edgeCount = 0;

    while (edgeCount != cSize-1)
    {
        if (!pq.empty())
        {
            Tuple now = pq.top(); pq.pop();
            int dist,src,dst;

            tie(dist,src,dst) = now;
            dist = -dist;

            int c1 = find(src);
            int c2 = find(dst);

            if (c1 != c2)
            {
                _union(c1,c2);
                result += dist;
                edgeCount += 1;
            }
        }
        else
        {
            result = -1;
            break;
        }
    }
    
    return result;
}

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

void bfs(int y, int x, int componentNumber)
{
    vector<Pair> result;
    queue<Pair> q;
    q.push(make_pair(y,x));
    result.push_back(make_pair(y,x));

    while (!q.empty())
    {
        Pair now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (!isSafe(ny,nx)) continue;
            else if (visited[ny][nx]) continue;
            else if (board[ny][nx] == 0) continue;

            visited[ny][nx] = true;
            q.push(make_pair(ny,nx));
            result.push_back(make_pair(ny,nx));
        }
    }

    for (Pair p : result)
    {
        board[p.Y][p.X] = componentNumber;
    }

    return;
}

int main(void)
{
    ios::sync_with_stdio(0);

    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    board.resize(N,vector<int>(M,0));
    visited.resize(N,vector<bool>(M,false));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> board[i][j];
        }
    }

    int componentNumber = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (!visited[i][j] && board[i][j] != 0)
            {
                visited[i][j] = true;
                bfs(i,j,componentNumber + 1);
                componentNumber++;
            }
        }
    }

    //그래프 생성 후 거리 찾기
    graph.resize(componentNumber+1,vector<int>(componentNumber+1,INF));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (board[i][j] == 0) continue;
            else
            {
                int myNumber = board[i][j];
                
                for (int dir = 0; dir < 4; ++dir)
                {
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];

                    int dist = 0;

                    while (isSafe(ny, nx) && board[ny][nx] == 0)
                    {
                        ny += dy[dir];
                        nx += dx[dir];
                        dist += 1;
                    }

                    if (isSafe(ny,nx) && board[ny][nx] != 0 && board[ny][nx] != myNumber && dist != 1)
                    {
                        int adjNumber = board[ny][nx];
                        graph[myNumber][adjNumber] = min(dist, graph[myNumber][adjNumber]);
                        graph[adjNumber][myNumber] = min(dist, graph[adjNumber][myNumber]);
                    }
                }
            }
        }
    }

    cout << kruskal(componentNumber);

    return 0;
}