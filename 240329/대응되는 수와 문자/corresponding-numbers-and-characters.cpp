#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

int n, m;
unordered_map<string, string> map;
queue<string> result;

int main() {
    string tmp;

    cin>>n>>m;
    for(int i = 1; i <= n; ++i){
        cin>>tmp;
        map[tmp] = to_string(i);
        map[to_string(i)] = tmp;
    }
    for(int i = 0; i < m; ++i){
        cin>>tmp;
        result.push(map[tmp]);
    }
    while(!result.empty()){
        cout<<result.front()+"\n";
        result.pop();
    }
    return 0;
}