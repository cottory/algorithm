#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int maxv,B;
string A;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> A >> B;
    int _size = A.length();
    
    vector<int> order(_size,0);
    
    for (int i = 0; i < order.size(); ++i)
        order[i] = i;
    
    maxv = -1;
    do {
        string candidate = "";
        for (int idx : order) 
            candidate += A[idx];

        if (candidate[0] == '0') continue;
        int candidate_int = stoi(candidate);
        if (candidate_int <= B && candidate_int > maxv) {
            maxv = candidate_int;
        }

    } while(next_permutation(order.begin(), order.end()));
    
    cout << maxv << "\n";
    return 0;
}