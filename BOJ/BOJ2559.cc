#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<int> arr;
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    
    for (int x,i = 0; i < N; ++i)
    {
        cin >> x;
        arr.push_back(x);
    }

    int st = 0, en = 0;
    int pick = 0;
    int sum = 0;
    int answer = -987654321;

    while (st < N) {
        if (pick < K && en == N) {
            break;
        }

        if (pick < K) {
            sum += arr[en++];
            pick += 1;
        } else {
            sum -= arr[st++];
            pick -= 1;
        }
        if (pick == K) {
            answer = max(answer, sum);
        }
    }
    cout << answer << "\n";
    return 0;
}