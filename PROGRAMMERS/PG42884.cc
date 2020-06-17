#define EN first
#define ST second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
priority_queue<pii> pq;

int solution(vector<vector<int>> routes) {
    int answer = 0;

    for (int i = 0; i < routes.size(); ++i) {
        int st = routes[i][0];
        int en = -routes[i][1];
        pq.push(make_pair(en,st));
    }

    int cover_st, cover_en;
    cover_st = cover_en = -50000;
    while (!pq.empty()) {
        pii now = pq.top(); pq.pop();
        now.EN = -now.EN;
        if (cover_en < now.ST) {
            answer += 1;
            cover_st = now.ST;
            cover_en = now.EN;
        }
        else {
            continue;
        }
    }

    return answer;
}