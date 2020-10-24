#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int DIR_SIZE = 4;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

const int CHEEZE = 1;
const int EMPTY = 0;
int N, M,total;
vector<vector<int>> board;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

int meltdown()
{
    vector<Pair> meltCandidates, melts;
    vector<vector<bool>> visited(N,vector<bool>(M,false));

    queue<Pair> q;
    q.push({0,0});
    visited[0][0] = true;
    
    while (!q.empty())
    {
        Pair now = q.front(); q.pop();

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (!isSafe(ny,nx)) continue;
            else if (visited[ny][nx]) continue;
            
            visited[ny][nx] = true;

            if (board[ny][nx] == CHEEZE)
            {
                meltCandidates.push_back({ny,nx});
            }
            else
            {
                q.push({ny,nx});
            }
        }
    }

    for (Pair p : meltCandidates)
    {
        int adjCnt = 0;
        
        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = p.Y + dy[dir];
            int nx = p.X + dx[dir];

            if (board[ny][nx] == EMPTY && visited[ny][nx])
            {
                adjCnt += 1;
            }
        }

        if (adjCnt >= 2)
        {
            melts.push_back(p);
        }
    }

    for (Pair p : melts)
    {
        board[p.Y][p.X] = EMPTY;
    }

    return (int)melts.size();
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    board.resize(N,vector<int>(M,0));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> board[i][j];

            if (board[i][j] == CHEEZE)
            {
                total += 1;
            }
        }
    }

    int _time = 0;

    while (true)
    {
        if (total == 0)
            break;

        total -= meltdown();
        _time += 1;
    }

    cout << _time << "\n";

    return 0;
}