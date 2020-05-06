#define BLOCK 987654321
#define vvi vector<vector<int>>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int> > board, key[4];

int M, N, B, hole_cnt;

vvi rotate(vvi before)
{
    vvi nxt = before;

    for (int i = 0; i < M; ++i)
    for (int j = 0; j < M; ++j)
        nxt[j][M-1-i] = before[i][j];

    return nxt;
}

bool isUnlock(int state, int st_y, int st_x)
{
    int cover = 0;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if ((key[state][i][j] == 1) && (board[st_y + i][st_x +j] == 1))
                return false;
            if ((key[state][i][j] == 0) && (board[st_y + i][st_x +j] == 0))
                return false;
            if ((key[state][i][j] == 1) && (board[st_y + i][st_x +j] == 0))
                cover += 1;
        }
    }

    return (cover == hole_cnt ? true : false);
}

bool solve()
{
    for (int state = 0; state < 4; ++state)
    {
        for (int i = 0; i < B - M; ++i)
        for (int j = 0; j < B - M; ++j)
        {
            if (isUnlock(state, i, j ))
                return true;
        }
    }
    return false;
}
bool solution(vector<vector<int>> _key, vector<vector<int>> _lock) {
    bool answer = true;

    M = _key.size();
    N = _lock.size();

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        if (_lock[i][j] == 0) hole_cnt += 1;

    board.resize(2*M + N, vector<int>(2*M + N, 987654321));

    B = board.size();

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        board[M-1 + i][M-1 + j] = _lock[i][j];

    for (int i = 0; i < 4; ++i)
        key[i].resize(M, vector<int>(M, 0));

    key[0] = _key;

    for (int nxt = 1; nxt < 4; ++nxt)
        key[nxt] = rotate(key[nxt-1]);
    
    answer = solve();

    return answer;
}