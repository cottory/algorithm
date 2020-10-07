#define SET 0
#define CLEAR 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int BUMERANG_SIZE = 3;
const int BUMERANG_TYPE = 4;

const int dy[4][3] = {{0,0,1}, {0,0,-1}, {-1,0,0}, {1,0,0}};
const int dx[4][3] = {{-1,0,0}, {-1,0,0}, {0,0,1}, {0,0,1}};

int N, M, ans;
vector<vector<int>> board;
vector<vector<bool>> visited;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

bool isPossible(int y, int x, int type)
{
    for (int i = 0; i < BUMERANG_SIZE; ++i)
    {
        int ny = y + dy[type][i];
        int nx = x + dx[type][i];

        if (!isSafe(ny,nx)) return false;
        else if (visited[ny][nx]) return false;
    }

    return true;
}

int command(int y, int x, int type, int cmd)
{
    int result = 0;

        //set
    for (int i = 0; i < BUMERANG_SIZE; ++i)
    {
        int ny = y + dy[type][i];
        int nx = x + dx[type][i];
            
        if (cmd == SET)
        {
            visited[ny][nx] = true;
            result += board[ny][nx];
            if (i == 1) 
                result += board[ny][nx];

        }   
        else
        {
            visited[ny][nx] = false;
        }         
    }
    
    return result;
}
void backtrack(int idx, int score)
{
    if (idx == (N*M))
    {
        //스코어 계산
        ans = max(ans,score);
        return;
    }
    else 
    {
        int y = idx / M;
        int x = idx % M;

        if (visited[y][x])
        {
            backtrack(idx+1,score);
        }
        else
        {
            //사용 안한 상태
            for (int i = 0; i < BUMERANG_TYPE; ++i)
            {
                if (isPossible(y,x,i))
                {
                    int newScore = command(y,x,i,SET);
                    backtrack(idx+1, score + newScore);
                    command(y,x,i,CLEAR);
                }
            }

            backtrack(idx+1, score);
        }
    }
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

    ans = 0;
    backtrack(0,0);

    cout << ans << "\n";
    return 0;
}