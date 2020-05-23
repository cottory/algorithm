#include <iostream>
#include <string>
#include <vector>
using namespace std;

int tSize, pSize;
string T, P;
vector<int> pi;

void getPI() {
    int j = 0;
    for (int idx = 1; idx < P.length(); ++idx) {
        while (j > 0 && P[j] != P[idx]) {
            j = pi[j-1];
        }
        
        if (P[j] == P[idx]) {
            pi[idx] = ++j;
        }
    }
    return;
}
vector<int> KMP() {

    vector<int> ret;

    int j = 0;
    for (int idx = 0; idx < T.size(); ++idx) {
        while (j > 0 && P[j] != T[idx]) {
            j = pi[j-1];
        }
        
        if (P[j] == T[idx]) {
            if (j == pSize - 1) {
                ret.push_back(idx - (pSize-1) + 1);
                j = pi[j];
            }
            else
                j++;
        }
    }

    return ret;
}
int main(void) {

    getline(cin, T);
    getline(cin, P);

    tSize = T.length();
    pSize = P.length();
    pi.resize(pSize, 0);
    getPI();
    vector<int> ret = KMP();

    cout << ret.size() << "\n";
    for (int num : ret) {
        cout << num << "\n";
    }
    return 0;
}