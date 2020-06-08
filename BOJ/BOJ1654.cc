#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int N, K;
vector<ll> line;
bool isPossible(ll len) {

    ll ret = 0;
    for (int i = 0; i < K; ++i) {
        ret += (line[i] / len);
    }
    return ret >= N;
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll lo, hi, mid, ans;
    lo = 0;
    hi = -1;
    ans = -1;

    cin >> K >> N;
    line.resize(K);

    for (int i = 0; i < K; ++i) {
        cin >> line[i];
        hi = max(hi, line[i]);
    }

    hi += 1;
    
    while (lo < hi) {

        mid = (lo + hi) / 2;

        if (isPossible(mid)) {
            lo = mid + 1;
            ans = max(ans,mid);
        }
        else {
            hi = mid;
        }
    }

    cout << ans << "\n";
    return 0;
}