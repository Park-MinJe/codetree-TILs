#include <iostream>
#include <string>
#include <stack>

using namespace std;

int cnt = 0;
string str;
stack<char> cStack;

int main() {
    cin>>str;
    for(int i = 0; i < str.size(); ++i){
        if(str[i] == '('){
            for(int j = i+1; j < str.size(); ++j){
                if(str[j] == ')'){
                    ++cnt;
                }
            }
        }
    }

    printf("%d", cnt);

    return 0;
}