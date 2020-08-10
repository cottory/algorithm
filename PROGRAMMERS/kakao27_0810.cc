#define TYPE_STICK 0
#define TYPE_PAPER 1
#define REMOVE 0
#define SET 1
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int stick[110][110], paper[110][110];

bool isPossibleToSetStick(int y, int x)
{
    if (y == 0) return true;
    else if (stick[y-1][x]) return true;
    else if (paper[y][x] || (x > 0 && paper[y][x-1])) return true;

    return false;
}

bool isPossibleToSetPaper(int y, int x)
{
    if (y > 0 && stick[y-1][x]) return true;
    else if (y > 0 && stick[y-1][x+1]) return true;
    else if ((x > 0 && paper[y][x-1]) && paper[y][x+1]) return true;

    return false;
}

vector<vector<int>> setCandidate()
{
    vector<vector<int>> result;

    for (int x = 0; x <= N; ++x)
    {
        for (int y = 0; y <= N; ++y)
        {            
            if (stick[y][x]) {
                vector<int> candidate;
                candidate.push_back(x);
                candidate.push_back(y);
                candidate.push_back(TYPE_STICK);
                result.push_back(candidate);
            }
            if (paper[y][x]) {
                vector<int> candidate;
                candidate.push_back(x);
                candidate.push_back(y);
                candidate.push_back(TYPE_PAPER);
                result.push_back(candidate);
            }
        }
    }

    return result;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {

    vector<vector<int>> answer;
    N = n;

    for (vector<int> build : build_frame)
    {
        int x,y,type,build_type;
        x = build[0];   //가로좌표
        y = build[1];   //세로좌표
        type = build[2];    //기둥 OR 보
        build_type = build[3];  //설치 OR 삭제

        if (type == TYPE_STICK && build_type == SET) 
        {
            if (isPossibleToSetStick(y,x))
                stick[y][x] = 1;
        }
        else if (type == TYPE_PAPER && build_type == SET)
        {
            if (isPossibleToSetPaper(y,x))
                paper[y][x] = 1;
        }
        else if (type == TYPE_STICK && build_type == REMOVE)
        {
            bool isPossibleToRemove = true;
            stick[y][x] = 0;
            
            if (stick[y+1][x] && !isPossibleToSetStick(y+1,x)) isPossibleToRemove = false;
            else if (paper[y+1][x] &&!isPossibleToSetPaper(y+1,x)) isPossibleToRemove = false;
            else if (x > 0 && y < N && paper[y+1][x-1] && !isPossibleToSetPaper(y+1,x-1)) isPossibleToRemove = false;

            if (!isPossibleToRemove)
                stick[y][x] = 1;
        }
        else if (type == TYPE_PAPER && build_type == REMOVE)
        {
            bool isPossibleToRemove = true;
            paper[y][x] = 0;

            if (stick[y][x] && !isPossibleToSetStick(y,x)) isPossibleToRemove = false;
            else if (stick[y][x+1] && !isPossibleToSetStick(y,x+1)) isPossibleToRemove = false;
            else if (x > 0 && paper[y][x-1] && !isPossibleToSetPaper(y,x-1)) isPossibleToRemove = false; 
            else if (paper[y][x+1] && !isPossibleToSetPaper(y,x+1)) isPossibleToRemove = false;

            if (!isPossibleToRemove)
                paper[y][x] = 1;
        }
    }

    return answer = setCandidate();
}