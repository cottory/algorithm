#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct Token {
    int y, x, time;
    Token(int yy, int xx, int ttime) : y(yy), x(xx), time(ttime) {}
}Token;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

const int INF = 987654321;
const int DIR_SIZE = 4;

const int EMPTY = 0;
const int WALL = 1;
const int VIRUS = 2;

int N,M,ans,emptySize;
vector<vector<int>> board;
vector<Pair> virus;
vector<vector<bool>> visited;

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < N);
}

//특정 바이러스를 활성화 시키고 시뮬레이션
int solve(vector<int>& order)
{
    bool isFinished = false;
    int result = 0;
    int myEmptySize = emptySize;

    queue<Token> q;
    for (int i = 0; i < N; ++i)
        fill(visited[i].begin(), visited[i].end(), false);

    //set board
    for (int i = 0; i < order.size(); ++i)
    {
        if (order[i])
        {
            int y = virus[i].Y;
            int x = virus[i].X;            
            q.push(Token(y,x,0));
            visited[y][x] = true;
        }
    }

    while (q.size())
    {
        if (myEmptySize == 0)
        {
            isFinished = true;
            break;
        }
        else if (isFinished)
        {
            break;
        }

        int loop = q.size();
        result += 1;

        while (loop--)
        {
            Token now = q.front(); q.pop();

            if (myEmptySize == 0)
            {
                isFinished = true;
                break;
            }

            for (int dir = 0; dir < DIR_SIZE; ++dir)
            {
                int ny = now.y + dy[dir];
                int nx = now.x + dx[dir];

                if (isSafe(ny,nx) && !visited[ny][nx] && (board[ny][nx] != WALL))
                {
                    visited[ny][nx] = true;
                    q.push(Token(ny,nx,now.time+1));

                    if (board[ny][nx] == EMPTY)
                        myEmptySize--;

                }
            }
        }
    }

    if (isFinished) return result;
    else return result = INF;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);


    cin >> N >> M;
    board.resize(N,vector<int>(N,EMPTY));
    visited.resize(N,vector<bool>(N,false));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int state;
            cin >> state;
            if (state == VIRUS)
            {
                virus.push_back(make_pair(i,j));
            }
            else if (state == EMPTY)
            {
                emptySize += 1;
            }

            board[i][j] = state;
        }
    }

    int zeroSize = (int)virus.size() - M;
    vector<int> candidate(zeroSize,0);

    for (int loop = 0; loop < M; ++loop)
        candidate.push_back(1);

    ans = INF;

    do {

        ans = min(ans,solve(candidate));

    } while (next_permutation(candidate.begin(), candidate.end()));

    if (ans == INF) cout << -1 << "\n";
    else cout << ans << endl;

    return 0;
}