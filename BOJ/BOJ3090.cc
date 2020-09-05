#define ll long long
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N,T;
vector<int> arr, arrCopy, ans;

bool isPossible(ll diff)
{
    ll cnt = 0;
    arrCopy = arr;

    for (int i = 0; i < N-1; ++i)
    {
        if (arrCopy[i+1] - arrCopy[i] > diff)
        {
            cnt += (arrCopy[i+1] - (arrCopy[i] + diff));
            arrCopy[i+1] = (arrCopy[i] + diff);
        }
    }

    for (int i = N-1; i >= 1; --i)
    {
        if (arrCopy[i-1] - arrCopy[i] > diff)
        {
            cnt += (arrCopy[i-1] - (arrCopy[i] + diff));
            arrCopy[i-1] = (arrCopy[i] + diff);
        }
    }
    
    return cnt <= T ? true : false;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> T;

    for (int x,i = 0; i < N; ++i)
    {
        cin >> x;
        arr.push_back(x);
    }

    ll mid,st,en;
    st = 0;
    en = 1e9;
    
    while (st < en)
    {
        mid = (st + en) / 2;

        if (isPossible(mid))
        {
            en = mid;
            ans = arrCopy;
        }
        else
        {
            st = mid + 1;
        }
    }

    for (int i = 0; i < N; ++i)
        cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}