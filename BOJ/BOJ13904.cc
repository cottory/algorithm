#define DAY first
#define SCORE second
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> pq;
vector<Pair> v;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    for (int day,score,i = 0; i < N; ++i)
    {
        cin >> day >> score;
        v.push_back(make_pair(day,score));
    }

    sort(v.begin(), v.end());

    for (auto work : v)
    {
        if (pq.size() < work.DAY)
        {
            pq.push(work.SCORE);
        }
        else
        {
            //pq.size() >= work.DAY
            if (pq.top() < work.SCORE)
            {
                pq.pop();
                pq.push(work.SCORE);
            }
        }
    }

    int answer = 0;

    while (!pq.empty())
    {
        answer += pq.top(); 
        pq.pop();
    }

    cout << answer << endl;
    return 0;
}