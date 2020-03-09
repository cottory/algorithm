#define BOARD_SIZE 4
#include<iostream>
#include<string>
#include<set>
using namespace std;

typedef struct Token
{
    int y, x;
    string number;
    Token(int yy, int xx, string nnumber) : y(yy), x(xx), number(nnumber) {}
}Token;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

bool safe(int y, int x)
{
    return (0 <= y && y < BOARD_SIZE && 0 <= x && x < BOARD_SIZE);
}

void dfs(int board[BOARD_SIZE][BOARD_SIZE], set<string> &used, string ret, int y, int x, int cnt)
{
    if (cnt == 6 && ret.length() == 7)
    {
        if (!used.count(ret)) 
        {
            used.insert(ret);
        }

        return;
    }
    else if (cnt == 6) 
        return;
    
    for (int dir = 0; dir < 4; ++dir)
    {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if (safe(ny,nx))
        {
            string nxt = ret;
            char c = board[ny][nx] + '0';
            nxt += c;
            dfs(board, used, nxt, ny, nx, cnt+1);
        }
    }
    
    return;
}
int solve(int board[BOARD_SIZE][BOARD_SIZE])
{
    set<string> used;

    for (int row = 0; row < BOARD_SIZE; ++row)
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        int y = row;
        int x = col;
        char c = board[y][x] + '0';
        string candidate = "";
        candidate += c;
        dfs(board,used,candidate, y, x, 0);
    }

    return (int)used.size();
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int board[BOARD_SIZE][BOARD_SIZE];

        for (int row = 0; row < BOARD_SIZE; ++row)
        for (int col = 0; col < BOARD_SIZE; ++col)
            cin >> board[row][col];

        cout << "#" << test_case << " " << solve(board) << "\n";
	}   
	return 0;
}