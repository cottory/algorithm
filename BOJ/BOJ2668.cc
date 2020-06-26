#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int N;
queue<int> q;
vector<int> finished, child, ans;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    finished.resize(N,0);
    child.resize(N);

    for (int x,i = 0; i < N; ++i) {
        cin >> x;
        child[i] = --x;
        finished[x] += 1;
    }   

    for (int i = 0; i < N; ++i) 
        if (finished[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int now = q.front(); q.pop();
        finished[child[now]]--;
        if (finished[child[now]] == 0)
            q.push(child[now]);
    }
    
    for (int i = 0; i < N; ++i)
        if (finished[i]) 
            ans.push_back(i+1);
        
    
    cout << ans.size() << "\n";
    for (int num : ans) 
        cout << num << "\n";
    return 0;
}