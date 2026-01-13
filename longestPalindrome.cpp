#include <cmath>
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    string longestPalindrome(const string& s) {
        int n = (int)s.size();
        if(n < 2) return s;
        string res;
        for(int i = 0; i < n; ++i) {
            // 奇数中心
            string s1 = expand(s, i, i);
            if(res.size() < s1.size()) res = std::move(s1);

            // 偶数中心（边界优化：先判断 i+1 是否有效）
            if(i + 1 < n) {
                string s2 = expand(s, i, i + 1);
                if(res.size() < s2.size()) res = std::move(s2);
            }
        }
        return res;
    }

private:
    static string expand(const string& s, int left, int right) {
        while(left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        // 退出时 left/right 各多走了一步，截取 [left+1, right)
        string temp = s.substr(left + 1, right - left - 1);
        return temp;
    }
};

int main() {
    Solution solution;
    string input = "babad";
    string result = solution.longestPalindrome(input);
    // 输出结果
    cout << "Longest Palindromic Substring: " << result << endl;
    // 预期输出: "bab" 或 "aba"
    return 0;
}
