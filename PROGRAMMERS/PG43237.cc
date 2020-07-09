#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

bool isAnswer(vector<int>& budgets, const int budget, const int upper) {
    int total = 0;
    for (int p : budgets) {
        if (budget >= p) total += p;
        else total += budget;
    }

    return total <= upper ? true : false;
}
int solution(vector<int> budgets, int M) {
    ll answer = -1;

    ll total = 0;
    ll maxv = -1;
    for (ll p : budgets) {
        total += p;
        maxv = max(p, maxv);
    }

    if (total <= M) {
        answer = maxv;
    }
    else {
        // minv,maxv;
        maxv += 1;
        ll mid, minv;
        minv = 0;
        
        while (minv < maxv) {
            mid = (minv + maxv) / 2;

            if (isAnswer(budgets, mid, M)) {
                minv = mid + 1;
                answer = max(answer, mid);
            }
            else {
                maxv = mid;
            }
        }
    }

    return (int)answer;
}