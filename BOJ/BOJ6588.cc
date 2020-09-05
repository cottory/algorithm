#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int NMAX = 1000005;
bool isPrime[NMAX];
vector<int> candidate;
int main(void) {

    ios::sync_with_stdio(0);

    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(isPrime, isPrime + NMAX, true);

    for (int i = 2; i <= sqrt(NMAX); ++i)
    {
        if (isPrime[i] == false) continue;

        for (int j = i + i; j < NMAX; j += i)
        {
            isPrime[j] = false;
        }
    }
    
    for (int i = 3; i <= NMAX; ++i)
    {
        if (i % 2 && isPrime[i])
            candidate.push_back(i);
    }

    int n;
    while (true)
    {
        cin >> n;

        if (n == 0)
            break;

        for (int primeOddNumber : candidate)
        {
            int coupleNumber = n - primeOddNumber;
            if (coupleNumber < 0) continue;
            
            if (isPrime[coupleNumber])
            {
                cout << n << " = " << primeOddNumber << " + " << coupleNumber << "\n";
                break;
            }
        }   
    }

    return 0;
}