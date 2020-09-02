#define Pair pair<int,int>
#define WEIGHT first
#define VALUE second
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int WEIGHT_MAX = 100005;
int N,K;

int dp[WEIGHT_MAX];
vector<Pair> items;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    memset(dp,0,sizeof(dp));

    for (int w,v,i = 0; i < N; ++i)
    {
        cin >> w >> v;
        items.push_back(make_pair(w,v));
    }
    
    for (int i = 0; i < N; ++i)
    {
        for (int weight = K; weight >= 0; --weight)
        {
            if (items[i].WEIGHT <= weight)
            {
                dp[weight] = max(dp[weight], dp[weight-items[i].WEIGHT] + items[i].VALUE);
            }
        }
    }

    cout << dp[K] << endl;
    return 0;
}