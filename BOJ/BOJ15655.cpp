#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N, M;
vector<bool> used;
vector<int> pick, numbers;

void combination(int idx, int cnt)
{
    if (idx == N && cnt != M) return;

    if (cnt == M)
    {
        for (int num : pick)
        {
            cout << num << " ";
        }
        cout << "\n";
    }
    else
    {
        int now = numbers[idx];
        if (!used[now]) 
        {
            used[now] = true;
            pick.push_back(now);
            combination(idx + 1, cnt + 1);
            pick.pop_back();   
            used[now] = false;
        }
        combination(idx + 1, cnt);
    }
    
}
int main(void)
{
    cin >> N >> M;
    used.resize(10001,false);
    for (int x,loop = 0; loop < N; ++loop)
    {
        cin >> x;
        numbers.push_back(x);
    }

    sort(numbers.begin(), numbers.end());
    combination(0,0);
    return 0;
}