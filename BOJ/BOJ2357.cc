#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SZ = 1<<17;
int min_tree[2*SZ], max_tree[2*SZ];
int N, M;

void update(int cmd, int n, int val, int bit = 1, int st = 0, int en = SZ-1)
{
    int m = (st+en) >> 1;

    if (st == en) {
        if (cmd == 0) min_tree[bit] = val;
        else max_tree[bit] = val;
        return;
    }
    
    if (n <= m) {
        update(cmd,n,val,2*bit,st,m);
    }
    else {
        update(cmd,n,val,2*bit+1,m+1,en);
    }

    if (cmd == 0) min_tree[bit] = min(min_tree[2*bit],min_tree[2*bit+1]);
    else max_tree[bit] = max(max_tree[2*bit],max_tree[2*bit+1]);
}

int query(int cmd, int n1 , int n2, int bit = 1, int st = 0, int en = SZ- 1)
{
    int m = (st+en) >> 1;

    if (n1 > n2 || en < n1 || n2 < st) {
        if (cmd == 0) return INT32_MAX;
        else return INT32_MIN;
    }

    if (n1 <= st && en <= n2) {
        if (cmd == 0) return min_tree[bit];
        else return max_tree[bit];
    }

    if (cmd == 0) return min(query(cmd, n1, n2, 2*bit,st,m), query(cmd,n1,n2,2*bit+1,m+1,en));
    return max(query(cmd, n1, n2, 2*bit,st,m), query(cmd,n1,n2,2*bit+1,m+1,en));
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        update(0,i,v);
        update(1,i,v);
    }

    for (int i = 0; i < M; ++i) {
        int n1, n2;
        cin >> n1 >> n2;
        n1--; n2--;
        cout << query(0,n1,n2) << " " << query(1,n1,n2) << "\n";
    }

    return 0;
}