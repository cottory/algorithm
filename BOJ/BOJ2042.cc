#define ll long long
#include <iostream>
#include <vector>
using namespace std;

int ARR_SIZE = (1<<20);

int N, M, K;
vector<ll> tree;

void update(int n, ll val, int bit = 1, int st = 0, int en = ARR_SIZE-1)
{
    int m = (st + en) >> 1 ;
    
    if (st == en) {
        tree[bit] = val;
        return;
    }

    if (n <= m) 
        update(n,val, 2*bit, st, m);
    else
        update(n,val,2*bit+1,m+1,en);

    tree[bit] = tree[2*bit] + tree[2*bit+1];
}

ll query(int n1, int n2, int bit = 1, int st = 0, int en = ARR_SIZE-1)
{
    int m = (st + en) >> 1;

    //하나도 안 겹치는 경우 => 항등원 리턴
    if (n1 > n2 || n2 < st || en < n1)
        return 0;

    //구간이 포함되는 경우
    if (n1 <= st && en <= n2)
        return tree[bit];

    //일부만 겹치는 경우
    return query(n1,n2,2*bit,st,m) + query(n1,n2,2*bit+1,m+1,en);
}
int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;

    tree.resize(2*ARR_SIZE, 0);
    
    for (int i = 0; i < N; ++i) {
        ll v;
        cin >> v;
        update(i,v);
    }

    for (int i = 0; i < (M+K); ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        if (a == 1) {
            update(--b, c);
        }
        else {
            cout << query(--b,--c) << "\n";
        }

    }

    return 0;

}