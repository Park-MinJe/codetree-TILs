#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

#define MAX_N 10001

using namespace std;

int n, s, e, v,
    max_dist = 0,
    last_node,
    dist[MAX_N];
unordered_map<int, vector<pair<int, int>>> map;    // <s, <e, v>>
bool isVisited[MAX_N];

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>s>>e>>v;
        map[s].push_back(
            make_pair(e, v)
        );
        map[e].push_back(
            make_pair(s, v)
        );
    }
}

void dfs(int start){
    for(int i = 0; i < map[start].size(); ++i){
        tie(e, v) = map[start][i];

        if(isVisited[e]) continue;

        isVisited[e] = true;
        dist[e] = dist[start] + v;

        if(dist[e] > max_dist){
            max_dist = dist[e];
            last_node = e;
        }

        dfs(e);
    }
}

void solve(){
    isVisited[1] = true;
    dfs(1);

    for(int i = 1; i <= n; ++i){
        isVisited[i] = false;
        dist[i] = 0;
    }

    isVisited[last_node] = true;
    dfs(last_node);
}

int main() {
    init();
    solve();
    cout<<max_dist;
    return 0;
}