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

        if(tree[cur].empty()
        || (tree[cur].size() == 1 && tree[cur][0] == trgt)){
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
void dfs_recursive(int curNode){
    if(tree[curNode].empty()
        || (tree[curNode].size() == 1 && tree[curNode][0] == trgt)){
        ++cnt;  // 리프 노드 추가
    }

    vector<int>::iterator child;
    for(child = tree[curNode].begin(); child != tree[curNode].end(); ++child){
        if(*child != trgt && !isVisited[*child]){ // 지운 노드가 아닌 경우
            isVisited[*child] = true;
            dfs_recursive(*child);
        }
    }
}

void solve(){
    if(root == trgt){
        return;
    }
    // dfs();
    dfs_recursive(root);
}

int main() {
    init();
    solve();
    cout<<cnt;
    return 0;
}