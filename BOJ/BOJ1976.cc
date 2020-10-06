#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N,M;
vector<int> tripPath;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> myComponentNumber;

void bfs(int node, int componentNumber)
{    
    queue<int> q;
    q.push(node);
    myComponentNumber[node] = componentNumber;

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        for (int nxt = 0; nxt < N; ++nxt)
        {
            if (nxt == now)
                continue;
            else if (visited[nxt])
                continue;
            else if (graph[now][nxt] == 0)
                continue;

            visited[nxt] = true;
            myComponentNumber[nxt] = componentNumber;
            q.push(nxt);
        }

    }
}

void setComponent()
{
    int componentNumber = 1;
    for (int node = 0; node < N; ++node)
    {
        if (!visited[node])
        {
            visited[node] = true;
            bfs(node,componentNumber);
            componentNumber++;
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    
    graph.resize(N,vector<int>(N,0));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> graph[i][j];
        }
    }

    for (int node,loop = 0; loop < M; ++loop)
    {
        cin >> node;
        node--;
        tripPath.push_back(node);
    }


    //floyd
    for (int mid = 0; mid < N; ++mid)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (!graph[i][j] && graph[i][mid] && graph[mid][j])
                {
                    graph[i][j] = 1;
                }
            }
        }
    }

    //set Component
    visited.resize(N,false);
    myComponentNumber.resize(N,0);

    //bfs
    setComponent();

    if (M == 0)
    {
        cout << "YES\n";
    }
    else
    {
        int componentNumber = myComponentNumber[tripPath[0]];

        bool isPossible = true;

        for (int node : tripPath)
        {
            if (myComponentNumber[node] != componentNumber)
            {
                isPossible = false;
                break;
            }
        }

        if (isPossible) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}