#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

#define MAX_NM 1001

using namespace std;

int n, m,
    p, c, w,
    s, e;

bool isVisited[MAX_NM];

vector<pair<int, int>> vertexes[MAX_NM];  // <node, w>
vector<pair<int, int>> toParent[MAX_NM];  // <parent, w>
vector<pair<int, int>> toChild[MAX_NM];  // <child, w>
vector<pair<int, int>> trgts;   // <s, e>
vector<int> results;

void init(){
    cin>>n>>m;
    for(int i = 0; i < n-1; ++i){
        cin>>c>>p>>w;

        // vertexes[p].push_back(
        //     make_pair(c, w)
        // );
        // vertexes[c].push_back(
        //     make_pair(p, w)
        // );

        toChild[p].push_back(
            make_pair(c, w)
        );
        toParent[c].push_back(
            make_pair(p, w)
        );
    }

    for(int i = 0; i < m; ++i){
        cin>>s>>e;
        trgts.push_back(
            make_pair(s, e)
        );
    }
}

void dfs(int trgt, int cur, int dist){
    if(!isVisited[cur]){
        isVisited[cur] = true;
        //debug
        // printf("cur = %d\n", cur);

        if(cur == trgt){    // 목표 노드 찾음
            results.push_back(dist);
            return;
        }

        // vector<pair<int, int>>::iterator itVertex;
        // for(itVertex = vertexes[cur].begin(); itVertex != vertexes[cur].end(); ++itVertex){
        //     if(!isVisited[itVertex->first]){
        //         dfs(
        //             trgt,
        //             itVertex->first,
        //             dist + itVertex->second
        //         );
        //     }
        // }

        vector<pair<int, int>>::iterator itChild;
        for(itChild = toChild[cur].begin(); itChild != toChild[cur].end(); ++itChild){
            if(!isVisited[itChild->first]){
                dfs(
                    trgt,
                    itChild->first,
                    dist + itChild->second
                );
            }
        }
        vector<pair<int, int>>::iterator itParent;
        for(itParent = toParent[cur].begin(); itParent != toParent[cur].end(); ++itParent){
            if(!isVisited[itParent->first]){
                dfs(
                    trgt,
                    itParent->first,
                    dist + itParent->second
                );
            }
        }
    }
}

void solve(){
    for(int i = 0; i < m; ++i){
        for(int i = 1; i <= n; ++i)
            isVisited[i] = false;

        tie(s, e) = trgts[i];
        // printf("\n(s, e)::(%d, %d)\n", s, e);
        dfs(e, s, 0);
        printf("%d\n", results[i]);
    }
}

int main() {
    init();
    solve();
    return 0;
}