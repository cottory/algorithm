#define ll long long
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int N, M;
int SEG_SIZE = 1;
// const int SEG_SIZE = 1<<20;
// ll tree[2*SEG_SIZE];
vector<ll> tree;

void update(int n, int v, int bit = 1, int st = 0, int en = SEG_SIZE-1) {

    int m = (st+en) >> 1;

    if (st == en) {
        tree[bit] = v;
        return;
    }

    if (n <= m)
        update(n,v,2*bit,st,m);
    else
        update(n,v,2*bit+1,m+1,en);
    
    tree[bit] = tree[2*bit] + tree[2*bit+1];
}

ll query(int n1, int n2, int bit = 1, int st = 0, int en = SEG_SIZE-1) {

    int m = (st+en) >> 1;

    if (n2 < st || en < n1) 
        return 0;

    if (n1 <= st && en <= n2)
        return tree[bit];

    return query(n1,n2,2*bit,st,m) + query(n1,n2,2*bit+1,m+1,en);
}   

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    while (SEG_SIZE < N) {
        SEG_SIZE *= 2;
    }

    tree.resize(2*SEG_SIZE, 0);
    
    while (M--) {
        int cmd,a,b;
        cin >> cmd >> a >> b;
        if (cmd) {
            a--;
            update(a,b);
        }
        else {
            if (a > b) swap(a,b);
            a--; b--;
            cout << query(a,b) << "\n";
        }
    }
    
    return 0;
}