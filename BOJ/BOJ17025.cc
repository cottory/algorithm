#define AREA first
#define PERIMETER second
#define Pair pair<int,int>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int DIR_SIZE = 4;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
int N;
vector<string> map;
vector<Pair> components;
vector<vector<bool>> visited;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

Pair bfs(int y, int x)
{
    queue<Pair> q;
    q.push(make_pair(y,x));
    int perimeter = 0;
    int area = 1;

    while (!q.empty())
    {
        Pair now = q.front(); q.pop();

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = now.first + dy[dir];
            int nx = now.second + dx[dir];

            if (!isSafe(ny,nx)) 
            {
                perimeter += 1;
                continue;
            }
            else if (visited[ny][nx]) continue;
            else if (map[ny][nx] == '.')
            {
                perimeter += 1;
                continue;
            }

            visited[ny][nx] = true;
            q.push(make_pair(ny,nx));
            area += 1;
        }
    }

    return make_pair(area,perimeter);
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> N;
    visited.resize(N,vector<bool>(N,false));

    for (int i = 0; i < N; ++i)
    {
        string str;
        cin >> str;
        map.push_back(str);
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (!visited[i][j] && (map[i][j] == '#'))
            {
                visited[i][j] = true;
                Pair component = bfs(i,j);
                components.push_back(component);
            }
        }
    }

    sort(components.begin(), components.end(), [](Pair p1, Pair p2) {
        if (p1.AREA == p2.AREA) return p1.PERIMETER < p2.PERIMETER;
        else return p1.AREA > p2.AREA;
    });

    cout << components[0].AREA << " " << components[0].PERIMETER << "\n";

    return 0;
}