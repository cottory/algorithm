#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N,T;
vector<int> student;
vector<int> finished;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> N;
        student.clear();
        finished.clear();
        student.resize(N);
        finished.resize(N,0);

        for (int x,i = 0; i < N; ++i) {
            cin >> x;
            x--;
            student[i] = x;
            finished[x]++;
        }

        int cnt = 0;
        queue<int> q;

        for (int i = 0; i < N; ++i) {
            if (finished[i] == 0) 
                q.push(i);
        }

        cnt = q.size();
        while (!q.empty()) {
            int solo = q.front(); q.pop();
            int nxt = student[solo];
            finished[nxt]--;

            if (finished[nxt] == 0) {
                cnt += 1;
                q.push(nxt);
            }
        }

        cout << cnt << "\n";
    }
    return 0;
}