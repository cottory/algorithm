#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, K;
vector<vector<int>> board;
vector<vector<int>> rotateInfos;

//ly, lx: 좌측상단
//ry, rx: 우측하단
void realRotate(vector<vector<int>>& _board, int ly, int lx, int ry, int rx, int s, int loopCount)
{
    if (ly >= ry)
        return;

    int luy = ly;    //left_up_y
    int lux = lx;    //left_up_x
    int ldy = ry;    //left_down_y
    int ldx = lx;    //left_down_x
    int ruy = ly;    //right_up_y
    int rux = rx;    //right_up_x
    int rdy = ry;    //right_down_y
    int rdx = rx;    //right_down_x
    
    int saveValue = _board[luy][lux];

    //1번
    for (int loop = 0; loop < (2 * s) - (2*loopCount); ++loop)
    {
        _board[luy + loop][lux] = _board[luy + loop + 1][lux];
    }

    //2번
    for (int loop = 0; loop < (2 * s) - (2*loopCount); ++loop)
    {
        _board[ldy][ldx + loop] = _board[ldy][ldx + loop + 1];
    }

    //3번
    for (int loop = 0; loop < (2 * s) - (2*loopCount); ++loop)
    {
        _board[rdy - loop][rdx] = _board[rdy - (loop + 1)][rdx];
    }

    //4번
    for (int loop = 0; loop < (2 * s) - (2*loopCount); ++loop)
    {
        _board[ruy][rux - loop] = _board[ruy][rux - (loop + 1)];
    }

    _board[luy][lux+1] = saveValue;
}

vector<vector<int>> rotate(vector<vector<int>> _board, int r, int c, int s)
{

    for (int loop = 0; loop < s; ++loop)
    {
        realRotate(_board, r-s + loop, c-s + loop,  r+s - loop ,  c+s - loop,  s,  loop);
    }

    return _board;
}

int solve(vector<int> order)
{
    vector<vector<int>> tmpBoard = board;

    for (int i = 0; i < order.size(); ++i)
    {
        int idx = order[i];
        vector<int> rotateInfo = rotateInfos[idx];
        int r = rotateInfo[0];
        int c = rotateInfo[1];
        int s = rotateInfo[2];
        tmpBoard = rotate(tmpBoard,r,c,s);
    }

    //결과 계산
    int result = 987654321;

    for (int i = 0; i < N; ++i)
    {
        int score = 0;
        for (int j = 0; j < M; ++j)
        {
            score += tmpBoard[i][j];
        }

        result = min(result,score);
    }

    return result;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    board.resize(N,vector<int>(M));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < K; ++i)
    {
        int r,c,s;
        cin >> r >> c >> s;
        r--; c--;
        vector<int> rotateInfo;
        rotateInfo.push_back(r);
        rotateInfo.push_back(c);
        rotateInfo.push_back(s);
        rotateInfos.push_back(rotateInfo);
    }

    vector<int> order(K);

    for (int i = 0; i < K; ++i)
    {
        order[i] = i;
    }

    int ans = 987654321;

    do {

        vector<int> nowOrder;
        for (int loop = 0; loop < K; ++loop)
        {
            for (int idx = 0; idx < K; ++idx)
            {
                if (order[idx] == loop)
                {
                    nowOrder.push_back(idx);
                }
            }
        }

        //rotate
        ans = min(ans,solve(nowOrder));

    } while (next_permutation(order.begin(), order.end()));

    cout << ans;

    return 0;
}