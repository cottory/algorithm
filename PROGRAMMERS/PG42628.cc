#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

int f,r;
priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

vector<int> solution(vector<string> operations) {
    vector<int> answer;

    for (string operation : operations) {
        vector<string> query;
        
        string token;
        stringstream ss(operation);

        while (getline(ss, token, ' ')) {
            query.push_back(token);
        }

        //Solve
        if (f == r) {
            while(!minHeap.empty()) minHeap.pop();
            while(!maxHeap.empty()) maxHeap.pop();
        }

        if (query[0].compare("I") == 0) {
            int num = stoi(query[1]);
            minHeap.push(num);
            maxHeap.push(num);
            r++;
        }
        else {
            if (f == r) {
                continue;
            }

            if (query[1].compare("1") == 0) {
                if (!maxHeap.empty()) {
                    maxHeap.pop();
                }
            }
            else {
                if (!minHeap.empty()) {
                    minHeap.pop();
                }
            }
            f++;
        }
    }

    if (f == r) {
        answer.push_back(0);
        answer.push_back(0);
    }
    else {
        if (!maxHeap.empty()) {
            answer.push_back(maxHeap.top());
        }
        if (!minHeap.empty()) {
            answer.push_back(minHeap.top());
        }
    }

    return answer;
}