#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

// 解法一：使用二分搜索二分答案，枚举给定长度的子串，用哈希集合储存校验子串是否重复出现O(n^2logn)
bool check(const string& s, int len) {
    if(len == 0) return true; // 空串视为重复
    if(len>s.size()) return false; // 长度超过字符串长度不可能重复
    unordered_set<string> seen; // 用于存储已见过的子串
    // 枚举所有长度为len的子串
    for (int i = 0; i + len <= s.size(); i++) {
        string sub = s.substr(i, len);
        if (seen.count(sub)){
            return true;
        }
        else{
            seen.insert(sub);
        }
    }
    return false;
}

int findTwinSubstring(const string& s) {
    int left = 1, right = s.size() - 1;
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(s, mid)) {
            result = mid; // 记录当前找到的最大长度
            left = mid + 1; // 尝试寻找更长的重复子串
        }
        else {
            right = mid - 1; // 搜索未果尝试寻找更短的重复子串
        }
    }
    return result;
}

// 解法二：暴力枚举所有子串，检查是否重复出现O(n^3)
int check(string &s){
    if(s.size()==1){
        return 0;
    }
    int max_len=0;
    // i 和 j 代表了两个不同后缀的起始位置：suffix[i] (即 s[i...]) 和 suffix[j] (即 s[j...])
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            int curLen=0;
            while(j+curLen<s.size() && s[i+curLen]==s[j+curLen]){
                curLen++;
            }
            max_len=max(max_len,curLen);
        }
    }
    return max_len;
}