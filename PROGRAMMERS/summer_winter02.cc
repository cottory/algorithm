#define U 0
#define D 1
#define R 2
#define L 3
#define Y first
#define X second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,1,-1};

int N;
set<pii> trip;
bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

pii get_next_Pos(pii now, char cmd)
{
    pii nxt = now;
    if (cmd == 'U') {
        nxt.Y += dy[U];
        nxt.X += dx[U];
    }
    else if (cmd == 'D') {
        nxt.Y += dy[D];
        nxt.X += dx[D];
    }
    else if (cmd == 'R') {
        nxt.Y += dy[R];
        nxt.X += dx[R];
    }
    else if (cmd == 'L') {
        nxt.Y += dy[L];
        nxt.X += dx[L];
    }

    return nxt;
}

pii make_statement(pii head, pii tail)
{
    pii state = {0,0};

    state.first = head.Y * 1000000 + head.X;
    state.second = tail.Y * 1000000 + tail.X;

    return state;
}
bool isVisit(pii head, pii tail)
{
    pii now = make_statement(head,tail);

    if (!trip.count({now.Y,now.X}) && !trip.count({now.X, now.Y}))
        return false;
    else 
        return true;
}
int solution(string dirs) {
    int answer = 0;

    N = 11;

    pii now = {5,5};

    for (char cmd : dirs)
    {
        pii nxt = get_next_Pos(now, cmd);
        //service
        if (!isSafe(nxt.Y, nxt.X)) continue;
        
        if (!isVisit(now, nxt))
        {
            pii new_edge = make_statement(now,nxt);
            trip.insert(new_edge);
        }

        now = nxt;
    }

    answer = trip.size();
    return answer;
}