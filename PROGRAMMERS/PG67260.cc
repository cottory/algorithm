#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int N;
vector<bool> visited;
vector<int> before,nxt;
vector<vector<int>> graph;
queue<int> q;
set<int> waitingList;

void bfs(int node)
{
    q.push(node);
    visited[node] = true;
    if (before[node] != -1) 
        return;

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        //1-1. now때문에 방문할 수 없었던 nxtNode 봉인 해제
        int nxtNode = nxt[now];
        if (nxtNode != -1)
            before[nxtNode] = -1;
        
        //1-2. now때문에 방문할 수 없었던 nxtNode 봉인 해제
        //어차피 큐에 들어갈 수 있었던 노드이기 때문에 waitingList에서 지우고 바로 inQueue
        if (waitingList.find(nxtNode) != waitingList.end())
        {
            waitingList.erase(nxtNode);
            visited[nxtNode] = true;
            q.push(nxtNode);   
        }

        //일반 BFS처럼 인접 노드 탐색
        for (int adjNode : graph[now])
        {
            if (visited[adjNode] == true)
                continue;

            //방문할 수 있는 노드지만, 선-후 관계 때문에 못 들어간다면 waitingList에 inQueue
            //나중에 '선'의 위치에 있는 노드를 방문할 때 waitingList에서 꺼내줍니다.
            if (before[adjNode] != -1)
            {
                waitingList.insert(adjNode);
            }
            else
            {
                //before[adjNode] == -1
                visited[adjNode] = true;
                q.push(adjNode);                
            }
        }
    }
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    
    N = n;
    bool answer = true;

    graph.resize(N);
    before.resize(N,-1);
    nxt.resize(N,-1);
    visited.resize(N,false);

    for (vector<int> v : path)
    {
        int src = v[0];
        int dst = v[1];
        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }

    for (vector<int> v : order)
    {
        int first = v[0];
        int second = v[1];
        before[second] = first;
        nxt[first] = second;
    }

    bfs(0);

    for (int i = 0; i < N; ++i)
        if (visited[i] == false) return false;
    
    return answer;
}