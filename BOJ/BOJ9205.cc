#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

const int NMAX = 100 + 3;
const int INF = 387654321;

int N;
int dist[NMAX][NMAX];
bool visited[NMAX];
vector<Pair> v;

int getDistance(Pair node1, Pair node2) 
{
    int y1,x1,y2,x2,result = 0;
    y1 = node1.Y;
    x1 = node1.X;

    y2 = node2.Y;
    x2 = node2.X;

    result += abs(y1-y2);
    result += abs(x1-x2);
    return result;
}

bool bfs()
{
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty())
    {
        int now = q.front(); q.pop();
        if (now == N+1)
            return true;

        for (int nxt = 0; nxt < N+2; ++nxt)
        {
            if (visited[nxt] == false && getDistance(v[now],v[nxt]) <= 1000)
            {
                q.push(nxt);
                visited[nxt] = true;
            }
        }
    }

    return false;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int test_case;
    cin >> test_case;

    for (int loop = 0; loop < test_case; ++loop)
    {
        v.clear();
        //dist ÃÊ±âÈ­
        for (int i = 0; i < NMAX; ++i)
            fill(dist[i], dist[i] + NMAX, INF);

        for (int i = 0; i < NMAX; ++i)
            dist[i][i] = 0;

        fill(visited,visited + NMAX, false);

        cin >> N;
        for (int y,x,i = 0; i < N+2; ++i)
        {   
            cin >> y >> x;
            v.push_back({y,x});
        }
           
        for (int mid = 0; mid < N+2; ++mid)
        {
            for (int i = 0; i < N+2; ++i)
            {
                for (int j = 0; j < N+2; ++j)
                {
                    int i2mid = getDistance(v[i],v[mid]);
                    int mid2j = getDistance(v[mid],v[j]);

                    if (dist[i][j] > i2mid + mid2j)
                    {
                        dist[i][j] = i2mid + mid2j;
                    }
                }
            }
        }

        bool isArrived = bfs();

        if (isArrived == true)  cout << "happy\n";
        else cout << "sad\n";
    }

    return 0;
}