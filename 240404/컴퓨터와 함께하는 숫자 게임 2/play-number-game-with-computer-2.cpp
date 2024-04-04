#include <iostream>
#include <algorithm>

#define MAX_M 1000000000000000000

using namespace std;

long long m, a, b,
    L, R,
    minCnt = MAX_M,
    maxCnt = 0;

void init(){
    cin>>m;
    cin>>a>>b;
}

void solve(){
    for(long long trg = a; trg <= b; ++trg){
        long long tmpCnt = 1;
        L = 1; R = m;
        while(L <= R){
            long long mid = (L+R)/2;
            if(trg == mid){
                minCnt = min(minCnt, tmpCnt);
                maxCnt = max(maxCnt, tmpCnt);
                break;
            }
            else if(trg > mid){
                L = mid+1;
                ++tmpCnt;
            }
            else{
                R = mid-1;
                ++tmpCnt;
            }
        }
        // debug
        // printf("%lld::%lld\n", trg, tmpCnt);
    }
}

int main() {
    init();
    solve();
    cout<<minCnt<<" "<<maxCnt;
    return 0;
}