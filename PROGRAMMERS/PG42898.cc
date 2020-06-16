#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
vector<vector<int> > board, dp;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;

    board.resize(n,vector<int>(m,0));
    dp.resize(n,vector<int>(m,0));

    for (int i = 0; i < puddles.size(); ++i) {
        int x = puddles[i][0];
        int y = puddles[i][1];
        x--; y--;
        board[y][x] = 1;
    }

    for (int i = 0; i < n; ++i) {
        if (!board[i][0]) {
            dp[i][0] = 1;
        }
        else 
            break;
    }
    for (int j = 0; j < m; ++j) {
        if (!board[0][j]) {
            dp[0][j] = 1;
        }
        else 
            break;
    }
        
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            
            if (board[i][j]) {
                continue;
            }
            else {
                int upSide = 0, leftSide = 0;
                if (!board[i-1][j]) {
                    upSide = dp[i-1][j];
                }
                if (!board[i][j-1]) {
                    leftSide = dp[i][j-1];
                }
                dp[i][j] = ((upSide % MOD) + (leftSide % MOD)) % MOD;
            }
        }
    }

    answer = dp[n-1][m-1];
    return answer;
}