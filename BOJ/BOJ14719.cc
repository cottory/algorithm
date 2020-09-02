#include <iostream>
#include <vector>
using namespace std;

int H,W;
vector<vector<int>> board;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> H >> W;
    board.resize(H,vector<int>(W,0));

    for (int h,i = 0; i < W; ++i)
    {
        cin >> h;
        for (int loop = 1; loop <= h; ++loop)
        {
            board[H-loop][i] = 1;
        }
    }

    int answer = 0;

    //맨 밑에 층부터 탐색
    for (int i = H-1; i >= 0; --i)
    {
        int wallCnt = 0;
        int holeCnt = 0;
        int st = 0;

        //시작점 찾기
        for (st = 0; st < W; ++st)
        {
            if (board[i][st] == 1)
                break;
        }

        wallCnt = 1;
        for (int j = st + 1; j < W; ++j)
        {
            if (board[i][j] == 1 && wallCnt == 1)
            {
                answer += holeCnt;
                holeCnt = 0;
            }
            else if (board[i][j] == 1)
            {
                wallCnt = 1;
            }
            else if (board[i][j] == 0)
            {
                holeCnt += 1;
            }
        }
        
    }

    cout << answer << "\n";
    return 0;
}