#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;

//贪心算法，利用单调栈（递减）

string removeKdigits(string num, int k){
    if(k==num.length()) return "0";
    stack<char> s;
    for(int i=0;i<num.size();i++){
        while(!s.empty()&&k>0&&s.top()>num[i]){
            s.pop();
            k--;
        }
        s.push(num[i]);
    }
    while(k>0){
        s.pop();
        k--;
    }
    string result;
    while(!s.empty()){
        result.push_back(s.top());
        s.pop();
    }
    reverse(result.begin(),result.end());
    int start=0;
    while(start<result.length()&&result[start]=='0'){
        start++;
    }
    return start==result.size()?"0":result.substr(start);
}