#define tiii tuple<int,int,int>
#include <vector>
#include <queue>
#include <tuple>
#include <queue>
using namespace std;

vector<int> parent;
vector<vector<int> > graph;
priority_queue<tiii> pq;

int find(int node) {
    if (parent[node] == node) return node;
    else return parent[node] = find(parent[node]);
}

void uunion(int c1, int c2) {
    parent[c2] = c1;
    return;
}

int kruskal(int n) {
    
    int costSum = 0;
    int cnt = 0;
    parent.resize(n);
    for (int i = 0; i < n; ++i)
        parent[i] = i;
    
    while (cnt != n-1) {
        
        if (!pq.empty()) {
            tiii now = pq.top(); pq.pop();
            
            int cost = -get<0>(now);
            int node1 = get<1>(now);
            int node2 = get<2>(now);

            int c1 = find(node1);
            int c2 = find(node2);

            if (c1 != c2) {
                cnt += 1;
                costSum += cost;
                uunion(c1,c2);
            }
        }
    }

    return costSum;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;    
    for (auto cost : costs) 
        pq.push(make_tuple(-cost[2], cost[0], cost[1]));

    return answer = kruskal(n);
}