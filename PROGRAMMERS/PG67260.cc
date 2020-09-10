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

        //1-1. now������ �湮�� �� ������ nxtNode ���� ����
        int nxtNode = nxt[now];
        if (nxtNode != -1)
            before[nxtNode] = -1;
        
        //1-2. now������ �湮�� �� ������ nxtNode ���� ����
        //������ ť�� �� �� �־��� ����̱� ������ waitingList���� ����� �ٷ� inQueue
        if (waitingList.find(nxtNode) != waitingList.end())
        {
            waitingList.erase(nxtNode);
            visited[nxtNode] = true;
            q.push(nxtNode);   
        }

        //�Ϲ� BFSó�� ���� ��� Ž��
        for (int adjNode : graph[now])
        {
            if (visited[adjNode] == true)
                continue;

            //�湮�� �� �ִ� �������, ��-�� ���� ������ �� ���ٸ� waitingList�� inQueue
            //���߿� '��'�� ��ġ�� �ִ� ��带 �湮�� �� waitingList���� �����ݴϴ�.
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