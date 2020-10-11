#include <iostream>
#include <queue>
using namespace std;

int N;
queue<int> q;

int main(void) 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N;

    if (N == 1)
    {
        cout << 1;
        return 0;
    }

    for (int number = 1; number <= N; ++number)
    {
        q.push(number);
    }

    while (!q.empty())
    {
        q.pop();
        int num = q.front(); q.pop();

        if (q.empty())
        {
            cout << num << "\n"; 
            break;
        }
        else 
        {
            q.push(num);
        }
    }

    return 0;
}