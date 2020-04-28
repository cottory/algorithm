#include <string>
#include <vector>
#include <stack>
using namespace std;

stack<int> basket;

int pick(vector<vector<int>> &board, int idx)
{
    int ret = 0;
    for (int row = 0; row < board.size(); ++row)
    {
        if (board[row][idx])
        {
            ret = board[row][idx];
            board[row][idx] = 0;
            break;
        }
    }
    return ret;
}

bool isEmpty(vector<vector<int>> &board, int idx)
{
    for (int row = 0; row < board.size(); ++row)
    {
        if (board[row][idx]) return false;
    }

    return true;
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    for (int idx : moves)
    {
        idx -= 1;
        if (isEmpty(idx)) 
        {
            continue;
        }
        else 
        {
            int doll = pick(idx);

            if (basket.empty())
            {
                basket.push(doll);
            }
            else 
            {
                if (basket.top() == doll) 
                {
                    basket.pop();
                    answer += 1;
                }
                else 
                {
                    basket.push(doll);
                }
            }
        }
    }

    return answer * 2;
}