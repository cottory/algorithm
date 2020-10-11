#define Tuple tuple<int,int,int>
#define Tuple2 tuple<int,string,int>
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

const int DIR_SIZE = 4;
const int EMPTY = -1;
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};
int A,B,N,M;
vector<vector<int>> map;
vector<Tuple> robots;

bool isSafe(int y, int x)
{
    return (1 <= y && y <= B && 1 <= x && x <= A);
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> A >> B >> N >> M;
    map.resize(B+1,vector<int>(A+1,EMPTY));

    for (int i = 0; i < N; ++i)
    {
        int y,x,_dir;
        string dir;
        cin >> x >> y >> dir;

        if (dir.compare("N") == 0)
        {
            _dir = UP;
        }
        else if (dir.compare("W") == 0)
        {
             _dir = LEFT;
        }
        else if (dir.compare("E") == 0)
        {   
             _dir = RIGHT;
        }
        //S
        else
        {
             _dir = DOWN;
        }
        
        y = (B+1-y);
        
        map[y][x] = i;
        robots.push_back(make_tuple(y,x,_dir));
    }

    vector<Tuple2> querys;

    for (int i = 0; i < M; ++i)
    {
        int robo_id, loopCount;
        string cmd;

        cin >> robo_id >> cmd >> loopCount;
        robo_id--;

        querys.push_back(make_tuple(robo_id,cmd,loopCount));
    }

    bool isError = false;

    for (Tuple2 query : querys)
    {
        int robo_id,loopCount;
        string cmd;

        tie(robo_id,cmd,loopCount) = query;

        int crashedRoboid = -1;
        bool isCrashedIntoWall = false;
        bool isCrashedIntoRobo = false;

        for (int loop = 0; loop < loopCount; ++loop)
        {
            Tuple robot = robots[robo_id];
            int y,x,dir;
            tie(y,x,dir) = robot;
            
            if (cmd.compare("L") == 0)
            {
                dir = (dir - 1 + DIR_SIZE) % DIR_SIZE;
            }
            else if (cmd.compare("R") == 0)
            {
                dir = (dir + 1) % DIR_SIZE;
            }
            //F
            else 
            {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if (!isSafe(ny,nx))
                {
                    isCrashedIntoWall = true;
                    break;
                }
                else
                {
                    if (map[ny][nx] == EMPTY)
                    {
                        map[y][x] = EMPTY;
                        map[ny][nx] = robo_id;
                        y = ny;
                        x = nx;
                    }
                    else
                    {
                        crashedRoboid = map[ny][nx];
                        isCrashedIntoRobo = true;
                        break;
                    }
                }
            }

            robots[robo_id] = make_tuple(y,x,dir);
        }

        if (isCrashedIntoWall || isCrashedIntoRobo)
        {
            isError = true;

            if (isCrashedIntoWall) 
            {
                cout << "Robot " << robo_id + 1 << " crashes into the wall";
            }
            else 
            {
                cout << "Robot " << robo_id + 1 << " crashes into robot " << crashedRoboid + 1;
            }

            break;
        }
    }

    if (!isError)
    {
        cout << "OK";
    }

    return 0;
}