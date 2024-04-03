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
    sort(days.begin(), days.end());
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
    }
}

int main() {
    init();
    solve();
    cout<<roomCnt;
    return 0;
}