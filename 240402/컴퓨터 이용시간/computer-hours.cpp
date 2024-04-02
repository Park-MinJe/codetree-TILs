#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <set>

#define MAX_N 100001

using namespace std;

int n, p, q,
    seat[MAX_N];
vector<tuple<int, int, int>> times; // <t, v, idx>
set<int> seatNums;

void init(){
    cin>>n; // 사람 수
    for(int i = 0; i < n; ++i){
        cin>>p>>q;
        times.push_back(
            make_tuple(p, 1, i)
        );
        times.push_back(
            make_tuple(q, -1, i)
        );

        seatNums.insert(i+1);
    }

    sort(times.begin(), times.end());
}

void solve(){
    for(int i = 0; i < n*2; ++i){
        int t, v, idx;
        tie(t, v, idx) = times[i];

        if(v == 1){
            seat[idx] = (*seatNums.begin());
            seatNums.erase(seat[idx]);
        }
        else{
            seatNums.insert(seat[idx]);
        }
    }
}

void printResult(){
    for(int i = 0; i < n; ++i){
        cout<<seat[i]<<" ";
    }
}

int main() {
    init();
    solve();
    printResult();
    return 0;
}