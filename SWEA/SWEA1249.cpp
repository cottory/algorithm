#define IMPOSSIBLE 987654321
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

typedef struct token
{
    int y, x, time;
    token(int yy, int xx, int ttime) : y(yy), x(xx), time(ttime) {}
}token;

typedef struct Comp
{
    bool operator()(token t1, token t2) 
    {
        if (t1.time == t2.time)
        {
            if (t1.y == t2.y)
            {
                return (t1.x > t2.x);
            }
            else 
            {
                return (t1.y > t2.y);
            }
        }
        else 
        {
            return (t1.time > t2.time);
        }
    }
}Comp;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

bool safe(int y, int x, int nSize)
{
    return (0 <= y && y < nSize && 0 <= x && x < nSize);
}

int bfs(vector<vector<int> > &graph, int nSize)
{
    vector<vector<int> > dist(nSize,vector<int>(nSize,IMPOSSIBLE));
    priority_queue<token, vector<token>, Comp> pq;

    dist[0][0] = 0;
    pq.push(token(0,0,0));

    while (!pq.empty())
    {
        token now = pq.top(); pq.pop();

        for (int dir = 0; dir <4; ++dir)
        {
            int ny = now.y + dy[dir];
            int nx = now.x + dx[dir];

            if (safe(ny,nx,nSize))
            {
                if (dist[ny][nx] > dist[now.y][now.x] + graph[ny][nx])
                {
                    dist[ny][nx] = dist[now.y][now.x] + graph[ny][nx];
                    pq.push(token(ny,nx,dist[ny][nx]));
                }
            }
        }
        
    }

    return dist[nSize-1][nSize-1];
    
}
int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        vector<vector<int> > graph;
        vector<string> inputData;

        cin >> N;
        graph.resize(N,vector<int>(N,0));

        for (int loop = 0; loop < N; ++loop)
        {
            string s;
            cin >> s;
            inputData.push_back(s);
        }

        for (int row = 0; row < inputData.size(); ++row)
        {
            for (int col = 0; col < inputData[row].size(); ++col)
            {
                graph[row][col] = inputData[row][col] - '0';
            }
        }
        
        cout << "#" << test_case << " " << bfs(graph,N) << "\n";
	}
	return 0;
}