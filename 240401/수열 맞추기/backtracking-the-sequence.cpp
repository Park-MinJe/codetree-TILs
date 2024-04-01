#include <iostream>
#include <deque>
#define MAX_N 200001

using namespace std;

int n, a[MAX_N], tmpIn;
deque<int> dq;

int main() {
    cin>>n;
    for(int i = n; i > 0; --i){
        cin>>a[i];
    }

    for(int i = 1; i <= n; ++i){
        int tmp;
        switch(a[i]){
        case 1:
            dq.push_front(i);
            break;
        case 2:
            tmp = dq.front();
            dq.pop_front();
            dq.push_front(i);
            dq.push_front(tmp);
            break;
        case 3:
            dq.push_back(i);
            break;
        }
    }
    
    while(!dq.empty()){
        cout<<dq.front()<<" ";
        dq.pop_front();
    }

    return 0;
}