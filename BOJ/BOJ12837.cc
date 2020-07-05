#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int N,Q;
const int treeSize = 1 << 20;
ll tree[2*treeSize];

void update(int n, ll v, int bit = 1, int st = 0, int en = treeSize-1) {

    int mid = (st + en) / 2;

    if (st == en) {
        tree[bit] += v;
        return;
    }

    if (n <= mid) {
        update(n, v, 2*bit, st, mid);
    }
    else {
        update(n, v, 2*bit + 1, mid+1, en);
    }
    
    tree[bit] = (tree[2*bit] + tree[2*bit+1]);
}
ll query(int n1, int n2, int bit = 1, int st = 0, int en = treeSize-1) {

    int mid = (st + en) / 2;

    if (n1 > n2 || en < n1 || n2 < st) {
        return 0;
    }
    else if (n1 <= st && en <= n2) {
        return tree[bit];
    }

    return query(n1,n2,2*bit,st,mid) + query(n1,n2,2*bit+1,mid+1,en);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> Q;
    memset(tree, 0, sizeof(tree));

    while (Q--) {
        ll cmd, a, b;
        cin >> cmd >> a >> b;

        if (cmd == 1) {
            update(--a,b);
        } 
        else {
            cout << query(--a,--b) << "\n";
        } 

    }
    
    return 0;
}