#include <iostream>
#include <string>

#define MAX_LEN 100001

using namespace std;

string str;
int open = 0,
    close = 0,
    R[MAX_LEN],
    ans = 0;

int getnC2(int n){
    return n * (n-1) / 2;
}

int main() {
    cin>>str;
    int strLen = str.size();
    for(int i = strLen-3; i >= 1; --i){
        if(str[i+1] == ')' && str[i+2] == ')'){
            R[i] = R[i+1] + 1;
        }
        else{
            R[i] = R[i+1];
        }
    }
    for(int i = 1; i < strLen-2; ++i){
        if(str[i-1] == '(' && str[i] == '('){
            ans += R[i];
        }
    }
    cout<<ans;
    return 0;
}