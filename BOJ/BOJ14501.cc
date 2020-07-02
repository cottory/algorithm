#define IMPOSSIBLE -999999999
#define LENGTH first
#define REVENUE second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
vector<pii> works;
int dp[15][15000];

int func(int revenue, int idx) {
    if (idx >= N + 1) {
        return IMPOSSIBLE;
    }
    else if (idx == N) {
        return 0;
    }

    if (dp[idx][revenue] != -1) 
        return dp[idx][revenue];
    
    int ret = max(func(revenue + works[idx].REVENUE, idx + works[idx].LENGTH) + works[idx].REVENUE,
                  func(revenue, idx + 1));
    
    return dp[idx][revenue] = ret;
}

int main(void) {

    cin >> N;
    for (int t,r,i = 0; i < N; ++i) {
        cin >> t >> r;
        works.push_back(make_pair(t,r));
    }
    
    memset(dp, -1, sizeof(dp));
    func(0,0);
    cout << dp[0][0] << "\n";
    return 0;
}