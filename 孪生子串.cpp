#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std;

// 解法一：使用二分搜索二分答案，枚举给定长度的子串，用哈希集合储存校验子串是否重复出现O(nlogn)
// 利用哈希滚动算法减少空间复杂度
typedef unsigned long long ULL;
constexpr ULL BASE = 131;  // 哈希基数
vector<ULL> pow_base;      // 预计算 BASE 的幂次方
vector<ULL> prefix_hash;   // 前缀哈希数组

void init_hash(const string& s) {
    pow_base.resize(s.size() + 1, 1);
    prefix_hash.resize(s.size() + 1, 0);
    pow_base[0] = 1;
    for(int i = 1; i <= s.size(); i++) { //类似于P进制数的计算
        pow_base[i] = pow_base[i - 1] * BASE;
        prefix_hash[i] = prefix_hash[i - 1] * BASE + s[i - 1];
    }
}

inline ULL get_hash(int left, int right) {
    return prefix_hash[right + 1] - prefix_hash[left] * pow_base[right - left + 1];
}

bool check(const string& s, int len) {
    if(len == 0) return true;         // 空串视为重复
    if(len > s.size()) return false;  // 长度超过字符串长度不可能重复
    unordered_set<ULL> seen;          // 用于存储已见过的子串
    // 枚举所有长度为len的子串
    for(int i = 0; i + len <= s.size(); i++) {
        ULL sub = get_hash(i, i + len - 1);
        if(seen.count(sub)) {
            return true;
        }
        else {
            seen.insert(sub);
        }
    }
    return false;
}

int findTwinSubstring(const string& s) {
    int left = 1, right = (int)s.size() - 1;
    int result = 0;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(check(s, mid)) {
            result = mid;    // 记录当前找到的最大长度
            left = mid + 1;  // 尝试寻找更长的重复子串
        }
        else {
            right = mid - 1;  // 搜索未果尝试寻找更短的重复子串
        }
    }
    return result;
}

// 解法二：暴力枚举所有子串，检查是否重复出现O(n^3)
int check(string& s) {
    if(s.size() == 1) {
        return 0;
    }
    int max_len = 0;
    // i 和 j 代表了两个不同后缀的起始位置：suffix[i] (即 s[i...]) 和 suffix[j] (即 s[j...])
    for(int i = 0; i < s.size(); i++) {
        for(int j = i + 1; j < s.size(); j++) {
            int curLen = 0;
            while(j + curLen < s.size() && s[i + curLen] == s[j + curLen]) {
                curLen++;
            }
            max_len = max(max_len, curLen);
        }
    }
    return max_len;
}