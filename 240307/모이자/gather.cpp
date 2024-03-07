#include <iostream>
#define MAX 10001;

using namespace std;

int n;  // 집
int* a; // 사람 수
int minCost;

void calcminCost(){
    for(int i = 1; i<=n; ++i){
        int sum = 0;
        for(int j = 1; j <= n; ++j){
            if(j == i) continue;
            sum += a[j] * abs(i-j);
        }
        if(sum < minCost) minCost = sum;
    }
    printf("%d", minCost);
}

int main() {
    minCost = MAX;
    scanf("%d", &n);
    a = new int[n+1];

    for(int i = 1; i <=n;++i){
        scanf("%d", &a[i]);
    }

    calcminCost();

    return 0;
}