#include <iostream>
#include <deque>
#include <string>
#include <vector>

#define MAX_N 10001

using namespace std;

int n;
vector<int> result;

int main() {
    deque<int> dq;

    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        string cmd;
        int arg;
        cin>>cmd;
        if(cmd.compare("push_back") == 0){
            scanf("%d", &arg);
            dq.push_back(arg);
        }
        else if(cmd.compare("push_front") == 0){
            scanf("%d", &arg);
            dq.push_front(arg);
        }
        else if(cmd.compare("pop_front") == 0){
            result.push_back(dq.front());
            dq.pop_front();
        }
        else if(cmd.compare("pop_back") == 0){
            result.push_back(dq.back());
            dq.pop_back();
        }
        else if(cmd.compare("size") == 0){
            result.push_back(dq.size());
        }
        else if(cmd.compare("empty")== 0){
            if(dq.empty()){
                result.push_back(1);
            }
            else{
                result.push_back(0);
            }
        }
        else if(cmd.compare("front") == 0){
            result.push_back(dq.front());
        }
        else if(cmd.compare("back") == 0){
            result.push_back(dq.back());
        }
    }

    vector<int>::iterator it;
    for(it = result.begin(); it != result.end(); ++it){
        printf("%d\n", *it);
    }

    return 0;
}