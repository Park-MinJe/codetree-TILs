#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 100001

using namespace std;

int n, s, e, w,
    farNode;
long long maxCost = 0;
vector<pair<int, int>> tree[MAX_N];    // <node, w>
bool isVisited[MAX_N];

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>s>>e>>w;
        tree[s].push_back(
            make_pair(e, w)
        );
        tree[e].push_back(
            make_pair(s, w)
        );
    }
}

void dfs(int curNode, long long curCost){

    if(!isVisited[curNode]){
        isVisited[curNode] = true;

        if(maxCost < curCost){
            maxCost = curCost;
            farNode = curNode;
        }

        vector<pair<int, int>>::iterator it;
        for(it = tree[curNode].begin(); it != tree[curNode].end(); ++it){
            dfs(
                it->first,
                it->second + curCost
            );
        }
    }
}

void solve(){
    dfs(1, 0);
    for(int i = 1; i <= n; ++i){
        isVisited[i] = false;
    }
    maxCost = 0;

    dfs(farNode, 0);
}

int main() {
    init();
    solve();
    cout<<maxCost;
    return 0;
}