#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int n, tmp;
string cmd;
unordered_set<int> set;
vector<string> result;

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>cmd>>tmp;
        if(cmd.compare("add") == 0){
            if(set.find(tmp) == set.end())
                set.insert(tmp);
        }
        else if(cmd.compare("remove") == 0){
            set.erase(tmp);
        }
        else if(cmd.compare("find") == 0){
            if(set.find(tmp) != set.end())
                result.push_back("true\n");
            else
                result.push_back("false\n");
        }
    }
    
    vector<string>::iterator it;
    for(it = result.begin(); it != result.end(); ++it){
        cout<<*it;
    }

    return 0;
}