#include <iostream>
#include <vector>
#include <queue>
#define MAX_NODE 1001

using namespace std;

int n, m, result;
int isVisited[MAX_NODE];
vector<int> arc[MAX_NODE];

void bfs(){
    queue<int> q;
    q.push(1);
    isVisited[1] = true;
    result = 0;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        
        vector<int>::iterator it;
        for(it = arc[x].begin(); it != arc[x].end(); ++it){
            if(!isVisited[*it]){
                q.push(*it);
                result++;
                isVisited[*it] = true;
            }
        }
    }

    printf("%d", result);
}

int main() {
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; ++i){
        isVisited[i] = false;
    }

    int tmpX, tmpY;
    for(int i = 1; i <= m; ++i){
        scanf("%d %d", &tmpX, &tmpY);
        arc[tmpX].push_back(tmpY);
        arc[tmpY].push_back(tmpX);
    }

    bfs();

    return 0;
}