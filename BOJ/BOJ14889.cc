#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, ans;
vector<int> order;
vector<vector<int>> S;

int solve(vector<int>& teamA, vector<int>& teamB) {
    int teamA_score, teamB_score;
    teamA_score = 0, teamB_score = 0;

    int aSize = teamA.size();
    int bSize = teamB.size();

    for (int i = 0; i < aSize-1; ++i) {
        for (int j = i+1; j < aSize; ++j) {
            teamA_score += S[teamA[i]][teamA[j]];
            teamA_score += S[teamA[j]][teamA[i]];
        }
    }

    for (int i = 0; i < bSize-1; ++i) {
        for (int j = i+1; j < bSize; ++j) {
            teamB_score += S[teamB[i]][teamB[j]];
            teamB_score += S[teamB[j]][teamB[i]];
        }
    }

    return abs(teamA_score - teamB_score);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N;

    S.resize(N, vector<int>(N,0));
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        cin >> S[i][j];

    order.resize(N/2, 0);
    for (int loop = 0; loop < N/2; ++loop) 
        order.push_back(1);
    
    ans = 987654321;
    
    do {

        vector<int> teamA, teamB;
        for (int i = 0; i < order.size(); ++i) {
            if (order[i]) 
                teamA.push_back(i);
            else 
                teamB.push_back(i);
        }      

        ans = min(ans, solve(teamA,teamB));
    } while (next_permutation(order.begin(), order.end()));

    cout << ans << "\n";
    return 0;
}