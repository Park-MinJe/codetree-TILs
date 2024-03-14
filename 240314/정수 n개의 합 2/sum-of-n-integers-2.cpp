#include <iostream>

#define MAX_N 100000

using namespace std;

int n, k, tmpSum = 0, maxSum = 0;
int arr[MAX_N];

void setMaxSum(int tmpSum){
    if(maxSum < tmpSum){
        maxSum =tmpSum;
    }
}

void init(){
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; ++i){
        scanf(" %d", &arr[i]);
        if(i < k){
            tmpSum += arr[i];
        }
    }
    setMaxSum(tmpSum);
}

void solve(){
    for(int i = k; i < n; ++i){
        tmpSum = tmpSum - arr[i-k] + arr[i];
        setMaxSum(tmpSum);
    }
}

int main() {
    init();
    solve();
    printf("%d", maxSum);
    return 0;
}