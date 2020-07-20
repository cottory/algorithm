#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//점화식: dp[h][w] = triangle[h][w] + max(dp[h-1][w-1], dp[h-1][w]);
int tSize;
vector<vector<int>> dp;

bool isSafe(int height, int width) {
    if (height < 0 || height > tSize - 1)
        return false;
    
    if (width < 0 || width > height)
        return false;

    return true;
}
int solve(vector<vector<int>>& triangle, int height, int width) {

    if (!isSafe(height, width))
        return dp[height][width] = 0;

    if (dp[height][width] != -1)
        return dp[height][width];

    int ret = triangle[height][width] + max(solve(triangle, height-1, width-1), solve(triangle, height-1, width));
    return dp[height][width] = ret;
}
int solution(vector<vector<int>> triangle) {
    int answer = 0;
    tSize = triangle.size();
    
    dp.resize(tSize + 1, vector<int>(tSize + 1, -1));
    dp[0][0] = triangle[0][0];
    
    for (int i = 0; i < tSize; ++i) 
        solve(triangle, tSize - 1, i);
    
    for (int i = 0; i < tSize; ++i)
        answer = max(answer, dp[tSize-1][i]);

    return answer;
}