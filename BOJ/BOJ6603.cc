#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> pick,candidate;
vector<bool> used;

void print()
{
    for (int i = 0; i < pick.size(); ++i)
        cout << pick[i] << " ";
    cout << "\n";
}
void combination(int idx, int r)
{
    if (r == 6)
    {
        print();
        return;
    }

    if (idx == N)
        return;
    
    if (!used[idx])
    {
        used[idx] = true;
        pick.push_back(candidate[idx]);
        combination(idx + 1, r + 1);
        pick.pop_back();
        used[idx] = false;
    }

    combination(idx + 1, r);
}
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true)
    {
        cin >> N;
        if (N == 0)
            break;

        used.resize(N,false);

        for (int x,i = 0; i < N; ++i)
        {
            cin >> x;
            candidate.push_back(x);
        }

        combination(0,0);
        cout << "\n";

        pick.clear();
        candidate.clear();
        used.clear();
    }
    return 0;
}