#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int DIR_SIZE = 9;
const int dy[] = {0,1,1,1,0,0,0,-1,-1,-1};
const int dx[] = {0,-1,0,1,-1,0,1,-1,0,1};
const int LEFT_DOWN = 1;   
const int DOWN = 2;
const int RIGHT_DOWN = 3;
const int LEFT = 4;
const int STOP = 5;
const int RIGHT = 6;
const int LEFT_UP = 7;
const int UP = 8;
const int RIGHT_UP = 9;

int N, M, jy,jx;
vector<string> map;
vector<Pair> madArduinos;
vector<bool> isCrashed;
string cmd;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        string str;
        cin >> str;
        map.push_back(str);
    }

    cin >> cmd;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (map[i][j] == 'I')
            {
                jy = i;
                jx = j;
                map[i][j] = '.';
            }
            else if (map[i][j] == 'R')
            {
                madArduinos.push_back(make_pair(i,j));
            }
        }
    }

    isCrashed.resize(madArduinos.size(), false);
    bool isFinished = false;
    int time = 0;

    for (char command : cmd)
    {
        if (isFinished)
            break;

        time += 1;
        vector<vector<int>> board(N,vector<int>(M,0));

        //1st. Á¾¼ö move
        int _cmd = command - '0';

        int ny = jy + dy[_cmd];
        int nx = jx + dx[_cmd];

        if (map[ny][nx] == 'R')
        {
            break;
        }
        else
        {
            jy = ny;
            jx = nx;
        }

        //2. madArduion move
        for (int i = 0; i < madArduinos.size(); ++i)
        {
            if (isCrashed[i]) continue;
            
            Pair now = madArduinos[i];
            int minv = 987654321,my,mx;

            for (int dir = 1; dir <= DIR_SIZE; ++dir)
            {
                int ny = now.Y + dy[dir];
                int nx = now.X + dx[dir];

                if (!isSafe(ny,nx)) continue;

                int dist = abs(jy-ny) + abs(jx-nx);
                if (dist < minv)
                {
                    minv = dist;
                    my = ny;
                    mx = nx;
                }
            }

            if (my == jy && mx == jx)
            {
                isFinished = true;
                break;
            }

            board[my][mx]++;
            madArduinos[i].Y = my;
            madArduinos[i].X = mx;
        }
        
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        {
            if (board[i][j] >= 2)
            {
                for (int k = 0; k < madArduinos.size(); ++k)
                {
                    Pair now = madArduinos[k];
                    if (now.Y == i && now.X == j)
                    {
                        isCrashed[k] = true;
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            map[i][j] = '.';

        for (int i = 0; i < madArduinos.size(); ++i)
        {
            if (isCrashed[i]) continue;

            Pair now = madArduinos[i];
            map[now.Y][now.X] = 'R';
        }
    }

    if (time != cmd.size())
    {
        cout << "kraj " << time << "\n"; 
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (i == jy && j == jx)
                    cout << 'I';
                else
                    cout << map[i][j];
            }
            cout << "\n";
        }
    }
    
    return 0;
}