#define Pair pair<int,int>
#define Y first
#define X second
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAP_ROW = 4;
const int SPEICAL_COLUMN = 5;
const int TOKEN_SIZE = 4;
const int DICE_SIZE = 10;
const int FINISHED = 0;
vector<Pair> token;
vector<int> diceNumbers;
vector<bool> isFinished, hasArrivedSpecialPosition;

//ROW
//COL
int map[4][15] = {
    {0,2,4,6,8,10,13,16,19,25,30,35,40,FINISHED,},
    {0,12,14,16,18,20,22,24,25,30,35,40,FINISHED,},
    {0,22,24,26,28,30,28,27,26,25,30,35,40,FINISHED,},
    {0,32,34,36,38,40,FINISHED,}
};

//각 ROW 마다 아래 endLine 이상 도달하면 도착한 것
int endLine[4] = {13,12,13,6};

bool isDuplicated(int targetIdx,  int nowTokenNumber, int now_y, int now_x)
{
    //case1. 진짜로 같은 좌표이면 중복
    if (token[targetIdx].Y == now_y && token[targetIdx].X == now_x
    //case2. 둘 다 지름길인데 25,30,35,40 중 하나를 같이 밟고 있는 경우
    || (hasArrivedSpecialPosition[targetIdx] && hasArrivedSpecialPosition[nowTokenNumber] 
            && (token[targetIdx].X > SPEICAL_COLUMN && now_x > SPEICAL_COLUMN)
            && (map[token[targetIdx].Y][token[targetIdx].X] == map[now_y][now_x]))
    //case3. 40을 같이 밟고 있는 경우
    || (map[token[targetIdx].Y][token[targetIdx].X] == 40 && map[now_y][now_x] == 40))
        return true;
    
    return false;
}

int move(Pair& tokenPosition, int tokenNumber, int diceNumber)
{
    int result = 0;
    int y,x,ny,nx;
    y = tokenPosition.Y;
    x = tokenPosition.X;

    //이동은 X축으로만 함
    nx = x + diceNumber;

    //특수한 칸 밟은 적 있는지 check
    //특수한 칸을 밟은 적이 있다면
    if (hasArrivedSpecialPosition[tokenNumber])
    {
        if (nx >= endLine[y])
        {
            isFinished[tokenNumber] = true;
            nx = min(nx,endLine[y]);
            tokenPosition.Y = y;
            tokenPosition.X = nx;
            return map[y][nx];
        }
        else
        {
            //특수한 칸을 밟은 적이 있지만 아직 마지막 칸이 아닌 경우
            
            //다른 말 있는지 확인
            for (int i = 0; i < TOKEN_SIZE; ++i)
            {
                if (i != tokenNumber)
                {
                    if (isDuplicated(i,tokenNumber,y,nx))
                        return -1;
                }
            }

            //다른 말이 없는 경우 
            //1. 그 칸으로 이동 후
            //2. 그 칸의 점수만큼 갱신
            tokenPosition.Y = y;
            tokenPosition.X = nx;
            return map[y][nx];
        }
    }
    //2.특수한 칸을 밟은 적이 없다면
    else
    {
        //2-1.특수좌표인 경우
        if (nx == SPEICAL_COLUMN)
        {
            //다른 말 있는지 확인
            for (int i = 0; i < TOKEN_SIZE; ++i)
            {
                if (i != tokenNumber)
                {
                    if (isDuplicated(i,tokenNumber,y,nx))
                        return -1;
                }
            }

            //다른 말이 없는 경우 

            //0. 특수 좌표 이동가능 플래그 셋팅
            //1. 그 칸으로 이동 후
            //2. 그 칸의 점수만큼 갱신

            hasArrivedSpecialPosition[tokenNumber] = true;
            tokenPosition.Y = y;
            tokenPosition.X = nx;
            return map[y][nx];
        }
        //2-2. 특수좌표가 아닌 경우
        else
        {
            //2-2-1.특수 좌표가 아닌데 SPEICAL_COLUMN 칸 보다 더 뛴 경우
            if (nx > SPEICAL_COLUMN)
            {
                //마지막 좌표인지 확인 (마지막 칸용)
                if (nx >= endLine[y])
                {
                    isFinished[tokenNumber] = true;
                    nx = min(nx,endLine[y]);
                    tokenPosition.Y = y;
                    tokenPosition.X = nx;
                    return map[y][nx];
                }
                //마지막 좌표가 아닌 경우 (가장 일반적인 케이스)
                else
                {
                    y = min(MAP_ROW-1, y+1);
                    nx = nx % SPEICAL_COLUMN;

                    //다른 말 있는지 확인
                    for (int i = 0; i < TOKEN_SIZE; ++i)
                    {
                        if (i != tokenNumber)
                        {
                            if (isDuplicated(i,tokenNumber,y,nx))
                                return -1;
                        }
                    }

                    //다른 말이 없는 경우 
                    //1. 그 칸으로 이동 후
                    //2. 그 칸의 점수만큼 갱신
                    tokenPosition.Y = y;
                    tokenPosition.X = nx;
                    return map[y][nx];
                }
            }
            //2-2-2.특수 좌표가 아니고 OFFSET만큼 뛰지 않은 경우
            else
            {
                //다른 말 있는지 확인
                for (int i = 0; i < TOKEN_SIZE; ++i)
                {
                    if (i != tokenNumber)
                    {
                        if (isDuplicated(i,tokenNumber,y,nx))
                            return -1;
                    }
                }

                //다른 말이 없는 경우 
                //1. 그 칸으로 이동 후
                //2. 그 칸의 점수만큼 갱신
                tokenPosition.Y = y;
                tokenPosition.X = nx;
                return map[y][nx];
            }
        }
    }
}

int main(void)
{
    for (int num,i = 0; i < DICE_SIZE; ++i)
    {
        cin >> num;
        diceNumbers.push_back(num);
    }

    int ans = -1;
    isFinished.resize(TOKEN_SIZE, false);
    hasArrivedSpecialPosition.resize(TOKEN_SIZE, false);
    
    for (int state = 0; state < (1 << 20); ++state)
    {
        //경우의 수 생성
        int nowState = state;
        vector<int> candidate;
        
        for (int loop = 0; loop < DICE_SIZE; ++loop)
        {
            int tokenNumber = nowState % TOKEN_SIZE;
            candidate.push_back(tokenNumber);
            nowState /= TOKEN_SIZE;
        }

        //simulation
        int gameLoop, score = 0;
        token.clear();
        token.resize(TOKEN_SIZE,{0,0});
        fill(isFinished.begin(), isFinished.end(), false);
        fill(hasArrivedSpecialPosition.begin(), hasArrivedSpecialPosition.end(), false);

        for (gameLoop = 0; gameLoop < DICE_SIZE; ++gameLoop)
        {
            //지금 던질 말
            int tokenNumber = candidate[gameLoop];

            //지금 던질 숫자
            int diceNumber = diceNumbers[gameLoop];

            //얘 끝나있는지 상태부터 체크
            if (isFinished[tokenNumber])
                break;

            //move(Pair& tokenPosition, int tokenNumber, int diceNumber)
            int result = move(token[tokenNumber], tokenNumber, diceNumber);
            if (result == -1)
            {
                break;
            }
            else
            {
                score += result;
            }
        }

        if (gameLoop == DICE_SIZE)
        {
            //가능한 시나리오인 경우
            //ans 갱신
            ans = max(ans,score);
        }
    }

    cout << ans << "\n";

    return 0;
}