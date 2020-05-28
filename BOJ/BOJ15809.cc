#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N,M;
vector<int> soldier,parent, rest;

int find(int nation) {
    if (parent[nation] == nation) return nation;
    else return parent[nation] = find(parent[nation]);
}

//c2의 부모가 c1이 됨.
void _union(int c1, int c2) {
    parent[c2] = c1;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    soldier.resize(N);
    parent.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> soldier[i];
        parent[i] = i;
    }

    while (M--) {
        int O,P,Q;
        cin >> O >> P >> Q;
        P--; Q--;

        if (O == 1) {
            //동맹
            int c1 = find(P);
            int c2 = find(Q);
            _union(c1,c2);
            soldier[c1] += soldier[c2];
        }
        else {
            //전쟁
            int c1 = find(P);    
            int c2 = find(Q);
            if (soldier[c1] == soldier[c2]) {
                soldier[c1] = 0;
                soldier[c2] = 0;
            }
            else if (soldier[c1] > soldier[c2]) {
                soldier[c1] -= soldier[c2];
                soldier[c2] = 0;
                _union(c1, c2);
            }
            else {
                soldier[c2] -= soldier[c1];
                soldier[c1] = 0;
                _union(c2, c1);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (parent[i] == i && (soldier[i] != 0))
            rest.push_back(soldier[i]);
    }

    sort(rest.begin(), rest.end());
    
    cout << rest.size() << "\n";
    for (int num : rest) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}