#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
    int answer = 0;
    sort(d.begin(), d.end());

    for (int num : d) {
        if (budget >= num) {
            answer += 1;
            budget -= num;
        }
    }
    return answer;
}