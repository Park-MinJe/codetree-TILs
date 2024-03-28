#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

int n;  // 명령 수
unordered_map<string, string> map;
queue<string> result;

void init(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        string cmd, arg1, arg2;
        cin >> cmd;

        if(cmd.compare("add") == 0){
            cin>>arg1>>arg2;
            map[arg1] = arg2;
        }
        else if(cmd.compare("remove") == 0){
            cin>>arg1;
            map.erase(arg1);
        }
        else if(cmd.compare("find") == 0){
            cin>>arg1;
            if(map.find(arg1) != map.end()){
                result.push(map[arg1]);
            }
            else{
                result.push("None");
            }
        }
    }
}

void printResult(){
    while(!result.empty()){
        cout<<result.front()<<"\n";
        result.pop();
    }
}

int main() {
    init();
    printResult();
    return 0;
}