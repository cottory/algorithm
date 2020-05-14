#define Y first
#define X second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <set>
using namespace std;

typedef struct Edge {
    int weight, src, dst;
    Edge(int w, int s, int d) : weight(w), src(s), dst(d) {}
}Edge;

typedef struct Comp {
    bool operator()(Edge e1, Edge e2) {
        return (e1.weight > e2.weight);
    }
}Comp;

int N, H, cnt;
int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

vector<vector<int> > component;
vector<vector<bool> > trip;
priority_queue<Edge, vector<Edge>, Comp> pq;

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < N);
}
void _union(vector<int>& parent, int node1, int node2) {
    parent[node1] = node2;
}

int _find(vector<int>& parent, int node) {
    if (parent[node] == node) return node;
    else return parent[node] = _find(parent, parent[node]);
}

int kruskal() {

    int ret = 0;
    int pick = 0;
    vector<int> parent(cnt + 1);
    for (int i = 0; i < parent.size(); ++i)
        parent[i] = i;

    while (pick != cnt - 1) {
        
        if (!pq.empty()) {
            Edge now = pq.top(); pq.pop();

            int src = now.src;
            int dst = now.dst;

            int compo1 = _find(parent, src);
            int compo2 = _find(parent, dst);

            if (compo1 != compo2) {
                _union(parent, compo1, compo2);
                ret += now.weight;
                pick += 1;
            }        
        }
    }

    return ret;
}

void bfs(vector<vector<int>>& land, int y, int x, int componentNumber) {

    queue<pii> q;
    q.push({y,x});
    component[y][x] = componentNumber;

    while (!q.empty()) {
        pii now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (isSafe(ny,nx) && !trip[ny][nx] && abs(land[now.Y][now.X] - land[ny][nx]) <= H )
            {
                trip[ny][nx] = true;
                component[ny][nx] = componentNumber;
                q.push({ny,nx});
            }
        }
    }
    return ;
}

priority_queue<Edge, vector<Edge>, Comp> getEdge(vector<vector<int>>& land) {

    priority_queue<Edge, vector<Edge>, Comp> ret;

    for (int y = 0; y < N; ++y)
    for (int x = 0; x < N; ++x) {
        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (isSafe(ny,nx) && (component[ny][nx] != component[y][x])) {
                int edge = abs(land[ny][nx] - land[y][x]);
                ret.push(Edge(edge, component[y][x], component[ny][nx]));
            }
        }
    }

    return ret;
}

int solution(vector<vector<int>> land, int height) {
    int answer = 0;
    N = land.size();
    H = height;

    component.resize(N + 5, vector<int>(N + 5,-1));
    trip.resize(N + 5, vector<bool>(N + 5,false));

    //getComponent
    cnt = 0;
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
        if (!trip[i][j]) {
            trip[i][j] = true;
            bfs(land,i,j,cnt);
            cnt++;
        }
    }

    pq = getEdge(land);

    answer = kruskal();   
    return answer;
}