#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N,M;
vector<int> numbers;

bool binarySearch(int st, int en, int num)
{
    int mid;

    while (st < en)
    {
        mid = (st + en) / 2;

        if (M == numbers[mid] + num)
        {
            return true;
        }
        else if (M < numbers[mid] + num)
        {
            en = mid;
        }
        else
        {
            //M > numbers[mid] + num
            st = mid + 1;
        }
    }

    return false;
}
int main(void)
{
    int answer = 0;

    cin >> N >> M;

    for (int x,i = 0; i < N; ++i)
    {
        cin >> x;
        numbers.push_back(x);
    }

    sort(numbers.begin(), numbers.end());

    for (int idx = 0; idx < N-1; ++idx)
    {
        int now = numbers[idx];
        if (now >= M) continue;

        if (binarySearch(idx + 1, N, now))
            answer += 1;

    }

    cout << answer << "\n";
    
    return 0;
}