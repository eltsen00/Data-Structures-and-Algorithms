#include<string>
#include<vector>
using namespace std;

vector<int> buildNext(string &pattern){
    // next[i] 表示 pattern[0...i-1] (长度为 i 的前缀) 的最长真前后缀长度
    // next[0] = -1 是为了方便编程处理
    int m = pattern.size();
    vector<int> next(m + 1);

    if (m == 0) return next;

    next[0] = -1;
    int i = 0, j = -1;

    while (i < m) {
        // j == -1 表示回退到了起点，或者当前字符匹配成功
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            // 此时 i 表示当前计算的是长度为 i 的前缀的 next 值
            // j 表示该前缀的最长真前后缀长度
            next[i] = j;
        }
        else {
            // 字符不匹配，j 回退
            j = next[j];
        }
    }
    return next;
}

vector<int> KMP(string &text, string &pattern) {
    vector<int> res;
    if(pattern.empty()){
        return res;
    }
    if(text.empty()){
        return res;
    }
    
    vector<int> next = buildNext(pattern);
    int i = 0, j = 0;
    int n = text.size();
    int m = pattern.size();

    while(i < n){
        // j == -1 (从 next[0] 传来) 或者字符匹配
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
            if(j == m){
                res.push_back(i - j);
                j = next[j]; // 继续寻找下一个匹配
            }
        }
        else{ 
            j = next[j]; // 失配，查表回退
        }
    }
    return res;
}