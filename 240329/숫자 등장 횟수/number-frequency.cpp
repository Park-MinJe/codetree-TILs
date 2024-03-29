#include <iostream>
#include <unordered_map>

using namespace std;

int n, m;
unordered_map<int, int> mapCntNum;

void solve(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i){
        int tmp;
        scanf(" %d", &tmp);
        if(mapCntNum.find(tmp) == mapCntNum.end()){
            mapCntNum[tmp] = 1;
        }
        else{
            ++mapCntNum[tmp];
        }
    }

    for(int i = 0; i < m; ++i){
        int tmp;
        scanf(" %d", &tmp);
        printf("%d ", mapCntNum[tmp]);
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    solve();
    return 0;
}