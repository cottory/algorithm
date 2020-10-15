#define Tuple tuple<int,int,int>
#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <tuple>
using namespace std;

int N,C;
vector<Pair> fields;
vector<int> parent;
priority_queue<Tuple> pq;

void _union(int f1, int f2)
{
    parent[f2] = f1;
    return;
}

int find(int node)
{
    if (parent[node] == node) return node;
    else return parent[node] = find(parent[node]);
}

int kruskal()
{
    parent.resize(N,0);
    for (int i = 0; i < N; ++i)
        parent[i] = i;
    
    int pick = 0;
    int result = 0;
    bool isEmpty = false;
    

    while (!pq.empty() && pick != N-1)
    {
        int dist,f1,f2;
        Tuple now = pq.top(); pq.pop();

        tie(dist,f1,f2) = now;
        dist = -dist;

        int c1 = find(f1);
        int c2 = find(f2);

        if (c1 != c2)
        {
            _union(c1,c2);
            pick += 1;
            result += dist;
        }
    }

    if (pick == N-1) return result;
    else return -1;    
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C;

    //각 필드의 좌표
    for (int i = 0; i < N; ++i)
    {
        int y,x;
        cin >> y >> x;
        fields.push_back(make_pair(y,x));
    }

    int fSize = fields.size();
    for (int i = 0; i < fSize - 1; ++i)
    {
        for (int j = i+1; j < fSize; ++j)
        {
            int y1,x1,y2,x2;
            y1 = fields[i].Y;
            x1 = fields[i].X;
            y2 = fields[j].Y;
            x2 = fields[j].X;

            int dist = abs(y1-y2) * abs(y1-y2) + abs(x1-x2) * abs(x1-x2); 
            
            if (dist >= C)
            {
                pq.push(make_tuple(-dist,i,j));
            }             
        }
    }

    cout << kruskal() << "\n";
    return 0;
}