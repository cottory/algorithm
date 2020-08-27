#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int strLength;
vector<vector<int>> dp;
int solution(string s)
{
    int answer = 1;
    strLength = s.length();

    dp.resize(strLength + 5, vector<int>(strLength + 5,0));

    for (int i = 0; i < strLength; ++i)
        dp[i][i] = 1;

    for (int i = 0; i < strLength-1; ++i)
    {
        if (s[i] == s[i+1])
        {
            dp[i][i+1] = 1;
            answer = 2;
        }
    }

    for (int len = 3; len <= strLength; ++len)
    {
        for (int st = 0; st <= strLength - len; ++st)
        {
            int en = st + len - 1;
            if ((s[st] == s[en]) && dp[st+1][en-1])
            {
                dp[st][en] = 1;
                answer = max(answer,len);
            }
        }
    }

    return answer;
}