#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int aSize, bSize;
vector<bool> used;

bool isWin(vector<int>& A, int idx, int num)
{
    if (!used[idx] && A[idx] < num) return true;
    else return false;
}

int binarySearch(vector<int>& A, int num)
{
    int st, en, mid, before = 0;
    st = 0;
    en = aSize;

    while (st < en)
    {
        mid = (st + en) / 2;

        if (isWin(A, mid, num))
        {
            st = mid + 1;
            before = mid;
        }
        else
        {
            en = mid;
        }
    }

    if (!used[before] && num > A[before]) 
    {
        used[before] = true;
        return 1;
    }
    else
        return 0;
}

int solution(vector<int> A, vector<int> B) {
    int answer = 0;

    aSize = A.size();
    bSize = B.size();
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    used.resize(aSize + 10, false);

    int st = (int)B.size() - 1;
    
    for (int idx = st; idx >= 0; --idx)
    {
        if(binarySearch(A, B[idx]))
            answer += 1;
    }
    return answer;
}