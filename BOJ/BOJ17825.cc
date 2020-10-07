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

//�� ROW ���� �Ʒ� endLine �̻� �����ϸ� ������ ��
int endLine[4] = {13,12,13,6};

bool isDuplicated(int targetIdx,  int nowTokenNumber, int now_y, int now_x)
{
    //case1. ��¥�� ���� ��ǥ�̸� �ߺ�
    if (token[targetIdx].Y == now_y && token[targetIdx].X == now_x
    //case2. �� �� �������ε� 25,30,35,40 �� �ϳ��� ���� ��� �ִ� ���
    || (hasArrivedSpecialPosition[targetIdx] && hasArrivedSpecialPosition[nowTokenNumber] 
            && (token[targetIdx].X > SPEICAL_COLUMN && now_x > SPEICAL_COLUMN)
            && (map[token[targetIdx].Y][token[targetIdx].X] == map[now_y][now_x]))
    //case3. 40�� ���� ��� �ִ� ���
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

    //�̵��� X�����θ� ��
    nx = x + diceNumber;

    //Ư���� ĭ ���� �� �ִ��� check
    //Ư���� ĭ�� ���� ���� �ִٸ�
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
            //Ư���� ĭ�� ���� ���� ������ ���� ������ ĭ�� �ƴ� ���
            
            //�ٸ� �� �ִ��� Ȯ��
            for (int i = 0; i < TOKEN_SIZE; ++i)
            {
                if (i != tokenNumber)
                {
                    if (isDuplicated(i,tokenNumber,y,nx))
                        return -1;
                }
            }

            //�ٸ� ���� ���� ��� 
            //1. �� ĭ���� �̵� ��
            //2. �� ĭ�� ������ŭ ����
            tokenPosition.Y = y;
            tokenPosition.X = nx;
            return map[y][nx];
        }
    }
    //2.Ư���� ĭ�� ���� ���� ���ٸ�
    else
    {
        //2-1.Ư����ǥ�� ���
        if (nx == SPEICAL_COLUMN)
        {
            //�ٸ� �� �ִ��� Ȯ��
            for (int i = 0; i < TOKEN_SIZE; ++i)
            {
                if (i != tokenNumber)
                {
                    if (isDuplicated(i,tokenNumber,y,nx))
                        return -1;
                }
            }

            //�ٸ� ���� ���� ��� 

            //0. Ư�� ��ǥ �̵����� �÷��� ����
            //1. �� ĭ���� �̵� ��
            //2. �� ĭ�� ������ŭ ����

            hasArrivedSpecialPosition[tokenNumber] = true;
            tokenPosition.Y = y;
            tokenPosition.X = nx;
            return map[y][nx];
        }
        //2-2. Ư����ǥ�� �ƴ� ���
        else
        {
            //2-2-1.Ư�� ��ǥ�� �ƴѵ� SPEICAL_COLUMN ĭ ���� �� �� ���
            if (nx > SPEICAL_COLUMN)
            {
                //������ ��ǥ���� Ȯ�� (������ ĭ��)
                if (nx >= endLine[y])
                {
                    isFinished[tokenNumber] = true;
                    nx = min(nx,endLine[y]);
                    tokenPosition.Y = y;
                    tokenPosition.X = nx;
                    return map[y][nx];
                }
                //������ ��ǥ�� �ƴ� ��� (���� �Ϲ����� ���̽�)
                else
                {
                    y = min(MAP_ROW-1, y+1);
                    nx = nx % SPEICAL_COLUMN;

                    //�ٸ� �� �ִ��� Ȯ��
                    for (int i = 0; i < TOKEN_SIZE; ++i)
                    {
                        if (i != tokenNumber)
                        {
                            if (isDuplicated(i,tokenNumber,y,nx))
                                return -1;
                        }
                    }

                    //�ٸ� ���� ���� ��� 
                    //1. �� ĭ���� �̵� ��
                    //2. �� ĭ�� ������ŭ ����
                    tokenPosition.Y = y;
                    tokenPosition.X = nx;
                    return map[y][nx];
                }
            }
            //2-2-2.Ư�� ��ǥ�� �ƴϰ� OFFSET��ŭ ���� ���� ���
            else
            {
                //�ٸ� �� �ִ��� Ȯ��
                for (int i = 0; i < TOKEN_SIZE; ++i)
                {
                    if (i != tokenNumber)
                    {
                        if (isDuplicated(i,tokenNumber,y,nx))
                            return -1;
                    }
                }

                //�ٸ� ���� ���� ��� 
                //1. �� ĭ���� �̵� ��
                //2. �� ĭ�� ������ŭ ����
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
        //����� �� ����
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
            //���� ���� ��
            int tokenNumber = candidate[gameLoop];

            //���� ���� ����
            int diceNumber = diceNumbers[gameLoop];

            //�� �����ִ��� ���º��� üũ
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
            //������ �ó������� ���
            //ans ����
            ans = max(ans,score);
        }
    }

    cout << ans << "\n";

    return 0;
}