#include <iostream>
using namespace std;

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    
    while (T--)
    {
        int N, ret = 0;
        cin >> N;

        while (N >= 5)
        {
            int q = N / 5;
            ret += q;
            N /= 5;
        }        

        cout << ret << "\n";
    }
    
    return 0;
}