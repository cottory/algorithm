#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N,ans;
const int EMPTY = 0;
const int SET_QUEEN = 1;
vector<vector<int>> board;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}
//세로 체크
bool checkRow(int y, int x)
{
    for (int i = 0; i < N; ++i)
        if (board[i][x]) return false;

    return true;
}

//가로 체크
bool checkCol(int y, int x)
{
    for (int i = 0; i < N; ++i)
        if (board[y][i]) return false;
    
    return true;
}

//대각선 체크
bool checkDiagonal(int y, int x)
{
    /**
     * 00 01 02 03 04 
     * 10 11 12 13 14
     * 20 21 22 23 24
     * 30 31 32 33 34
     * 40 41 42 43 44
     */
    
    // / 방향 
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
        if (i+j == x+y)
        {
            if(board[i][j])
            {
                return false;
            }
        }
    }

    /**
     * 00 01 02 03 04 
     * 10 11 12 13 14
     * 20 21 22 23 24
     * 30 31 32 33 34
     * 40 41 42 43 44
     */

    // \ 방향 
    int ny = y;
    int nx = x;
    while (isSafe(ny,nx))
    {
        if (board[ny][nx])
            return false;

        ny += 1;
        nx += 1;
    }

    ny = y - 1;
    nx = x - 1;
    while (isSafe(ny,nx))
    {
        if (board[ny][nx])
            return false;

        ny -= 1;
        nx -= 1;
    }

    return true;
}

bool isPossible2Set(int y, int x)
{
    if (checkRow(y,x) && checkCol(y,x) && checkDiagonal(y,x))
        return true;

    return false;
}

void setQueen(int y, int x, int cnt)
{   
    if (cnt == N)
    {
        ans += 1;
        return;
    }

    for (int nxt = 0; nxt < N; ++nxt)
    {
        if (board[y+1][nxt] == EMPTY && isPossible2Set(y+1,nxt))
        {
            board[y+1][nxt] = SET_QUEEN;
            setQueen(y+1,nxt,cnt+1);
            board[y+1][nxt] = EMPTY;
        }
    }
    
    return;
}

int solution(int n) {
    int answer = 0;
    N = n;

    board.resize(N,vector<int>(N,EMPTY));

    for (int i = 0; i < n; ++i)
    {
        if (board[0][i] == EMPTY && isPossible2Set(0,i))
        {
            board[0][i] = SET_QUEEN;
            setQueen(0,i,1);
            board[0][i] = EMPTY;
        }    
    }
    
    answer = ans;
    return answer;
}