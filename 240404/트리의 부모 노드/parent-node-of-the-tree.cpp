#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 100001

using namespace std;

int n, s, e;
vector<int> tree[MAX_N];   // 인접 리스트
bool isVisited[MAX_N];
int parents[MAX_N];

void init(){
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin>>s>>e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }
}

void dfs(){
    queue<int> q;
    q.push(1);
    isVisited[1] = true;

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        vector<int>::iterator childIt;
        for(childIt = tree[cur].begin(); childIt != tree[cur].end(); ++childIt){
            if(!isVisited[*childIt]){
                parents[*childIt] = cur;
                isVisited[*childIt] = true;
                q.push(*childIt);
            }
        }
    }
}

void solve(){
    dfs();
}

void printResult(){
    for(int i = 2; i <= n; ++i){
        printf("%d\n", parents[i]);
    }
}

int main() {
    init();
    solve();
    printResult();
    return 0;
}