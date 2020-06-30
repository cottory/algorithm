#define START_TIME first
#define LEN second
#define tiii tuple<int,int,int>
#define pii pair<int,int>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <iostream>
using namespace std;
priority_queue<tiii> pq2;
priority_queue<pii> pq1;

int solution(vector<vector<int>> jobs) {
   
    for (int i = 0; i < jobs.size(); ++i) {
        int st = jobs[i][0];
        int len = jobs[i][1];
        pq1.push(make_pair(-st,-len));  //1.시작순서가 빠른대로, 2.길이가 짧은 작업먼저
    }

    int answer = 0;
    int hd_time = 0;

    while (!pq1.empty()) {
        
        pii now = pq1.top(); pq1.pop();
        now.START_TIME = -now.START_TIME;
        now.LEN = -now.LEN;

        if (hd_time < now.START_TIME) {
            hd_time = now.START_TIME + now.LEN;
            answer += now.LEN;
        } 
        else {  
            pq2.push(make_tuple(-now.LEN, -(now.START_TIME + now.LEN), -now.START_TIME));

            while (!pq1.empty() && (-pq1.top().START_TIME <= hd_time)) {
                pii nxt = pq1.top(); pq1.pop();
                nxt.START_TIME = -nxt.START_TIME;
                nxt.LEN = -nxt.LEN;
                pq2.push(make_tuple(-nxt.LEN, -(nxt.START_TIME + nxt.LEN), -nxt.START_TIME));
            }

            if (!pq2.empty()) {
                tiii candidate = pq2.top(); pq2.pop();
                int st = -get<2>(candidate);
                int len = -get<0>(candidate);
                
                int offset = hd_time - st;
                answer += offset;
                answer += len;
                hd_time += len;
            }

            //나머지 다시 pq1에 넣기
            while (!pq2.empty()) {
                tiii rollback = pq2.top(); pq2.pop();
                int st = get<2>(rollback);
                int len = get<0>(rollback);
                pq1.push(make_pair(st,len));
            }
        }
    }
    answer /= jobs.size();
    return answer;
}