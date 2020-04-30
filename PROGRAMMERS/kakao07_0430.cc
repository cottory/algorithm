#define SEARCH_SIZE 3
#define Y first
#define X second
#define pii pair<int,int>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int dy[] = {1,0,1};
int dx[] = {1,1,0};

int M,N;
vector<vector<bool> > isErase;

bool isSafe(int y, int x)
{
    return (0 <= y && y < M && 0 <= x && x < N);
}

void down(vector<string>& board)
{

    for (int x = 0; x < N; ++x)
    {
        //추출
        stack<char> s;
        for (int y = 0; y < M; ++y)
        {
            if (board[y][x] != 'X')
            {
                s.push(board[y][x]);
                board[y][x] = 'X';
            }
        }

        //재배치
        int idx = M-1;
        while (!s.empty())
        {
            board[idx][x] = s.top(); s.pop();
            idx--;
        }
    }
}
int solve(bool& flag, vector<string>& board)
{
    int ret = 0;
    vector<pii> removed;

    for (int y = 0; y < M-1; ++y)
    {
        for (int x = 0; x < N-1; ++x)
        {
            
            int cnt = 0;
            char target = board[y][x];
            
            if (target == 'X') 
                continue;
            
            for (int dir = 0; dir < SEARCH_SIZE; ++dir)
            {
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if (isSafe(ny,nx) && target == board[ny][nx])
                {
                    cnt += 1;
                }
            }

            if (cnt == 3) 
            {
                if (!isErase[y][x]) {
                    removed.push_back({y,x});
                    ret += 1;
                    isErase[y][x] = true;
                }

                for (int dir = 0; dir < SEARCH_SIZE; ++dir)
                {
                    int ny = y + dy[dir];
                    int nx = x + dx[dir];

                    if (isSafe(ny,nx))
                    {
                        if (!isErase[ny][nx]) 
                        {
                            removed.push_back({ny,nx});
                            ret += 1;
                            isErase[ny][nx] = true;
                        }
                    }
                }  
            }
        }
    }

    if (ret) flag = false;
    else flag = true;

    for (pii pos : removed)
    {
        board[pos.Y][pos.X] = 'X';
    }

    return ret;
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    M = m;
    N = n;

    isErase.resize(M, vector<bool>(N, false));
    bool flag = false;

    while (!flag)
    {
        for (int i = 0; i < isErase.size(); ++i) 
        {
            fill(isErase[i].begin(), isErase[i].end(), false);
        }

        answer += solve(flag, board);
        down(board);
    }
    return answer;
}