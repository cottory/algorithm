#define NOT_USED 987654321
#define NMAX 2005
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N, dp[NMAX][NMAX];

int isPossible(int l, int r, int position)
{
    if (dp[l][position] == dp[position+1][r]) return 0;
    else if (dp[l][position] > dp[position+1][r]) return 1;
    else return 2;
}
int binarySearch(int l, int r)
{
    int st, en, mid;

    st = l;
    en = r;

    while (st < en)
    {
        mid = (st + en)/ 2;
        int ret = isPossible(l, r, mid);

        if (ret == 0) return mid;
        else if (ret == 1) en = mid;
        else st = mid + 1;
    }

    return -1;
}
int func(vector<int>& cookie, int l, int r)
{
    //기저 사례
    if (l > r)
        return NOT_USED;
        
    if (dp[l][r] != NOT_USED)
        return dp[l][r];

    int ret = func(cookie, l, r- 1) + cookie[r];
    return dp[l][r] = ret;
}
int solution(vector<int> cookie) {
    int answer = 0;
    N = cookie.size();

    for (int i = 0; i < NMAX; ++i)
        fill(dp[i], dp[i] + NMAX, NOT_USED);

    for (int i = 0; i < N; ++i)
        dp[i][i] = cookie[i];    

    //dp[][] 계산
    for (int st = 0; st < N-1; ++st)
    for (int en = st + 1; en < N; ++en)
        func(cookie,st,en);

    //solve
    for (int left = 0; left < N-1; ++left)
    for (int right = left+1; right < N; ++right)
    {
        int ret = binarySearch(left, right);
        if (ret >= 0)
            answer = max(answer, dp[left][ret]);
    }

    return answer;
}