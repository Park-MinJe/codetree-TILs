#include <iostream>
#include <vector>
#include <queue>
#define MAX_NODE 1001

using namespace std;

int n, m,
    result = 0;
vector<int> arch[MAX_NODE];
bool isVisitied[MAX_NODE];

void dfs(){
    queue<int> q;
    q.push(1);
    isVisitied[1] = true;
    while(!q.empty()){
        int curN = q.front();
        //printf("%d\n", curN);
        q.pop();

        vector<int>::iterator it;
        for(it = arch[curN].begin(); it != arch[curN].end(); ++it){
            if(!isVisitied[*it]){
                q.push(*it);
                isVisitied[*it] = true;
                ++result;
            }
        }
    }

    printf("%d", result);
}

int main() {
    int x, y;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i){
        isVisitied[i] = false;
    }
    for(int i = 0; i < m; ++i){
        scanf(" %d %d", &x, &y);
        arch[x].push_back(y);
        arch[y].push_back(x);
    }

    dfs();
    
    return 0;
}