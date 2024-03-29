#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

int n, m;
unordered_map<string, string> mapByStr;
unordered_map<string, string> mapByInt;
queue<string> result;

int main() {
    string tmp;

    cin>>n>>m;
    for(int i = 1; i <= n; ++i){
        cin>>tmp;
        mapByStr[tmp] = to_string(i);
        mapByInt[to_string(i)] = tmp;
    }
    for(int i = 0; i < m; ++i){
        cin>>tmp;
        if("1"<=tmp && tmp<=to_string(n)){
            result.push(mapByInt[tmp]);
        }
        else{
            result.push(mapByStr[tmp]);
        }
    }
    while(!result.empty()){
        cout<<result.front()+"\n";
        result.pop();
    }
    return 0;
}