#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int N;
vector<int> v;
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for (int x,i = 0; i < N; ++i) {
        cin >> x;
        v.push_back(x);
    }

    int ans = -1111111111;
    sort(v.begin(), v.end());
    do {
        int sum = 0;
        for (int i = 0; i < N-1; ++i) {
            sum += abs(v[i] - v[i+1]);
        }
        ans = max(ans,sum);
    } while(next_permutation(v.begin(), v.end()));

    cout << ans << "\n";
    return 0;
}