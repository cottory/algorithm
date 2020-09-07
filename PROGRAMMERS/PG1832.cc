#define WALL 1
#define SPECIAL_BLOCK 2
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 20170805;
const int BOARD_SIZE = 502;

int solution(int m, int n, vector<vector<int>> city_map) {
    
    int answer = 0;
    int right[BOARD_SIZE][BOARD_SIZE];
    int down[BOARD_SIZE][BOARD_SIZE];

    memset(right,0,sizeof(right));
    memset(down,0,sizeof(down));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int block = city_map[i-1][j-1];
            
            if (i == 1 && j == 1)
            {
                right[i][j] = 1;
                down[i][j] = 1;
            }
            else if (block == WALL)  
            {
                right[i][j] = 0;
                down[i][j] = 0;
            }
            else if (block == SPECIAL_BLOCK)
            {
                right[i][j] = right[i][j-1];
                down[i][j] = down[i-1][j];
            }
            else
            {
                right[i][j] = (right[i][j-1] + down[i-1][j]) % MOD;
                down[i][j] = (right[i][j-1] + down[i-1][j]) % MOD;
            }
        }
    }
    
    //answer = down[m][n]; 둘 중에 무얼해도 상관 X
    answer = right[m][n];
    return answer;
}