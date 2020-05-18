#define WHITE 0
#define RED 1
#define BLUE 2
#define si stack<int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

typedef struct Tok {
    int num,y,x,dir;
    Tok(int nnum, int yy, int xx, int ddir) : num(nnum), y(yy), x(xx), dir(ddir) {}
}Tok;

int dy[] = {0,-1,0,1};
int dx[] = {1,0,-1,0};
int N, K;

vector<vector<int>> map;
vector<vector<si>> v;
vector<Tok> tok_list;

bool safe(int y, int x) {
    return (0<=y&&y<N&&0<=x&&x<N);
}

stack<int> _reverse(stack<int> before) {
    stack<int> ret;
    while (!before.empty()) {
        ret.push(before.top());
        before.pop();
    }
    return ret;
}

stack<int> getToken(int y, int x, int num) {
    stack<int> ret;

    while (!v[y][x].empty()) {
        if (v[y][x].top() == num) {
            ret.push(v[y][x].top());
            v[y][x].pop();
            break;
        }
        else {
            ret.push(v[y][x].top());
            v[y][x].pop();
        }
    }
    return ret;
}

void addToken(int y, int x, stack<int> target) {
    while (!target.empty()) {
        v[y][x].push(target.top());
        target.pop();
    }
}
void changePosition(stack<int> target, int ny , int nx) {
    while (!target.empty()) {
        int num = target.top(); target.pop();
        tok_list[num].y = ny;
        tok_list[num].x = nx;
    }
}
void process_to_white(stack<int> target, int y, int x) {
    changePosition(target, y,x);
    addToken(y,x,target);
}
void process_to_red(stack<int> target, int y, int x) {
    changePosition(target,y,x);
    target = _reverse(target);
    addToken(y,x,target); 
}
void process_to_blue(stack<int> target, Tok& t, int ny, int nx) {
    int by, bx;
    by = t.y;
    bx = t.x;

    t.dir = (t.dir + 2) % 4; 
    ny = by + dy[t.dir];
    nx = bx + dx[t.dir];

    if (!safe(ny,nx) || map[ny][nx] == BLUE) {
        addToken(by,bx,target);  
    }
    else {
        if (map[ny][nx] == WHITE) {
            process_to_white(target, ny, nx);
        }
        else if (map[ny][nx] == RED) {
            process_to_red(target,ny,nx); 
        }
    }
    
}
void move(Tok& t) {

    //getToken
    si ret = getToken(t.y, t.x, t.num);

    //find next position
    int ny = t.y + dy[t.dir];
    int nx = t.x + dx[t.dir];

    if (safe(ny,nx)) {
        if (map[ny][nx] == WHITE) {
            process_to_white(ret, ny, nx);
        }
        else if (map[ny][nx] == RED) {
            process_to_red(ret,ny,nx); 
        }
        else if (map[ny][nx] == BLUE) {
            process_to_blue(ret, t, ny ,nx);
        }
    }
    else {
        process_to_blue(ret, t, ny ,nx);
    }

    //
}
bool isFinished() {
    for (Tok t : tok_list) {
        if (v[t.y][t.x].size() >= 4) 
            return true;
    }
    return false;
}
bool solve() {

    for (Tok& t : tok_list) {        
        move(t);
        if (isFinished())
            return true;
    }

    return false;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    map.resize(N,vector<int>(N,0));
    v.resize(N,vector<si>(N));

    for (int i = 0; i < N; ++i)
    for (int x,j = 0; j < N; ++j) 
        cin >> map[i][j];

    for (int y,x,dir,i = 0; i < K; ++i) {
        cin >> y >> x >> dir;
        y--; x--; 
        if (dir == 1) dir = 0;
        else if (dir == 2) dir = 2;
        else if (dir == 3) dir = 1;
        else if (dir == 4) dir = 3;

        tok_list.push_back(Tok(i,y,x,dir));
        v[y][x].push(i);
    }

    int cnt = 1;
    while (cnt <= 1000) {
        if (solve()) break;
        cnt += 1;
    }

    if (cnt > 1000) 
        cout << -1 << "\n";
    else
        cout << cnt << "\n";

    return 0;
}