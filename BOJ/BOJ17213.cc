#include <iostream>
using namespace std;

int N, M;
int ans, pick;

void solve(int idx, int rest) {
    if (idx == N) {
        if (rest == 0) 
            ans += 1;
        return;
    }    

    if (rest == 0) {
        ans += 1;
        return;
    }

    for (int pick_num = 0; pick_num <= rest; ++pick_num)
        solve(idx + 1, rest - pick_num);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    pick = M-N;

    solve(0, pick);

    cout << ans << "\n";
    return 0;
}