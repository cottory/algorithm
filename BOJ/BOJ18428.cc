#define EMPTY 0 
#define STUDENT 1
#define TEACHER 2
#define WALL 3
#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int N, emptyCnt;
vector<Pair> teachers, emptyBlocks;
vector<vector<int>> map;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

//학생 찾으면 true
//학생 못 찾으면 false
bool teacherBeam(vector<vector<int>>& nowMap)
{
    for (Pair t : teachers)
    {
        int y = t.Y;
        int x = t.X;

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            
            while (isSafe(ny,nx) && nowMap[ny][nx] != WALL)
            {
                if (nowMap[ny][nx] == STUDENT)
                    return true;
                else if (nowMap[ny][nx] == TEACHER)
                    break;

                ny += dy[dir];
                nx += dx[dir];
            }
        }
    }

    return false;
}

bool isFindStudent(vector<int>& pickState)
{
    vector<vector<int>> newMap = map;
    
    //set the newMap
    for (int idx = 0; idx < pickState.size(); ++idx)
    {
        if (pickState[idx])
        {
            int y = emptyBlocks[idx].Y;
            int x = emptyBlocks[idx].X;
            newMap[y][x] = WALL;
        }
    }

    if (teacherBeam(newMap))
        return true;
    else
        return false;
}

int main(void) 
{
    ios::sync_with_stdio(0);

    cin >> N;
    map.resize(N, vector<int>(N, EMPTY));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            char c;
            cin >> c;

            if (c == 'X')
            {
                map[i][j] = EMPTY;
                emptyBlocks.push_back({i,j});
                emptyCnt += 1;

            }
            else if (c == 'S')
            {
                map[i][j] = STUDENT;
            }
            else
            {
                map[i][j] = TEACHER;
                teachers.push_back({i,j});
            }
        }
    }

    vector<int> pick(emptyCnt-3,0);
    for (int i = 0; i < 3; ++i)
        pick.push_back(1);
    
    bool ans = false;

    do {

        if (!isFindStudent(pick))
        {
            ans = true;
            break;
        }

    } while (next_permutation(pick.begin(), pick.end()));

    if (ans) 
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}