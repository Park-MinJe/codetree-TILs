#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int n, cntMax = 0;
unordered_map<string, int> map;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        string tmp;
        cin>>tmp;
        
        if(map.find(tmp) != map.end()){
            ++map[tmp];
        }
        else{
            map[tmp] = 1;
        }

        if(cntMax < map[tmp]){
            cntMax = map[tmp];
        }
    }

    printf("%d", cntMax);
    return 0;
}