#define ll long long
#include <algorithm>
#include <cmath>
using namespace std;

ll gcd(ll a, ll b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}
long long solution(int w,int h) {
    return (ll)w*h - (w+h - gcd(w,h));
}