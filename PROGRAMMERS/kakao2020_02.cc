#define PLUS 0
#define MINUS 1
#define MULTI 2
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <deque>
using namespace std;
typedef long long ll;

stack<ll> tmp;
deque<ll> que;

deque<ll> parseNumber(string expression) {

    deque<ll> ret;

    int total = 0;
    for (char c : expression)
    {
        if ('0' <= c && c <= '9') 
        {
            int num = c - '0';
            total = (10 * total) + num;
        }
        else 
        {
            ret.push_back(ll(total));

            if (c == '+') ret.push_back(PLUS);
            else if (c == '-') ret.push_back(MINUS);
            else ret.push_back(MULTI);

            total = 0;
        }
    }

    ret.push_back(ll(total));

    return ret;
}

ll calculate_number(ll leftNumber, ll optr, ll rightNumber) {
    if (optr == PLUS) return leftNumber + rightNumber;
    else if (optr == MINUS) return leftNumber - rightNumber;
    else return leftNumber * rightNumber;
}

ll calculate(vector<ll> order) {

    for (int idx = 0; idx < order.size(); ++idx) 
    {
        if (que.size() == 1) 
            break;

        //po: priority_operator
        //priority_operator에 대해서만 연산하기
        ll po = order[idx];
        ll opndLeft, opndRight;
        ll optr;   //operator

        while (!que.empty())
        {
            opndLeft = que.front(); que.pop_front();
            optr = que.front(); que.pop_front();
            opndRight = que.front(); que.pop_front();

            if (optr == po) 
            {
                ll result = calculate_number(opndLeft, optr, opndRight);
                que.push_front(result);
            }
            else 
            {
                //현재 우선순위의 연산자가 아닐 시 그냥 tmp에 옮겨놓음
                tmp.push(opndLeft);
                tmp.push(optr);
                que.push_front(opndRight);
            }

            if (que.size() == 1) {
                break;
            }
        }

        while (!tmp.empty()) 
        {
            que.push_front(tmp.top());
            tmp.pop();
        }    
    }

    if (que.size() == 1) {
        return abs(que.front());
    }
    else 
        return 0;
}

ll solution(string expression) {
    ll answer = 0;
    vector<ll> order;

    for (int i = 0; i < 3; ++i)
        order.push_back(i);

    do {

        que = parseNumber(expression);
        
        while (!tmp.empty()) {
            tmp.pop();
        }

        ll candidate = calculate(order);
        answer = max(answer, candidate);

    } while(next_permutation(order.begin(), order.end()));

    return answer;
}