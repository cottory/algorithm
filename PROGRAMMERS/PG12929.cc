#include <string>
#include <vector>

using namespace std;

int solve(int openCnt, int idx, int n)
{
    //기저 사례
    if (idx == n) {
        if (openCnt == 0) return 1;
        else return 0;
    }

    if (openCnt > (n / 2)) {
        return 0;
    }

    int ret = 0;
    if (openCnt) {
        //plus Close Garo
        ret += solve(openCnt - 1, idx + 1, n);
    }

    //plus Open Garo
    ret += solve(openCnt + 1, idx + 1, n);
    return ret;
}
int solution(int n) {
    int answer = 0;

    answer = solve(0, 0, 2*n);
    return answer;
}