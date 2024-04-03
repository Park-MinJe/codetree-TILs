#include <iostream>

#define MAX_N 100001

using namespace std;

int n,
    movingCost[MAX_N],
    chargingCost[MAX_N];
long long
    movingCostToEnd[MAX_N],
    minChargingCostToEnd[MAX_N];

void init(){
    cin>>n;
    for(int i = 0; i < n-1; ++i){
        cin>>movingCost[i];     // i에서 이동하는 데 드는 비용
    }
    for(int i = n-2; i >= 0; --i){
        movingCostToEnd[i] = (long long) movingCost[i] + movingCostToEnd[i+1];
        //debug
        // printf("%d::%lld\n", i, movingCostToEnd[i]);
    }
    for(int i = 0; i < n; ++i){
        cin>>chargingCost[i];     // i에서 에너지 1 충전에 드는 비용
    }
}

void solve(){
    minChargingCostToEnd[n-2] = movingCost[n-2] * chargingCost[n-2];
    for(int i = n-3; i >= 0; --i){
        minChargingCostToEnd[i] = 
            min(
                minChargingCostToEnd[i+1] + movingCost[i] * chargingCost[i],
                movingCostToEnd[i] * chargingCost[i]
            );
    }
}

int main() {
    init();
    solve();
    cout<<minChargingCostToEnd[0];
    return 0;
}