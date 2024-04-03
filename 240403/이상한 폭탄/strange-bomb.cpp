#include <iostream>

#define MAX_N 200001

using namespace std;

int n,  // 폭탄 수
    k,  // 폭발하는 거리
    bombs[MAX_N],
    ans = -1;    // 폭발할 폭탄의 가장 큰 번호

void init(){
    cin>>n>>k;
    for(int i = 0; i < n; ++i){
        cin>>bombs[i];
    }
}

void solve(){
    for(int i = 0; i < n-k; ++i){
        for(int j = i+1 ; j <= i+k; ++j){
            if(bombs[j] == bombs[i]){
                if(ans < bombs[i]) ans = bombs[i];
                break;
            }
        }
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}