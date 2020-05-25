#define ll long long
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N, Q;
const int SEG_SIZE = (1 << 17);
ll tree[2*SEG_SIZE];
vector<int> v;

void update(int n, int v, int bit = 1, int st = 0, int en = SEG_SIZE - 1) {

    int m = (st + en) >> 1;

    if (st == en) {
        tree[bit] = v;
        return;
    }

    if (n <= m) {
        update(n,v,2*bit, st, m);
    }
    else {
        update(n,v,2*bit+1,m+1,en);
    }
    
    tree[bit] = tree[2*bit] + tree[2*bit+1];
    return;
}

ll query(int n1 ,int n2, int bit = 1, int st = 0, int en = SEG_SIZE - 1) {

    int m = (st + en) >> 1;

    if (n2 < st || en < n1)
        return 0;

    if (n1 <= st && en <= n2) {
        return tree[bit];
    }

    return query(n1,n2,2*bit,st,m) + query(n1,n2,2*bit+1,m+1,en);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> Q;

    v.resize(SEG_SIZE, 0);

    for (int i = 0; i < N; ++i) {
        ll x;
        cin >> x;
        update(i,x);
    }    

    while (Q--) {
        int x,y,a,b;
        cin >> x >> y >> a >> b;
        
        x--; y--; a--;

        if (x > y) swap(x,y);
    
        cout << query(x,y) << "\n";
        update(a,b);
    }

    return 0;
}