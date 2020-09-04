#include <iostream>
using namespace std;

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N,answer,cnt,targetNumber;
    const int MOD = 1000;
    cin >> N;

    cnt = 0;
    targetNumber = 1;

    while (true)
    {
        int now = targetNumber;

        while (now)
        {
            int r = now % MOD;
            if (r == 666) 
            {
                cnt += 1;
                break;
            }
            else 
            {
                now /= 10;
            }
        }

        if (cnt == N)
        {
            answer = targetNumber;
            break;
        }

        targetNumber++;
    }

    cout << answer << endl;

    return 0;
}