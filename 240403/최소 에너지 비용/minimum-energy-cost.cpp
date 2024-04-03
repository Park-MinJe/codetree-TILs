#include <iostream>

#define MAX_N 100001

using namespace std;

int n,
    dist[MAX_N],
    cost[MAX_N],
    min_cost[MAX_N];
long long ans = 0;

void init(){
    cin>>n;
    for(int i = 2; i <= n; ++i){
        cin>>dist[i];     // i에서 이동하는 데 드는 비용
    }
    for(int i = 1; i <= n; ++i){
        cin>>cost[i];     // i에서 에너지 1 충전에 드는 비용
    }
}

void solve(){
    min_cost[2] = cost[1];
    for(int i = 3; i <= n; ++i){
        min_cost[i] = min(
            min_cost[i-1],
            cost[i-1]
        );
    }

    for(int i = 1; i <=n; ++i){
        ans += (long long)min_cost[i] * dist[i];
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}