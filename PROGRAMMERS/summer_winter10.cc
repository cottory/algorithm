#define NOT_USED 987654321
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
    
//DP[N] = max(DP[N-1], DP[N-2] + STICKER[N])

int N;
int dp[2][100005];
int func(vector<int>& sticker, int n, int flag)
{
    if (dp[flag][n] != NOT_USED)
        return dp[flag][n];
    
    //기저 사례s
    if (n == N-1)
    {
        if (flag) 
            return dp[flag][n] = func(sticker, n-1,flag);
        else
            return dp[flag][n] = max(func(sticker, n-1, flag), func(sticker, n-2, flag) + sticker[n]);
    }

    int ret = max(func(sticker, n-1, flag), func(sticker, n-2, flag) + sticker[n]);
    
    return dp[flag][n] = ret;
}
int solution(vector<int> sticker)
{
    int answer = 0;
    N = sticker.size();
    
    for (int i = 0; i < 2; ++i)
        fill(dp[i], dp[i] + 100005, NOT_USED);

    dp[0][0] = 0;
    dp[0][1] = sticker[1];
    dp[1][0] = sticker[0];
    dp[1][1] = sticker[0];

    for (int n = 2; n < N; ++n)
    {
        for (int flag = 0; flag < 2; ++flag)
        {   
            if (flag && n == N-1) 
                dp[flag][n] = dp[flag][n-1];
            else
                dp[flag][n] = max(dp[flag][n-1], dp[flag][n-2] + sticker[n]);
        }
    }

    answer = max(dp[0][N-1], dp[1][N-1]);
    return answer;
}