#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

set<string> word_info;
vector<int> solution(int n, vector<string> words) {
    vector<int> answer;

    int idx;
    char nxt = words[0][0];
    for (idx = 0; idx < words.size(); ++idx) {

        if (nxt != words[idx][0] || words[idx].size() == 1 || word_info.count(words[idx]))
            break;
        
        int len = words[idx].length();
        word_info.insert(words[idx]);
        nxt = words[idx][len-1];        
    }

    if (idx == words.size()) {
        answer.push_back(0);
        answer.push_back(0);
    }
    else {
        answer.push_back((idx % n) + 1);
        answer.push_back((idx / n) + 1);
    }

    return answer;
}