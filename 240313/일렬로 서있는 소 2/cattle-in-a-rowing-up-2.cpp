#include <iostream>
#include <vector>
using namespace std;

int n,
    cnt = 0;
int* lstH;
vector<int>* lstSet;

void getInput(){
    scanf("%d", &n);
    lstH = new int[n+1];
    for(int i = 1; i <= n; ++i){
        scanf("%d", &lstH[i]);
    }
    lstSet = new vector<int>[n+1];
}

void dfs(int len, int startIdx){
    if(len == 1){
        ++cnt;
        return;
    }

    vector<int>::iterator it;
    for(it = lstSet[startIdx].begin(); it != lstSet[startIdx].end(); ++it){
        dfs(len-1, *it);
    }
}

void solve(){
    for(int i = 1; i <= n-1; ++i){
        for(int j = i+1; j <=n; ++j){
            if(lstH[i] <= lstH[j]){
                lstSet[i].push_back(j);
            }
        }
    }
    for(int i = 1; i <= n-1; ++i){
        dfs(3, i);
    }
}

int main() {
    getInput();
    solve();
    printf("%d", cnt);
    return 0;
}