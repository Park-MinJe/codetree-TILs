#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 51

using namespace std;

int n,
    parents[MAX_N],
    root,
    trgt,
    cnt = 0;
vector<int> tree[MAX_N];    // 인접 리스트
bool isVisited[MAX_N];

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>parents[i];
        if(parents[i] == -1)
            root = i;
        else{
            tree[parents[i]].push_back(i);
            // tree[i].push_back(parents[i]);
        }
    }
    cin>>trgt;
}

void dfs(){
    queue<int> q;
    q.push(root);
    isVisited[root] = true;

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        // debug
        // cout<<cur<<"\n";

        if(tree[cur].empty()){
            ++cnt;  // 리프 노드 추가
        }

        vector<int>::iterator child;
        for(child = tree[cur].begin(); child != tree[cur].end(); ++child){
            if(*child != trgt && !isVisited[*child]){ // 지운 노드가 아닌 경우
                q.push(*child);
                isVisited[*child] = true;
            }
        }
    }
}

void solve(){
    if(root == trgt){
        return;
    }
    dfs();
}

int main() {
    init();
    solve();
    cout<<cnt;
    return 0;
}