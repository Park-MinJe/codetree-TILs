#include <iostream>
#include <vector>

using namespace std;

int n, k, cnt = 0;
vector<int> coins;

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; ++i){
        int tmpC;
        scanf(" %d", &tmpC);
        coins.push_back(tmpC);
    }

    for(int i = n-1; i >= 0; --i){
        int tmpCnt = k/coins[i];
        cnt += tmpCnt;
        k -= tmpCnt*coins[i];
        
        if(k == 0){
            printf("%d", cnt);
            break;
        }
    }
    
    return 0;
}