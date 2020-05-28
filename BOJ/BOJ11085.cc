#define tiii tuple<int,int,int>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int P,W,C,V;
vector<int> parent;
priority_queue<tiii> pq;

int find(int node) {
    if (parent[node] == node) return node;
    else return parent[node] = find(parent[node]);
}
void _union(int c1, int c2) {
    parent[c2] = c1;
}

int kruskal() {

    int ret = 0;

    while (!pq.empty()) {

        tiii now = pq.top(); pq.pop();
        ret = get<0>(now);
        int n1 = get<1>(now);
        int n2 = get<2>(now);
        int c1, c2;

        c1 = find(n1);
        c2 = find(n2);

        if (c1 != c2) {
            _union(c1,c2);
        }

        if (find(C) == find(V)) 
            break;
    }
    return ret;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> P >> W >> C >> V;
    parent.resize(P,0);

    for (int i = 0; i < P; ++i)
        parent[i] = i;

    for (int st,en,w,i = 0; i < W; ++i) {
        cin >> st >> en >> w;
        pq.push(make_tuple(w,st,en));
    }

    cout << kruskal() << "\n";
    return 0;
}