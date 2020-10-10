#define NUMBER first
#define DIR second
#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int EMPTY = 0;
const int SHARK = 987654321; 
const int dy[] = {-1,-1,0,1,1,1,0,-1};
const int dx[] = {0,-1,-1,-1,0,1,1,1};
const int DIR_SIZE = 8;
const int N = 4;

int ans;
vector<vector<Pair>> board;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

void fishMove(vector<vector<Pair>>& board)
{
    vector<bool> isMoved(N*N + 1,false);
    
    for (int number = 1; number <= N*N; ++number)
    {
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j].NUMBER == number && !isMoved[number])
            {
                isMoved[number] = true;
                int startDir = board[i][j].DIR;
                
                for (int dir = startDir; dir < startDir + DIR_SIZE; ++dir)
                {
                    int ny =  i + dy[dir % DIR_SIZE];
                    int nx =  j + dx[dir % DIR_SIZE];

                    if (!isSafe(ny,nx))
                        continue;
                    else if (board[ny][nx].NUMBER == SHARK)
                        continue;

                    //ºó Ä­ÀÌ°Å³ª ´Ù¸¥ °í±âÄ­ÀÌ°Å³ª
                    if (board[ny][nx].NUMBER == EMPTY)
                    {
                        board[ny][nx] = make_pair(number,dir % DIR_SIZE);
                        board[i][j] = make_pair(EMPTY,EMPTY);
                        break;
                    }
                    else
                    {
                        //swap
                        board[i][j] = board[ny][nx];
                        board[ny][nx] = make_pair(number,dir % DIR_SIZE);
                        break;
                    }
                }
            }
        }
    }
}

//sy: sharkÀÇ YÁÂÇ¥
//sx: sharkÀÇ XÁÂÇ¥
//sDir: sharkÀÇ ¹æÇâ
void backtrack(vector<vector<Pair>> board, int sy ,int sx, int sDir, int score)
{
    //fishMove
    fishMove(board);

    //backtracking
    int nsy = sy;
    int nsx = sx;
    
    for (int loop = 0; loop < N; ++loop)
    {
        nsy += dy[sDir];
        nsx += dx[sDir];

        if (isSafe(nsy,nsx) && board[nsy][nsx].NUMBER != EMPTY)
        {
            int newScore = board[nsy][nsx].NUMBER;
            int nsDir = board[nsy][nsx].DIR;

            vector<vector<Pair>> nxtBoard = board;

            nxtBoard[sy][sx] = make_pair(EMPTY,EMPTY);
            nxtBoard[nsy][nsx] = make_pair(SHARK, nsDir);
            
            backtrack(nxtBoard,nsy,nsx,nsDir,score + newScore);
        }
    }

    ans = max(ans,score);
    return;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    board.resize(N,vector<Pair>(N));

    for (int i = 0; i < N*N; ++i)
    {
        int num,dir;
        cin >> num >> dir;
        dir--;
        
        int y = i / N;
        int x = i % N;
        
        board[y][x] = make_pair(num,dir);
    }

    //0,0 ¸Ô´Â°É·Î ½ÃÀÛ
    int sy = 0;
    int sx = 0;
    int initScore = board[sy][sx].NUMBER;
    int sDir = board[sy][sx].DIR;

    board[0][0] = make_pair(SHARK,sDir);
    backtrack(board, sy,sx,sDir,initScore);
    cout << ans;

    return 0;
}