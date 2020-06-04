#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

ll N,M;
vector<ll> jewelry;

bool solve(ll count) {
    int ret = 0;

    for (ll amount : jewelry) {
        ret += (amount / count);
        if (amount % count)
            ret += 1;
    }
    
    if (ret <= N) return true;
    else return false;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    ll low,high,mid,result;
    low = 1;
    high = -1;
    result = __LONG_LONG_MAX__;

    for (int loop = 0; loop < M; ++loop) {
        ll height;
        cin >> height;
        jewelry.push_back(height);
        high = max(high,height);
    }
    
    //이분탐색 범위가 [low,high) 이므로
    //=> [low,high]로 맞춰줌
    high += 1;  

    while (low < high) {
        mid = (low + high) / 2;

        if (solve(mid)) {
            high = mid;
            result = min(result,mid);
        } 
        else {
            low = mid + 1;
        }
    }

    cout << result << "\n";
    return 0;
}