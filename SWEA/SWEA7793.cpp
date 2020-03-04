#define pii pair<int,int>
#define Y first
#define X second
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef struct token
{
    //type: 0: 여신, 1: 악마
    int y, x, type, cnt;
    token(int yy, int xx, int ttype, int ccnt) : y(yy), x(xx), type(ttype), cnt(ccnt) {}
}token;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

bool safe(int y, int x, int ySize, int xSize) 
{
    return (0 <= y && y < ySize && 0 <= x && x < xSize);
}

int bfs(vector<string> &graph, int st_y, int st_x, int en_y, int en_x, int ySize, int xSize) 
{
    int ans = 0;
    bool isEscape = false;
    vector<vector<int> > trip[2];
    queue<token> q;

    for (int loop = 0; loop < 2; ++loop)
    {
        trip[loop].resize(ySize, vector<int>(xSize,0));
    }

    for (int row = 0; row < ySize; ++row)
    {
        for (int col = 0; col < xSize; ++col)
        {
            if (graph[row][col] == '*')
            {
                q.push({row,col,1,0});
                trip[1][row][col] = 1;
            }
        }
    }

    q.push({st_y,st_x,0,0});
    trip[0][st_y][st_x] = 1;

    while (!q.empty() && !isEscape)
    {
        int qSize = q.size();
        while (qSize--)
        {
            token now = q.front(); q.pop();

            //종료 조건
            if (now.y == en_y && now.x == en_x && now.type == 0)
            {
                isEscape = true;
                ans = now.cnt;
                break;
            }
            else
            {
                for (int dir = 0; dir < 4; ++dir)
                {
                    int ny = now.y + dy[dir];
                    int nx = now.x + dx[dir];

                    if (safe(ny,nx,ySize,xSize) && graph[ny][nx] != 'X')
                    {
                        if (now.type == 0) 
                        {
                            if (!trip[0][ny][nx] && !trip[1][ny][nx])
                            {
                                trip[now.type][ny][nx] = 1;
                                q.push({ny,nx,0,now.cnt + 1});
                            }
                        }
                        else if (now.type == 1) 
                        {
                            if (!trip[now.type][ny][nx] && graph[ny][nx] != 'D' && graph[ny][nx] != 'S')
                            {
                                trip[now.type][ny][nx] = 1;
                                q.push({ny,nx,1,0});
                            }
                        }
                    }
                }
            }
            
        }
    }

    if (isEscape) 
    {
        return ans;
    }
    else
    {
        return -1;
    }
    
}
int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N,M,ans = 0;
        int st_y, st_x, en_y, en_x;

        vector<string> map;

        cin >> N >> M;
        map.resize(N);
        
        for (int idx = 0; idx < N; ++idx)   
        {
            cin >> map[idx];
        }

        for (int row = 0; row < map.size(); ++row)
        {
            for (int col = 0; col < map[row].size(); ++col)
            {
                if (map[row][col] == 'S')
                {
                    st_y = row;
                    st_x = col;
                }
                else if (map[row][col] == 'D')
                {
                    en_y = row;
                    en_x = col;
                }
            }
        }
    
        ans = bfs(map, st_y, st_x, en_y, en_x, N, M);
        cout << "#" << test_case << " ";

        if (ans == -1) 
        {
            cout << "GAME OVER" << "\n";
        }
        else 
        {
            cout << ans << "\n";
        }
	}   
	return 0;
}