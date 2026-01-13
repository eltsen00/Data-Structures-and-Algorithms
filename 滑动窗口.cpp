#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;
// 滑动窗口算法，难点在于判断收缩条件，更新结果。扩大窗口与收缩窗口进行的窗口数据的更新对称
string minWindow(const string& s, const string& t) {
    unordered_map<char, int> need, window; // 记录需要的字符及其出现次数，窗口中字符及其出现次数
    // 统计need数据
    for(const char& c : t) {
        need[c]++;
    }
    // 进行初始数据准备
    int left = 0, right = 0;
    // 记录window中的字符满足need条件的字符个数
    int valid = 0;
    // 记录最小覆盖子串的起始索引及长度
    int start = 0, len = (int)s.size();

    while(right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 扩大窗口
        right++;
        // 进行窗口内数据的一系列更新
        if(need.count(c)) {
            window[c]++;
            if(window[c] == need[c]) valid++;
        }

        // 判断左侧窗口是否要收缩
        while(valid == need.size()) {
            // 在这里更新最小覆盖子串
            if(right - left < len) {
                start = left;
                len = right - left;
            }
            // d 是将移出窗口的字符
            char d = s[left];
            // 缩小窗口
            left++;
            // 进行窗口内数据的一系列更新
            if(need.count(d)) {
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    // 返回最小覆盖子串
    return len == INT_MAX ? "" : s.substr(start, len);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string result = minWindow(s, t);
    cout << "Minimum window substring: " << result << endl;
    return 0;
}

/*
// 滑动窗口算法伪码框架
void slidingWindow(string s) {
    // 用合适的数据结构记录窗口中的数据，根据具体场景变通
    // 比如说，我想记录窗口中元素出现的次数，就用 map
    // 如果我想记录窗口中的元素和，就可以只用一个 int
    auto window = ...

    int left = 0, right = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        window.add(c);
        // 增大窗口
        right++;

        // 进行窗口内数据的一系列更新
        ...

        // *** debug 输出的位置 ***
        printf("window: [%d, %d)\n", left, right);
        // 注意在最终的解法代码中不要 print
        // 因为 IO 操作很耗时，可能导致超时

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            window.remove(d);
            // 缩小窗口
            left++;

            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
*/