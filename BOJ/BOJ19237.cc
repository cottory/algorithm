#define Y first
#define X second
#define NUMBER first    //0번이면 block, 양수는 sharkNumber
#define REST_TIME second    //뿌린 냄새 남은 시간
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

typedef struct Shark {
    int y,x,dir;
    Shark() : y(0), x(0), dir(0) {}
    Shark(int yy, int xx, int ddir) : y(yy), x(xx), dir(ddir) {}
}Shark;

//1, 2, 3, 4는 각각 위, 아래, 왼쪽, 오른쪽을 의미한다.
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
const int BLOCK = 0;
const int DIR_SIZE = 4;
const int NMAX = 20;
const int MMAX = 401;

int N,M,K,deadCount;
vector<vector<Pair>> board;
vector<bool> isDead;
vector<Shark> sharks;
int dirInfo[MMAX][DIR_SIZE][DIR_SIZE];
int visited[NMAX][NMAX];

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}
void sharkMove()
{
    for (int idx = 1; idx <= M; ++idx)
    {
        if (isDead[idx]) 
            continue;

        Shark now = sharks[idx];
        bool isFindBlock = false;

        //첫 번째 루프. 빈칸 찾기
        for (int loop = 0; loop < DIR_SIZE; ++loop)
        {
            int nowDir = dirInfo[idx][now.dir][loop];
            int ny = now.y + dy[nowDir];
            int nx = now.x + dx[nowDir];

            if (!isSafe(ny,nx)) 
                continue;

            if (board[ny][nx].NUMBER == BLOCK) 
            {
                isFindBlock = true;
                sharks[idx].y = ny;
                sharks[idx].x = nx;
                sharks[idx].dir = nowDir;
                break;
            }
        }

        if (!isFindBlock)
        {
            //두 번째 루프. 내 칸 찾기
            for (int loop = 0; loop < DIR_SIZE; ++loop)
            {
                int nowDir = dirInfo[idx][now.dir][loop];
                int ny = now.y + dy[nowDir];
                int nx = now.x + dx[nowDir];

                if (!isSafe(ny,nx)) 
                    continue;

                if (board[ny][nx].NUMBER == idx) 
                {
                    isFindBlock = true;
                    sharks[idx].y = ny;
                    sharks[idx].x = nx;
                    sharks[idx].dir = nowDir;
                    break;
                }
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    board.resize(N,vector<Pair>(N,make_pair(BLOCK,0)));
    isDead.resize(M+1,false);
    sharks.resize(M+1);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int number;
            cin >> number;
            
            if (number != 0)
            {
                board[i][j] = make_pair(number,K);
                sharks[number].y = i;
                sharks[number].x = j;
            }
            else
            {
                board[i][j] = make_pair(number,0);
            }
        }
    }

    for (int number = 1; number <= M; ++number)
    {
        int dir;
        cin >> dir;
        dir--;
        sharks[number].dir = dir;
    }
    
    //4*4*M LOOP
    for (int number = 1; number <= M; ++number)
    {
        for (int loop = 0; loop < 4; ++loop)
        {
            for (int i = 0; i < DIR_SIZE; ++i)
            {
                int dir;
                cin >> dir;
                dir--;
                dirInfo[number][loop][i] = dir;
            }
        }
    }

    int time = 0;
    
    while (deadCount != M-1)
    {
        if (time > 1000)
            break;

        time += 1;

        //1.sharkmove
        sharkMove();

        //2.blockCount--;
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j].NUMBER != BLOCK)
            {
                board[i][j].REST_TIME = max(0, board[i][j].REST_TIME - 1);

                //K만큼 시간 지났으면 BLOCK으로 만들기
                if (board[i][j].REST_TIME == 0)
                {
                    board[i][j] = make_pair(BLOCK,0);
                }
            }
        }

        //3.상어가 겹치는 check
        memset(visited, 0, sizeof(visited));
        for (int number = 1; number <= M; ++number)
        {
            if (isDead[number]) 
                continue;

            Shark now = sharks[number];
            
            if (visited[now.y][now.x] == 0)
            {
                //빈 칸이면
                visited[now.y][now.x] = 1;
            }
            else
            {
                //다른 상어가 이미 방문한 칸이면
                isDead[number] = true;
                deadCount += 1;
            }
        }    

        //4.영역표시(방귀 뀌기)
        for (int number = 1; number <= M; ++number)
        {
            if (isDead[number]) 
                continue;

            Shark now = sharks[number];
            board[now.y][now.x] = make_pair(number, K);
        }
    }

    if (time > 1000) cout << -1 << "\n";
    else cout << time << "\n";

    return 0;
}