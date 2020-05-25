#define PLUS 0
#define MINUS 1
#define MULTI 2
#define DIV 3
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, minv, maxv;
vector<int> numbers,oper_list,order;

int solve(vector<int>& numbers, vector<int>& order) {
    int ret = numbers[0];

    for (int i = 0; i < order.size(); ++i) {
        if (order[i] == PLUS) 
            ret += numbers[i+1];
        else if (order[i] == MINUS) 
            ret -= numbers[i+1];
        else if (order[i] == MULTI) 
            ret *= numbers[i+1];
        else if (order[i] == DIV) 
            ret /= numbers[i+1];
    }

    return ret;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    numbers.resize(N);
    oper_list.resize(4,0);

    for (int i = 0; i < N; ++i) 
        cin >> numbers[i];

    for (int loop = 0; loop < 4; ++loop) 
        cin >> oper_list[loop];

    for (int loop = 0; loop < 4; ++loop) 
    for (int i = 0; i < oper_list[loop]; ++i) 
        order.push_back(loop);

    minv = 1111111111;
    maxv = -1111111111;
    
    do {
        int result = solve(numbers, order);
        minv = min(minv, result);
        maxv = max(maxv, result);
    } while (next_permutation(order.begin(), order.end()));
    
    cout << maxv << "\n" << minv << "\n";
    return 0;
}