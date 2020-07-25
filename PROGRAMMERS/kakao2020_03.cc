#define tiii tuple<int,int,int>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

set<string> myGem,globalGem;
vector<tiii> answerCandidate;

map<string,int> state;

vector<int> solution(vector<string> gems) {
    vector<int> answer;

    for (string gem : gems) 
        globalGem.insert(gem);

    int gSize = gems.size();
    int left = 0, right = 0;

    while (left <= right) {

        if (myGem.size() == globalGem.size()) {
            answerCandidate.push_back(make_tuple((right - left), left, right));
        }

        if (right == gSize)
            break;

        string nowGem = gems[right];

        if (myGem.find(nowGem) == myGem.end()) 
        {
            myGem.insert(nowGem);
            state[nowGem] = 1;
        }
        else
        {
            //현재, 보석을 가지고 있는 상태인데 만남
            state[nowGem] += 1;

            while (left <= right)
            {
                string targetGem = gems[left];
                if (state[targetGem] > 1) {
                    left++;
                    state[targetGem] -= 1;
                }
                else {
                    break;
                }
            }
        }

        right++;
    }

    sort(answerCandidate.begin(), answerCandidate.end());

    left = get<1>(answerCandidate[0]);
    right = get<2>(answerCandidate[0]);

    answer.push_back(left + 1);
    answer.push_back(right);
    return answer;
}