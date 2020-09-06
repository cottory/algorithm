#define ll long long
#include <string>
#include <vector>
using namespace std;

ll factorial(ll n) {
    if (n == 1) return  1;
    else return n * factorial(n-1);
}

vector<int> solution(int n, long long k) {
    vector<int> answer, numbers;
    
    for (int num = 1; num <= n; ++num)
        numbers.push_back(num);

    while (true)
    {
        if (n == 0)
            break;
            
        ll componentSize = factorial(n) / (ll)n;
        int targetIdx = (int)((k-1) / componentSize);
        
        answer.push_back(numbers[targetIdx]);
        numbers.erase(numbers.begin() + targetIdx);

        n--;

        k %= componentSize;
        if (k == 0)
            k = componentSize;
    }

    return answer;
}