#define psi pair<string,int>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

int wSize;
set<string> visited;

bool isCandidate(string begin, string target) {
    int ret = 0;
    for (int i = 0; i < begin.length(); ++i) {
        if (begin[i] == target[i]) 
            ret += 1;
    }
    return ret == (wSize - 1) ? true : false;
}

int bfs(string begin, string target, vector<string> words) {

    int ret = 0;
    queue<psi> q;
    q.push(make_pair(begin,0));

    while (!q.empty()) {
        psi now = q.front(); q.pop();

        if (now.first.compare(target) == 0) {
            return now.second;
        }

        for (int i = 0; i < words.size(); ++i) {
            if (isCandidate(now.first,words[i]) && !visited.count(words[i])) {
                visited.insert(words[i]);
                q.push(make_pair(words[i], now.second + 1));
            }
        }
    }

    return ret;
}
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    wSize = begin.length();
    answer =  bfs(begin, target, words);
    return answer;
}