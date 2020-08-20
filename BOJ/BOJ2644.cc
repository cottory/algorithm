#define PERSON first
#define CNT second
#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N,M,x,y;
vector<int> child[105];
int parent[105];
int trip[105];

int bfs(int x, int y)
{
    queue<Pair> q;
    q.push(make_pair(x,0));
    trip[x] = 1;
    
    while (!q.empty())
    {
        Pair now = q.front(); q.pop();
        if (now.PERSON == y)
        {
            return now.CNT;
        }

        //부모에서 SEARCH
        if (parent[now.PERSON])
        {
            int nxt = parent[now.PERSON];
            if (!trip[nxt]) {
                trip[nxt] = true;
                 q.push(make_pair(nxt,now.CNT + 1)); 
            }
        }

        //자식에서 SEARCH
        for (int i = 0; i < child[now.PERSON].size(); ++i)
        {
            int nxt = child[now.PERSON][i];    
            if (trip[nxt]) continue;
            
            trip[nxt] = 1;
            q.push(make_pair(nxt,now.CNT + 1));
        }
    
    }

    return -1;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    cin >> x >> y;
    cin >> M;
    for (int par,chi,i = 0; i < M; ++i)
    {
        cin >> par >> chi;  //parent, child;
        parent[chi] = par;
        child[par].push_back(chi);
    }
    
    cout << bfs(x,y) << "\n";
    return 0;
}