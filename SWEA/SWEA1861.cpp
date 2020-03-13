#define MINV first
#define LENGTH second
#define pii pair<int,int>
#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;

typedef struct Token
{
    int y, x, num;
    Token(int yy, int xx, int nnum) : y(yy), x(xx), num(nnum) {}
}Token;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};
int N;
vector<int> used;

bool isSafe(int y, int x)
{
    return (0<=y && y<N && 0<=x && x<N);
}
pii bfs(vector<vector<int> > &board, int y, int x)
{
    pii ret;
    int minv = board[y][x];
    int length = 1;
    queue<Token> q;
    
    q.push(Token(y,x,board[y][x]));

    while (!q.empty())
    {
        Token now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = now.y + dy[dir];
            int nx = now.x + dx[dir];

            if (isSafe(ny,nx) && !used[board[ny][nx]] && ((board[ny][nx] == board[now.y][now.x] + 1) || (board[ny][nx] == board[now.y][now.x] - 1)))
            {
                used[board[ny][nx]] = 1;
                q.push(Token(ny,nx,board[ny][nx]));
                length++;
                minv = min(minv, board[ny][nx]);
            }
        }
    }

    ret.first = minv;
    ret.second = length;
    return ret;
}

pii solve(vector<vector<int> > &board)
{
    pii ret = {0,0};
    
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if (!used[board[row][col]])
            {
                used[board[row][col]] = 1;
                pii now = bfs(board,row,col);

                //bfs
                //candidate 갱신
                if (now.LENGTH > ret.LENGTH)
                {
                     ret = now;
                }
                else if (now.LENGTH == ret.LENGTH)
                {
                    if (now.MINV < ret.MINV) 
                    {
                        ret = now;
                    }
                }
            }
        }
    }
    
    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        vector<vector<int> > board;
        pii ans;
        
        scanf("%d",&N);

        used.clear();
        used.resize(N*N + 1,0);
        board.resize(N,vector<int>(N,0));
        
        for (int i = 0; i < N; ++i)
        for (int x,j = 0; j < N; ++j)
        {
            scanf("%d",&x);
            board[i][j] = x;
        }

        ans = solve(board);

        printf("#%d %d %d\n",test_case, ans.first, ans.second);
	}
	return 0;
}