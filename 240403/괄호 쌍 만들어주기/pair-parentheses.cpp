#include <iostream>
#include <string>

#define MAX_LEN 100001

using namespace std;

string str;
int open = 0,
    close = 0;

int getnC2(int n){
    return n * (n-1) / 2;
}

int main() {
    cin>>str;
    int strLen = str.size();
    for(int i = 0; i < strLen-1; ++i){
        if(str[i] == '(' && str[i+1] == '('){
            ++open;
        }
        if(str[i] == ')' && str[i+1] == ')'){
            ++close;
        }
    }
    cout<<open * close;
    return 0;
}