#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T,N;
const int INF = 987654321;

int main(void) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    while (T--)
    {
        cin >> N;
        vector<int> grade(N+10,0);

        int result = 0;
        for (int paper_rank,interview_rank,i =  0; i < N; ++i)
        {
            cin >> paper_rank >> interview_rank;
            grade[paper_rank] = interview_rank;
        }

        int minInterviewRank = INF;
        for (int i = 1; i <= N; ++i)
        {
            if (grade[i] < minInterviewRank)
            {
                minInterviewRank = grade[i];
                result += 1;
            }
        }
   
        cout << result << "\n";
    }

    return 0;
}