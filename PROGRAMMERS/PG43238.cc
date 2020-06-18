#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isPossible(int n, vector<int>& times, ll time) {
    ll ret = 0;
    for (int t : times) {
        ret += (time / t);
    }
    return ret >= n ? true: false;
}

long long solution(int n, vector<int> times) {
    long long answer = __LONG_LONG_MAX__;
    ll st, en, mid;
    sort(times.begin(), times.end());
    st = 1;
    en = (ll)times.back() * (ll)n;
    
    while (st < en) {
        mid = (st + en) / 2;
        if (isPossible(n,times,mid)) {
            answer = min(answer,mid);
            en = mid;
        }
        else {  
            st = mid + 1;
        }
    }

    return answer;
}