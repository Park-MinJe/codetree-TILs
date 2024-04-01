#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int n, k, cnt;
unordered_map<int, vector<int>> map;
unordered_map<int, bool> mapIsUsed;

int main() {
    cin>>n>>k;
    for(int i = 0; i < n; ++i){
        int tmp;
        cin>>tmp;
        map[tmp].push_back(i);
        mapIsUsed[tmp] = false;
    }
    
    unordered_map<int, vector<int>>::iterator it;
    for(it = map.begin(); it != map.end(); ++it){
        if(!mapIsUsed[it->first]){
            mapIsUsed[it->first] = true;
            int minus = k - it->first;
            if(minus != it->first){
                if(!mapIsUsed[minus]){
                    mapIsUsed[minus] = true;
                    cnt += it->second.size() * map[minus].size();
                }
                //cout<<minus<<" "<<cnt<<"\n";
            }
            else{
                int tmpSize = (it->second).size();
                cnt += tmpSize * (tmpSize-1) / 2;
            }
            
        }
    }

    cout<<cnt;
    
    return 0;
}