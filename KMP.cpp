#include <string>
#include <vector>
using namespace std;

vector<int> buildNext(string &pattern) {
    // next[i] 表示 pattern[0...i] 的最长相等前后缀的长度
    int m = (int)pattern.size();
    vector<int> next(m, 0);
    if(m == 0) return next;
    for(int i = 1, j = 0; i < m; i++) {             // j 代表长度，也代表下一位待匹配字符的位置
        while(j > 0 && pattern[i] != pattern[j]) {  // j = 0 不能再回退了
            j = next[j - 1];
        }
        if(pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

vector<int> KMP(string &text, string &pattern) {
    vector<int> res;
    if(pattern.empty()) {
        return res;
    }
    if(text.empty()) {
        return res;
    }
    vector<int> next = buildNext(pattern);
    int n = (int)text.size();
    int m = (int)pattern.size();
    for(int i = 0, j = 0; i < n; i++) {
        while(j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if(text[i] == pattern[j]) {
            j++;
        }
        if(j == m) {
            res.push_back(i - m + 1);  // 找到一个匹配
            j = next[j - 1];           // 继续寻找下一个匹配
        }
    }
    return res;
}