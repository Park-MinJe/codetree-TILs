#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAX_NM 100001

using namespace std;

int n, m;
long long points[MAX_NM],
    start, _end;
vector<pair<long long, long long>> segs;

void init(){
    cin>>n>>m;

    for(int i = 0; i < n; ++i)
        cin>>points[i];
    sort(points, points+n);
    
    for(int i = 0; i < m; ++i){
        cin>>start>>_end;
        segs.push_back(
            make_pair(start, _end)
        );
    }
}

void solve(){
    for(int i = 0; i < m; ++i){
        tie(start, _end) = segs[i];
        cout<<upper_bound(points, points + n, _end) - lower_bound(points, points+n, start)<<"\n";
    }
}

int main() {
    init();
    solve();
    return 0;
}