#include <iostream>
#include <unordered_map>

#define MAX_N 200001

using namespace std;

int n,  // 폭탄 수
    k,  // 폭발하는 거리
    bombs[MAX_N], R[MAX_N],
    ans = -1;    // 폭발할 폭탄의 가장 큰 번호

void init(){
    cin>>n>>k;
    for(int i = 0; i < n; ++i){
        cin>>bombs[i];
    }
}

void solve(){
    unordered_map<int, int> latest_index;
    for(int i = n-1; i >= 0; --i){
        if(latest_index.find(bombs[i]) == latest_index.end()){
            R[i] = -1;
        }
        else{
            R[i] = latest_index[bombs[i]];
        }

        latest_index[bombs[i]] = i;
    }

    for(int i = 0; i < n; ++i){
        if(R[i] != -1 && R[i] - i <= k){
            ans = max(ans, bombs[i]);
        }
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}