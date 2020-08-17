#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <algorithm>
#define TUPLE tuple<int,int,int>
using namespace std;

const int INF = 1 << 30;
const int NMAX = 105;
const int COST_MAX = 10005;
int T,N,M,K;
int dp[NMAX][COST_MAX];
vector<TUPLE> graph[NMAX];
int main() {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;

    while (T--)
    {
        cin >> N >> M >> K;
        
        for (int i = 0; i < NMAX; ++i) {
            fill(dp[i], dp[i] + COST_MAX, INF);
            graph[i].clear();
        }
        
        dp[1][0] = 0;

        for (int src,dst,cost,time,i = 0; i < K; ++i)
        {
            cin >> src >> dst >> cost >> time;
            graph[src].push_back(make_tuple(dst,cost,time));
        }

        //time, city_idx, cost
        priority_queue<TUPLE> pq;
        pq.push(make_tuple(0,1,0)); // 0초만에, 1번 마을로, 0원에 가는 것으로 start
        bool isFindPath = false;

        while (!pq.empty())
        {
            TUPLE now = pq.top(); pq.pop();
            int cur_time, cur_idx, cur_cost;
            tie(cur_time, cur_idx, cur_cost) = now;
            cur_time = -cur_time;
            
            // 주어진 cost 내에서 time이 작은 순으로 보고있기 때문에 N에 도달하는 즉시 출력하면 됨.
            if (cur_idx == N) {
                isFindPath = true;
                cout << cur_time << "\n";
                break;
            }

            if (dp[cur_idx][cur_cost] < cur_time)  // 이미 city에 cost를 써서 더 빨리 도달한 경우가 있을 경우
                continue;

            for (int i = 0; i < graph[cur_idx].size(); ++i)
            {
                int nxt_idx = get<0>(graph[cur_idx][i]);
                int nxt_cost = cur_cost + get<1>(graph[cur_idx][i]);
                int nxt_time = cur_time + get<2>(graph[cur_idx][i]);

                if (nxt_cost > M) // 예산을 초과했을 경우
                    continue;

                if (dp[nxt_idx][nxt_cost] > nxt_time) // 더 좋은 경로를 찾은 경우
                {
                    dp[nxt_idx][nxt_cost] = nxt_time;
                    pq.push(make_tuple(-nxt_time,nxt_idx,nxt_cost));
                }
            } 
        }

        if (!isFindPath) {
            cout << "Poor KCM\n";
        }

    }

    return 0;
}