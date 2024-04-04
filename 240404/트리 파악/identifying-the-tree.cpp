#include <iostream>
#include <vector>

#define MAX_N 100001

using namespace std;

int n, p, c,
    toParent[MAX_N-1];
vector<int> toChild[MAX_N-1];
vector<int> leafs;

void init(){
    cin>>n;
    for(int i = 0; i < n-1; ++i){
        cin>>p>>c;
        toParent[c] = p;
        toChild[p].push_back(c);
    }

    // 리프 노드를 구한다.
    for(int i = 1; i <= n; ++i){
        if(toChild[i].empty()){
            leafs.push_back(i);
        }
    }
}

int getHeight(int node, int h){
    if(node == 1) return h;

    return getHeight(toParent[node], h+1);
}

bool solve(){
    int totalHeight = 0;
    
    vector<int>::iterator leaf;
    for(leaf = leafs.begin(); leaf != leafs.end(); ++leaf){
        totalHeight += getHeight(*leaf, 0);
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