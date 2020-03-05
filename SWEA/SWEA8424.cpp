#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, cnt = 0;
        vector<vector<int> > graph;
        vector<int> finished, visited;
        queue<int> candidate;

        //input
        cin >> N;
        graph.resize(N);
        finished.resize(N,0);
        visited.resize(N,0);

        for (int src,dst,loop = 0; loop < N; ++loop)
        {
            cin >> src >> dst;
            src--; dst--;
            graph[src].push_back(dst);
            graph[dst].push_back(src);

            finished[src]++;
            finished[dst]++;
        }        
        
        //solve
        for (int node = 0; node < N; ++node)
        {
            if (!visited[node] && (finished[node] == 1)) 
            {
                candidate.push(node);

                while (!candidate.empty())
                {
                    int now = candidate.front(); candidate.pop();

                    if (!visited[now] && (finished[now] == 1)) 
                    {
                        visited[now] = 1;
                        cnt++;

                        for (int nxt : graph[now])
                        {
                            finished[nxt]--;
                            candidate.push(nxt);
                        }   
                    }
                }
            }
        }

        cout << "#" << test_case << " " << N-cnt << "\n";

	}
	return 0;
}