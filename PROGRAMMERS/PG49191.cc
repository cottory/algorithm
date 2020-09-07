#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int NMAX = 100 + 3;
int dp[NMAX][NMAX];
int solution(int n, vector<vector<int>> results) {
    int answer = 0;

    for (vector<int> result : results)
    {
        int winner = result[0];
        int loser = result[1];
        dp[winner][loser] = 1;
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int from = 1; from <= n; ++from)
        {
            for (int to = 1; to <= n; ++to)
            {
                if (dp[from][k] && dp[k][to])
                    dp[from][to] = 1;
            }
        }
    }    

    for (int from = 1; from <= n; ++from)
    {
        int count = 0;
        for (int to = 1; to <= n; ++to)
        {
            if (dp[from][to] || dp[to][from]) 
                count += 1;
        }

        if (count == n-1)
            answer += 1;
    }

    return answer;
}