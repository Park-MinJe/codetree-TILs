#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

int n, roomCnt;
unsigned int s, e;
vector<tuple<unsigned int, int , int>> days;    // <day, v, idx>
unordered_map<int, int> reservation;      // <idx, room number>
priority_queue<int> rooms;

bool compare(tuple<unsigned int, int , int>& t1, tuple<unsigned int, int , int>& t2){
    unsigned int day1, day2;
    int v1, v2, idx1, idx2;
    tie(day1, v1, idx1) = t1;
    tie(day2, v2, idx2) = t2;

    return day1 < day2 || (day1 == day2 && v1 > v2);
}

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>s>>e;
        days.push_back(
            make_tuple(s, 1, i)
        );
        days.push_back(
            make_tuple(e, -1, i)
        );
    }
    sort(days.begin(), days.end(), compare);
}

void solve(){
    roomCnt = 0;
    for(int i = 0; i < n*2; ++i){
        unsigned int day;
        int v, idx;
        tie(day, v, idx) = days[i];

        if(v == 1){
            if(rooms.empty()){
                ++roomCnt;
                rooms.push(-roomCnt);
            }
            reservation[idx] = rooms.top();
            rooms.pop();
        }
        else{
            rooms.push(
                reservation[idx]
            );
            reservation.erase(idx);
        }

        // debug
        // printf("%u %d %d::%d\n", day, v, idx, roomCnt);
    }
}

int main() {
    init();
    solve();
    cout<<roomCnt;
    return 0;
}