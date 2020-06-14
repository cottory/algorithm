#include <string>
#include <vector>
using namespace std;
vector<vector<int> > ans;

void solve(int n, int st, int en) {
    if (n == 0) {
        return;
    }
    else {
        int rest = 3 - (st + en);
        solve(n-1, st, rest);
        //n번째 원판이동
        vector<int> now;
        now.push_back(st+1);
        now.push_back(en+1);
        ans.push_back(now);
        solve(n-1,rest,en);
    }
}
vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    solve(n,0,2);
    answer = ans;
    return answer;
}