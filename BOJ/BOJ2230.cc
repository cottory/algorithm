#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int N;
ll M;
vector<int> v;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> M;

    for (int x,i = 0; i < N; ++i) {
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end());
    int st = 0, en = 0;
    ll ans = __LONG_LONG_MAX__;

    int vSize = v.size();
    while (en < vSize && st <= en) {
        ll candidate = v[en] - v[st];
        if (candidate >= M) {
            if (candidate < ans) {
                ans = candidate;
            }
            st++;
        }
        else {
            en++;
        } 
    }

    cout << ans << "\n";
    return 0;
}