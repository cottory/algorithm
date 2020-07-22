#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
const int WIDTH = 3;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N;

    //dp[2][3];
    int max_dp[2][WIDTH], min_dp[2][WIDTH], board[2][WIDTH];

    memset(max_dp, 0, sizeof(max_dp));
    memset(min_dp, 0, sizeof(min_dp));
    memset(board, 0, sizeof(board));

    for (int j = 0; j < WIDTH; ++j) 
        cin >> board[0][j];

    for (int i = 0; i < WIDTH; ++i) 
    {
        max_dp[0][i] = board[0][i];
        min_dp[0][i] = board[0][i];
    }
    
    for (int i = 0 ; i < N-1; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
            cin >> board[(i+1)%2][j];

        for (int j = 0; j < WIDTH; ++j)
        {
            if (j == 0) 
            {
                max_dp[(i+1) % 2][j] = board[(i+1)%2][j] + max(max_dp[i%2][j], max_dp[i%2][j+1]);
                min_dp[(i+1) % 2][j] = board[(i+1)%2][j] + min(min_dp[i%2][j], min_dp[i%2][j+1]);
            }
            else if (j == 1) 
            {
                int ret1 = max(max_dp[i%2][j-1], max_dp[i%2][j]);
                int ret2 = max(max_dp[i%2][j], max_dp[i%2][j+1]);
                max_dp[(i+1) % 2][j] = board[(i+1)%2][j] + max(ret1,ret2);

                ret1 = min(min_dp[i%2][j-1], min_dp[i%2][j]);                
                ret2 = min(min_dp[i%2][j], min_dp[i%2][j+1]);
                min_dp[(i+1) % 2][j] = board[(i+1)%2][j] + min(ret1,ret2);
            }
            else 
            {
                max_dp[(i+1) % 2][j] = board[(i+1)%2][j] + max(max_dp[i%2][j-1], max_dp[i%2][j]);
                min_dp[(i+1) % 2][j] = board[(i+1)%2][j] + min(min_dp[i%2][j-1], min_dp[i%2][j]);
            }
        }
    }

    int minv, maxv;
    minv = 987654321;
    maxv = -1;

    for (int i = 0; i < WIDTH; ++i) 
    {
        if (N % 2 == 0)
        {
            //dp[1][]에 결과
            maxv = max(maxv, max_dp[1][i]);    
            minv = min(minv, min_dp[1][i]);
        }
        else 
        {
            //dp[0][]에 결과
            maxv = max(maxv, max_dp[0][i]);    
            minv = min(minv, min_dp[0][i]);
        }
    }

    cout << maxv << " " << minv << "\n";
    return 0;
}