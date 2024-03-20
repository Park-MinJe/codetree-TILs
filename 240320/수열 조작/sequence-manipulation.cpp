#include <iostream>
#include <deque>

using namespace std;

int N;

int main() {
    deque<int> dq;
    scanf("%d", &N);
    for(int i = 1; i <=N; ++i){
        dq.push_back(i);
    }
    while(dq.size() > 1){
        dq.pop_front();
        int tmp = dq.front();
        dq.pop_front();
        dq.push_back(tmp);
    }
    printf("%d", dq.front());
    return 0;
}