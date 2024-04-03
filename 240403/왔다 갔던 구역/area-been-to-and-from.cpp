#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int n;
long long totalSize = 0,
    size,
    preX = 0, curX = 0;
char op;

vector<pair<long long, int>> points;    // <x, v>

void init(){
    cin>>n;
    preX = 0, curX = 0;
    for(int i = 0; i < n; ++i){
        cin>>size>>op;

        preX = curX;
        if(op == 'L'){
            curX += size;
        } else if( op == 'R'){
            curX -= size;
        }
        points.push_back(
            make_pair(min(preX, curX), 1)
        );
        points.push_back(
            make_pair(max(preX, curX), -1)
        );
    }
    sort(points.begin(), points.end());
}

void solve(){
    int overlap = 0;
    preX = 0, curX = 0;
    for(int i = 0; i < n*2; ++i){
        long long x;
        int v;
        tie(x, v) = points[i];

        preX = curX;
        curX = x;
        if(overlap >= 2){
            totalSize += curX-preX;
        }

        overlap += v;
    }
}

int main() {
    init();
    solve();
    cout<<totalSize;
    return 0;
}