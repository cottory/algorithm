#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;

    if (n > s) {
        answer.push_back(-1);
    }
    else {
        int val = s / n;
        for (int loop = 0; loop < n; ++loop)
            answer.push_back(val);

        if ((s % n) != 0) {
            int r = s % n;
            int idx = 0;
            while (r--) {
                answer[idx]++;
                idx++;
            }
        }
    }

    sort(answer.begin(), answer.end());
    return answer;
}