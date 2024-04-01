#include <iostream>
#include <unordered_map>

using namespace std;

int n, sum = 0;
unordered_map<long long, long long> map;

int main() {
    cin>>n;
    long long x, y;
    for(int i = 0; i < n; ++i){
        cin>>x>>y;
        if(map.find(x) == map.end()){   // 없음
            map[x] = y;
            sum += y;
        }
        else{
            if(map[x] > y){
                sum = sum - map[x] + y;
                map[x] = y;
            }
        }
    }
    cout<<sum;
    return 0;
}