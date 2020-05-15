#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool isPossible(string target, string skill)
{
    int offset = 0;
    for (int i = 0; i < target.length(); ++i)
    {
        size_t idx = skill.find(target[i]);

        if ((idx != string::npos) && offset < (int)idx)
            return false;
        
        if (offset == skill.length()) 
            break;

        if (target[i] == skill[offset])
            offset += 1;
    }

    return true;
}
int solution(string skill, vector<string> skill_trees) {
    int answer = 0;

    for (string target : skill_trees)
    {
        if (isPossible(target, skill)) 
            answer += 1;
    }
    return answer;
}