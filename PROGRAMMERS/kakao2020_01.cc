#define pii pair<int,int>
#define Y  first
#define X second
#define STAR 10
#define ZERO 11
#define SHARP 12
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

const int WIDTH = 3;

pii lThumb, rThumb;
vector<pii> vp;


int getDistance(pii thumb, pii number)
{
    return abs(thumb.Y - number.Y) + abs(thumb.X - number.X);
}
vector<pii> init_position() {

    vector<pii> ret;

    //DUMMY
    ret.push_back(make_pair(-1,-1));

    for (int i = 0; i < 12; ++i) 
    {
        int y = i / WIDTH;
        int x = i % WIDTH;
        ret.push_back(make_pair(y,x));
    }

    return ret;
}

string solution(vector<int> numbers, string hand) {
    string answer = "";

    vp = init_position();
    
    lThumb = vp[STAR];
    rThumb = vp[SHARP];

    for (int num : numbers)
    {
        if (num == 1 || num == 4 || num == 7) 
        {
            lThumb = vp[num];
            answer += "L";
        }
        else if (num == 3 || num == 6 || num == 9)
        {
            rThumb = vp[num];
            answer += "R";
        }
        else 
        {
            if (num == 0) {
                num = ZERO;
            }

            //거리 비교 
            int leftDist = getDistance(lThumb, vp[num]);
            int rightDist = getDistance(rThumb, vp[num]);

            //가까운 놈이 처리
            if (leftDist < rightDist) 
            {
                lThumb = vp[num];
                answer += "L";
            }
            else if (rightDist < leftDist)
            {
                rThumb = vp[num];
                answer += "R";
            }
            else
            {
                if (hand.compare("left") == 0) 
                {
                    lThumb = vp[num];
                    answer += "L";
                }
                else 
                {
                    rThumb = vp[num];
                    answer += "R";
                }
            }
        }
    }
    
    return answer;
}