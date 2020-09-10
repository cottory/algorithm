#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int ROW_SIZE = 4;
int dp[2][ROW_SIZE];

void print()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < ROW_SIZE; ++j)
            cout << dp[i][j] << " ";
        
        cout << endl;
    }
}

int solution(vector<vector<int> > land)
{
    int answer = 0;

    memset(dp,0,sizeof(dp));

    for (int i = 0; i < ROW_SIZE; ++i)
        dp[0][i] = land[0][i];

    for (int i = 1; i < land.size(); ++i)
    {
        for (int j = 0; j < ROW_SIZE; ++j)
        {
            for (int nxt = 0; nxt < ROW_SIZE; ++nxt)
            {
                if (nxt == j) 
                    continue;

                dp[i % 2][j] = max(dp[i % 2][j], dp[(i-1) % 2][nxt] + land[i][j]);
            }
        }
    }

    for (int i = 0; i < 2; ++i)
    for (int j = 0; j < ROW_SIZE; ++j)
        answer = max(answer,dp[i][j]);

    return answer;
}