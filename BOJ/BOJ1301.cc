#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

int N;
ll dp[11][11][11][11][11][6][6];
int arr[11];

ll dfs(int one, int two, int three, int four, int five, int before, int bbefore) {

    ll ret = 0;

    if (one == 0 && two == 0 && three == 0 && four == 0 && five == 0)
        return 1;

    if (one < 0 || two < 0 || three < 0 || four < 0 || five < 0)
        return 0;

    if (dp[one][two][three][four][five][before][bbefore] != -1) 
        return dp[one][two][three][four][five][before][bbefore];

    if (one >= 1 && before != 1 && bbefore != 1) {
        ret = dfs(one-1,two,three,four,five,1,before);
    }

    if (two >= 1 && before != 2 && bbefore != 2) {
        ret += dfs(one,two-1,three,four,five,2,before);
    }

    if (three >= 1 && before != 3 && bbefore != 3) {
        ret += dfs(one,two,three-1,four,five,3,before);
    }

    if (four >= 1 && before != 4 && bbefore != 4) {
        ret += dfs(one,two,three,four-1,five, 4,before);
    }

    if (five >= 1 && before != 5 && bbefore != 5) {
        ret += dfs(one,two,three,four,five-1, 5,before);
    }

    return dp[one][two][three][four][five][before][bbefore] = ret;
}
int main(void) {
    
    memset(dp,-1,sizeof(dp));
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    cout << dfs(arr[0],arr[1],arr[2],arr[3],arr[4],-1,-1);
    return 0;
}