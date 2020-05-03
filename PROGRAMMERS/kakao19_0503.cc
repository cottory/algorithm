#include <string>
#include <vector>
using namespace std;

int solution(string dartResult) {
    int answer = 0;
    vector<int> score_vector;

    int score = 0;
    for (int i = 0; i < dartResult.length(); ++i)
    {
        if ('0' <= dartResult[i] && dartResult[i] <= '9')
            score = (score * 10) + (dartResult[i] - '0');
        else if (dartResult[i] == 'S') score_vector.push_back(score), score = 0;
        else if (dartResult[i] == 'D') score_vector.push_back(score*score), score = 0;
        else if (dartResult[i] == 'T') score_vector.push_back(score*score*score), score = 0;
        else if (dartResult[i] == '#') score_vector.back() = -score_vector.back();
        else  {
            score_vector.back() = 2 * score_vector.back();
            if (score_vector.size() > 1) {
                int lastScore = score_vector.back();
                score_vector.pop_back();
                score_vector.back() = 2 * score_vector.back();
                score_vector.push_back(lastScore);
            }
        }
    }

    for (int num : score_vector)
        answer += num;
    return answer;
}