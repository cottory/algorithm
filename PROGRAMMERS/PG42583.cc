#define WEIGHT first
#define TIME second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

queue<pii> q;
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int nowWeight = 0, cnt = 0, idx = 0;
    const int truckSize = truck_weights.size();
    
    while (cnt < truckSize) {
        
        int loop = q.size();

        while (loop--) {
            pii now = q.front(); q.pop();
            if (now.TIME < bridge_length) {
                now.TIME += 1;
                q.push({now});
            }
            else {
                nowWeight -= now.WEIGHT;
                cnt += 1;
            }
        }

        if (nowWeight + truck_weights[idx] <= weight) {
            q.push({truck_weights[idx],1});
            nowWeight += truck_weights[idx++];
        }

        answer += 1;
    }

    return answer;
}
