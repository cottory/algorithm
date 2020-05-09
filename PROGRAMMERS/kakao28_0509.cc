#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct Bus {
    int passenger_number;
    bool full;
    string start_time;
    vector<string> passenger_list;
    Bus(string st) : start_time(st), full(false), passenger_number(0) {}
}Bus;

int N, T, M;
vector<Bus> bus_list;

bool take_a_bus(Bus bus, string passenger)
{
    if (bus.full) return false;
    if (bus.start_time.compare(passenger) < 0) return false;
    return true;
}

int to_minute(string time_info)
{
    string h,m;
    int h_int, m_int;
    h = time_info.substr(0,2);
    m = time_info.substr(3,2);
    
    h_int = stoi(h);
    m_int = stoi(m);

    return (h_int * 60) + m_int;
}
string to_time(int _minute)
{
    string ret = "";

    int hour = _minute / 60;
    int minute = _minute % 60;

    if (hour <= 9)
     ret += "0";

    ret += to_string(hour);

    ret += ":";

    if (minute <= 9)
        ret += "0";
    
    ret += to_string(minute);

    return ret;
}

string solve()
{
    string ret;
    Bus bus = bus_list.back();

    if (bus.full == false)
        return bus.start_time;
    
    string my_rival = bus.passenger_list.back();
    int my_rival_minute = to_minute(my_rival);

    return to_time(my_rival_minute - 1);
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";

    N = n;
    T = t;
    M = m;

    sort(timetable.begin(), timetable.end());

    string time = "09:00";
    for (int i = 0; i < N; ++i)
    {
        bus_list.push_back(Bus(time));

        int nxt_time = to_minute(time);
        nxt_time += T;
        time = to_time(nxt_time);
    }

    //한 놈씩 버스에 태움
    for (string passenger : timetable)
    {
        bool used = false;

        for (Bus &bus : bus_list)
        {
            if (used == true) 
                break;

            if (take_a_bus(bus, passenger))
            {
                used = true;
                bus.passenger_number += 1;
                bus.passenger_list.push_back(passenger);
                if (bus.passenger_number == M)
                    bus.full = true;
            }
        }
    }

    answer = solve();
    return answer;
}