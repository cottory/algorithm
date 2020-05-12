#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> dp[21];
vector<int> func(int n)
{
    if (n == 1) 
        return dp[n] = vector<int>(1,0);

    if (dp[n].size() != 0)
        return dp[n];

    vector<int> ret, before = func(n-1);
    int token = 0;

    for (int loop = 0; loop < before.size(); ++loop)
    {
        ret.push_back(token);
        ret.push_back(before[loop]);
        token = !token;
    }

    ret.push_back(1);
    return dp[n] = ret;
}

vector<int> solution(int n) {
    vector<int> answer;
    fill(dp, dp + 21, vector<int>(0));
    
    answer = func(n);
    return answer;
}