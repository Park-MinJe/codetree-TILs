#include <iostream>
#include <unordered_map>
#include <vector>

#define MAX_N 1001

using namespace std;

int n, k, ans = 0,
    arr[MAX_N], // 증가수열
    curParentIdx;
unordered_map<int, int> toParent;
vector<int> toChild[MAX_N];

void init(){
    cin>>n>>k;
    for(int i = 0; i <n; ++i){
        cin>>arr[i];
    }

    curParentIdx = 0;
    for(int i = 1; i < n; ++i){
        toParent[arr[i]] = arr[curParentIdx];
        toChild[arr[curParentIdx]].push_back(arr[i]);
        if(i+1 < n && arr[i+1] != arr[i]+1){
            ++curParentIdx;
        }
    }
    // debug
    // unordered_map<int, int>::iterator it;
    // for(it = toParent.begin(); it != toParent.end(); ++it){
    //     cout<<it->first<<" "<<it->second<<"\n";
    // }
}

void solve(){
    int trgtParent = toParent[k],
        trgtGrandParent = toParent[trgtParent];
    
    vector<int>::iterator parentIt;
    vector<int>::iterator childIt;
    for(parentIt = toChild[trgtGrandParent].begin(); parentIt != toChild[trgtGrandParent].end(); ++parentIt){
        if(*parentIt == trgtParent) continue;

        ans += toChild[*parentIt].size();
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}