#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//0: 지우
//1: 경희
//2: 민호
const int MAX_LOOP = 20;
const int JIWOO = 0;
const int KYUNGHEE = 1;
const int MINHO = 2;

int N,K;
int player1, player2;
vector<vector<int>> balanced;
vector<int> jiwoo, kyunghee, minho;
int winCount[3];
int playersIdx[3];

//사람 change 함수
int getNextPlayer(int p1, int p2)
{
    return (3 - (p1 + p2));
}

//현재 이 사람이 뭐낼 건지 return하는 함수
int getSigniture(int player)
{
    int result = -1;
    if (player == JIWOO)
    {
        result = jiwoo[playersIdx[JIWOO]];
        playersIdx[JIWOO]++;
    }
    else if (player == KYUNGHEE)
    {
        result = kyunghee[playersIdx[KYUNGHEE]];
        playersIdx[KYUNGHEE]++;
    }
    else if (player == MINHO)
    {
        result = minho[playersIdx[MINHO]];
        playersIdx[MINHO]++;
    }

    return result;
}

//가위바위보 하는 함수 && 승리수 count 함수
int rps(int p1, int p2)
{
    int player1_signiture = getSigniture(p1);
    int player2_signiture = getSigniture(p2);

    if (balanced[player1_signiture][player2_signiture] == 2) 
    {
        return p1;
    }
    else if (balanced[player1_signiture][player2_signiture] == 1)
    {
        return p2;
    }
    else if (balanced[player1_signiture][player2_signiture] == 0)
    {
        return p2;
    }
}

//승자 나왔는지 체크하는 함수
bool isWinnerExisted()
{
    for (int i = 0; i < 3; ++i)
    {
        if (winCount[i] == K)
            return true;
    }
    
    return false;
}

//entrypoint 함수
bool solve()
{
    bool winnerFlag = false;

    for (int loop = 0; loop < MAX_LOOP; ++loop)
    {
        //1. 승자 나왔는지 체크
        if (isWinnerExisted())
        {
            winnerFlag = true;
            break;
        }

        //2. 지우가 낼 거 다 낸 경우 그냥 false
        if (playersIdx[JIWOO] == N)
        {
            break;
        }

        if (player1 > player2) 
            swap(player1, player2);
        
        //2. 가위바위보
        //3. 승리 수 count
        //4. 승자 return
        int winner = rps(player1, player2);
        winCount[winner]++;

        //5. 사람 change
        int nextPlayer = getNextPlayer(player1,player2);

        player1 = winner;
        player2 = nextPlayer;
    }

    if (winnerFlag)
    {
        return winCount[JIWOO] == K ? true : false;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    balanced.resize(N, vector<int>(N));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> balanced[i][j];
        }
    }

    for (int num,i = 0; i < MAX_LOOP; ++i)
    {
        cin >> num;
        num--;
        kyunghee.push_back(num);
    }

    for (int num,i = 0; i < MAX_LOOP; ++i)
    {
        cin >> num;
        num--;
        minho.push_back(num);
    }    

    bool answer = false;
    vector<int> order(N);
    for (int i = 0; i < N; ++i)
        order[i] = i;
    
    do {

        //simulation
        jiwoo = order;
        
        fill(winCount, winCount + 3, 0);
        fill(playersIdx, playersIdx + 3, 0);
        player1 = JIWOO;
        player2 = KYUNGHEE;

        if (solve()) 
        {
            answer = true;
            break;
        }

    } while (next_permutation(order.begin(), order.end()));
    
    if (answer) cout << 1 << "\n";
    else cout << 0 << "\n";

    return 0;
}