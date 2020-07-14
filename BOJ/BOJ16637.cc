#define PLUS 0
#define MINUS 1
#define MULTIPLY 2
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

int N;
ll ans = -9987654321;
string s;
vector<int> opertr, opernd; //operator, operand
vector<bool> used;

ll calculate(ll operand1, int _operator, int operand2) {
    if (_operator == PLUS) return operand1 + operand2;
    else if (_operator == MINUS) return operand1 - operand2;
    else return operand1 * operand2;
}
ll solve() {

    int oSize = opernd.size();
    ll init_number = opernd[0];
    int idx = 0;
    if (used[0]) {
        init_number = calculate(init_number, opertr[0], opernd[1]);
        idx += 2;
    }
    else {
        idx += 1;
    }
    
    //opertr[N-1]과 opernd[N] 조합해서 숫자 만들기
    while (idx < oSize) {
        if (!used[idx]) {
            init_number = calculate(init_number, opertr[idx-1], opernd[idx]);
            idx += 1;
        }
        else {
            ll ret = calculate(opernd[idx], opertr[idx], opernd[idx+1]);
            init_number = calculate(init_number, opertr[idx-1], ret);
            idx += 2;
        }
    }
    
    return init_number;
}
void combination(int idx) {
    if (idx == N/2 + 1) {
        ll result = solve();
        ans = max(result, ans);
        return;
    }
    else if (idx == (N/2 + 1) - 1) {
        //마지막 숫자인 경우
        combination(idx + 1);
        return;
    }

    if (!used[idx] && !used[idx+1]) {
        //괄호 셋팅
        used[idx] = true;
        used[idx + 1] = true;
        combination(idx + 2);
        used[idx + 1] = false;
        used[idx] = false;
    }

    combination(idx + 1);
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> s;

    for (char c : s) {
        if ('0' <= c && c <= '9') {
            int num = c - '0';
            opernd.push_back(num);
        }
        else {
            if (c == '+') opertr.push_back(PLUS);
            else if (c == '-') opertr.push_back(MINUS);
            else opertr.push_back(MULTIPLY);
        }
    }

    used.resize(N/2 + 1, false);
    combination(0);
    cout << ans << "\n";
    return 0;
}