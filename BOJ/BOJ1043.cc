#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//K: 구라인 거 아는 사람의 수
int N, M, K;
vector<bool> knownFake;
vector<vector<bool>> graph;
vector<vector<int>> partys;

int main(void) 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;

    knownFake.resize(N,false);
    graph.resize(N,vector<bool>(N,false));

    for (int loop = 0; loop < K; ++loop)
    {
        int personNumber;
        cin >> personNumber;
        personNumber--;
        knownFake[personNumber] = true;
    }

    for (int loop = 0; loop < M; ++loop)
    {
        int num;
        cin >> num;
        vector<int> connections;
        for (int loop2 = 0; loop2 < num; ++loop2)
        {
            int personNumber;
            cin >> personNumber;
            personNumber--;
            connections.push_back(personNumber);
        }

        partys.push_back(connections);

        int cSize = connections.size();
        for (int i = 0; i < cSize-1; ++i)
        {
            for (int j = i+1; j < cSize; ++j)
            {
                int p1 = connections[i];
                int p2 = connections[j];
                if (knownFake[p1] || knownFake[p2])
                {
                    knownFake[p1] = true;
                    knownFake[p2] = true;
                }
                
                graph[p1][p2] = true;
                graph[p2][p1] = true;
            }
        }
    }

    for (int loop = 0; loop < N; ++loop)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int adj = 0; adj < N; ++adj)
            {
                if (graph[i][adj] && knownFake[adj])
                    knownFake[i] = true;
            }
        }
    }

    int ans = 0;

    for (vector<int> party : partys)
    {
        bool isPossible = true;
        for (int participant : party)
        {
            if (knownFake[participant])
            {
                isPossible = false;
                break;
            } 
        }

        if (isPossible)
            ans += 1;
    }

    cout << ans << endl;
    return 0;
}