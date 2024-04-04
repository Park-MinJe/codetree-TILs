#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>

#define MAX_N 10001

using namespace std;

int m, a, b;
unordered_map<int, vector<int>> vertex;  // 인접 리스트
unordered_map<int, int>
    indegrees,   // 들어오는 간선의 수
    outdegrees;  // 나가는 간선의 수

unordered_map<int, bool> isVisited;

bool compare(pair<int, int>& p1, pair<int, int>& p2){
    return p1.second < p2.second;
}

void init(){
    cin>>m;
    for(int i = 0; i < m; ++i){
        cin>>a>>b;
        vertex[a].push_back(b);

        if(indegrees.find(a) == indegrees.end()){
            indegrees[a] = 0;
        }
        if(outdegrees.find(b) == outdegrees.end()){
            outdegrees[b] = 0;
        }
        ++indegrees[b];
        ++outdegrees[a];
    }
}

void dfs(int curNode){
    if(!isVisited[curNode]){
        isVisited[curNode] = true;

        vector<int>::iterator it;
        for(it = vertex[curNode].begin(); it != vertex[curNode].end(); ++it){
            dfs(*it);
        }
    }
}

bool solve(){
    vector<pair<int, int>>
        inVec(indegrees.begin(), indegrees.end()),
        outVec(outdegrees.begin(), outdegrees.end());
    sort(inVec.begin(), inVec.end(), compare);
    sort(outVec.begin(), outVec.end(), compare);

    //debug
    // for(int i = 0; i < inVec.size(); ++i){
    //     printf("%d %d\n", inVec[i].first, inVec[i].second);
    // }

    if(inVec[0].second != 0 || inVec[1].second == 0){
        // debug
        // printf("first::%d %d / %d %d\n", inVec[0].first, inVec[0].second, inVec[1].first, inVec[1].second);
        // printf("%d %d\n", 7, indegrees[7]);
        return false;
    }
    
    vector<pair<int, int>>::iterator it;
    for(it = inVec.begin()+1; it != inVec.end(); ++it){
        if(it->second > 1){
            // debug
            // cout<<"second\n";
            return false;
        }
    }

    dfs(inVec[0].first);
    unordered_map<int, bool>::iterator itVisited;
    for(itVisited = isVisited.begin(); itVisited != isVisited.end(); ++itVisited){
        if(!itVisited->second){
            // debug
            // cout<<"third\n";
            return false;
        }
    }

    return true;
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