#include <iostream>
#include <vector>

#define MAX_N 100001

using namespace std;

int n, p, c,
    toParent[MAX_N-1];
vector<int> toChild[MAX_N-1];
vector<int> leafs;
int H[MAX_N];

void init(){
    cin>>n;

    for(int i = 0; i <= n; ++i){
        H[i] = -1;
    }
    H[1] = 0;

    for(int i = 0; i < n-1; ++i){
        cin>>p>>c;
        toParent[c] = p;
        toChild[p].push_back(c);

        if(p == 1)
            H[c] = 1;
    }

    // 리프 노드를 구한다.
    for(int i = 1; i <= n; ++i){
        if(toChild[i].empty()){
            leafs.push_back(i);
        }
    }
}

void dfs(int node){
    vector<int>::iterator it;
    for(it = toChild[node].begin(); it != toChild[node].end(); ++it){
        H[*it] = H[node] + 1;
        dfs(*it);
    }
}

// int getHeight(int node, int h){
//     if(H[node] != -1) return H[node];
//     if(node == 1) return h;

//     H[node] = getHeight(toParent[node], h+1);
//     return H[node];
// }

bool solve(){
    dfs(1);

    int totalHeight = 0;
    
    vector<int>::iterator leaf;
    for(leaf = leafs.begin(); leaf != leafs.end(); ++leaf){
        // totalHeight += getHeight(*leaf, 0);
        totalHeight += H[*leaf];
    }

    // a가 선공이므로, totalHeight가 홀수여야 승리한다.
    if(totalHeight % 2 == 1)
        return true;
    else
        return false;
}

int main() {
    init();
    if(solve()){
        cout<<"1";
    }
    else{
        cout<<"0";
    }
    return 0;
}