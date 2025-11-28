#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        // key 是左括号的索引，value 是对应的右括号的索引
        unordered_map<int, int> rightIndex;
        // 利用栈结构来找到对应的括号（后进先出），存储左括号的索引
        stack<int> stack;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stack.push(i);
            } else if (s[i] == ')') {
                rightIndex[stack.top()] = i;
                stack.pop();
            }
        }
        if(stack.size() != 0) return 0; //括号不匹配
        return _calculate(s, 0, s.length() - 1, rightIndex);
    }

private:
    // 定义：返回 s[start..end] 内的表达式的计算结果
    int _calculate(const string& s, int start, int end, unordered_map<int, int> &rightIndex) {
        //储存数字的栈
        stack<int> stk;
        // 记录算式中的数字
        int num = 0;
        // 记录 num 前的符号，初始化为 +
        char sign = '+';
        for (int i = start; i <= end; i++) {
            char c = s[i];
            if (isdigit(c)) {
                num = 10 * num + (c - '0');
            }
            //找到左括号的时候，能直接通过 rightIndex 找到对应的右括号
            if (c == '(') {
                // 递归计算括号内的表达式
                num = _calculate(s, i + 1, rightIndex[i] - 1, rightIndex); //将括号视为一个数，递归计算
                i = rightIndex[i];
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || i == end) {
                int pre;
                switch (sign) {
                    case '+':
                        stk.push(num);
                        break;
                    case '-':
                        stk.push(-num);
                        break;
                    // 只要拿出前一个数字做对应运算即可
                    case '*':
                        pre = stk.top(); stk.pop();
                        stk.push(pre * num);
                        break;
                    case '/':
                        pre = stk.top(); stk.pop();
                        stk.push(pre / num);
                        break;
                }
                // 更新符号为当前符号，数字清零
                sign = c;
                num = 0;
            }
        }
        // 将栈中所有结果求和就是答案
        int res = 0;
        while (!stk.empty()) {
            res += stk.top();
            stk.pop();
        }
        return res;
    }
};

int main() {
    Solution sol;
    string s = "(1+(4+5+2)-3)+(6+8)";
    int result = sol.calculate(s);
    return 0;
}