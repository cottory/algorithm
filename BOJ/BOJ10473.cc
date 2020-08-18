#define Y first
#define X second
#define DIST first
#define NODE_NUMBER second
#define NODE pair<double, double>
#define Pair pair<double, int>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

NODE st,en;
int N;
const double INF = 987654321.0;
vector<NODE> v;
vector<double> dist;
priority_queue<Pair> pq;

double getDistance(int n1, int n2) {
    return sqrt((pow((v[n1].Y - v[n2].Y),2)) + (pow((v[n1].X - v[n2].X),2)));
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> st.Y >> st.X;
    cin >> en.Y >> en.X;
    cin >> N;

    v.resize(N+5);
    dist.resize(N+5);

    v[0] = {st.Y,st.X};
    v[N+1] = {en.Y,en.X};
    fill(dist.begin(), dist.end(), INF);

    for (int i = 1; i <= N; ++i)
    {
        cin >> v[i].Y >> v[i].X;
    }

    dist[0] = 0.0;
    pq.push({0.0,0});
    bool isStart = true;

    while (!pq.empty())
    {
        Pair now = pq.top();
        pq.pop();

        if (dist[now.NODE_NUMBER] < now.DIST)
            continue;

        for (int nxt = 1; nxt <= N+1; ++nxt)
        {
            if (now.NODE_NUMBER == nxt) continue;

            double useCanon = 2 + abs(getDistance(now.NODE_NUMBER,nxt) - 50) / 5;
            double justWalk = getDistance(now.NODE_NUMBER,nxt) / 5;
            double ret = isStart ? justWalk : min(justWalk,useCanon);

            if (dist[nxt] > dist[now.NODE_NUMBER] + ret)
            {
                dist[nxt] = dist[now.NODE_NUMBER] + ret;
                pq.push({dist[now.NODE_NUMBER] + ret,nxt});
            }
        }

        isStart = false;
    }       

    cout << fixed;
    cout.precision(6);
    cout << dist[N+1] << endl;
    return 0;
}

