#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;


priority_queue<ll> pq;
long long solution(int n, vector<int> works) {
    long long answer = 0;

    for (int work : works) {
        pq.push(work);
    }
    
    bool isFinished = false;
    
    while (n--) {
        if (!pq.empty()) {
            ll top = pq.top(); pq.pop();
            if (top != 0) {
                pq.push(--top);
            }
        }
        else {
            isFinished = true;
            break;
        }
    }

    if (isFinished) answer = 0;
    else {
        while (!pq.empty()) {
            ll candidate = pq.top(); pq.pop();
            answer += (candidate * candidate);
        }
    }
    
    return answer;
}