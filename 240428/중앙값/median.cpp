#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int T, sum, i;
double avg;
queue<queue<int>> answers;

int main() {
    cin>>T;

    for(int t = 0; t < T; ++t){
        sum = 0; avg = 0;

        int m;
        cin>>m;

        vector<int> v(m+1);
        int middian;
        priority_queue<int, vector<int>, greater<int>> biggerPq;
        priority_queue<int, vector<int>, less<int>> smallerPq;
        queue<int> answer;
        for(i = 1; i <= m; ++i){
            cin>>v[i];
            sum += v[i];
            avg = sum / (double)i;

            if(i == 1){
                middian = v[i];
            }
            else{
                if(v[i] >= middian) biggerPq.push(v[i]);
                else smallerPq.push(v[i]);
            }

            if(i % 2 == 1){
                // 홀수
                if(biggerPq.size() > smallerPq.size()){
                    smallerPq.push(middian);
                    middian = biggerPq.top();
                    biggerPq.pop();
                }
                else if(biggerPq.size() < smallerPq.size()){
                    biggerPq.push(middian);
                    middian = smallerPq.top();
                    smallerPq.pop();
                }

                answer.push(middian);
            }
        }
        
        answers.push(answer);
    }

    while(!answers.empty()){
        queue<int>& curQ = answers.front();

        while(!curQ.empty()){
            cout<<curQ.front()<<" ";
            curQ.pop();
        }
        cout<<"\n";
        
        answers.pop();
    }

    return 0;
}