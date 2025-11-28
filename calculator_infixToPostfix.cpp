#include <cctype>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
// 检查是否为运算符
bool isOperator(const string& op) {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "^";
}

// 返回运算符的优先级
int precedence(const string& op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    if (op == "^")
        return 3;
    return 0;
}

// 检查是否为函数
bool isFunction(const string& token) {
    static const map<string, function<double(double)>> funcs = {
        {"sin", [](double x) { return sin(x); }},
        {"cos", [](double x) { return cos(x); }},
        {"tan", [](double x) { return tan(x); }},
        {"sqrt", [](double x) { return sqrt(x); }}};
    return funcs.find(token) != funcs.end();
}

// 应用运算符或函数
double applyOperator(double a, double b, const string& op) {
    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/") {
        if (b == 0)
            throw runtime_error("Division by zero");
        return a / b;
    }
    if (op == "^")
        return pow(a, b);
    throw runtime_error("Unknown operator: " + op);
}

// 应用函数
double applyFunction(const string& func, double x) {
    if (func == "sin")
        return sin(x);
    if (func == "cos")
        return cos(x);
    if (func == "tan")
        return tan(x);
    if (func == "sqrt")
        return sqrt(x);
    throw runtime_error("Unknown function: " + func);
}

// 分词函数：将表达式分解为数字、标识符和运算符
vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string num, ident;
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c))
            continue;
        if (isdigit(c) || c == '.') {
            num.clear();
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                num.push_back(expr[i]);
                ++i;
            }
            tokens.push_back(num);
            --i;
        } else if (isalpha(c)) {
            ident.clear();
            while (i < expr.size() && isalpha(expr[i])) {
                ident.push_back(expr[i]);
                ++i;
            }
            tokens.push_back(ident);
            --i;
        } else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.push_back(string(1, c));
        } else {
            throw runtime_error(string("Invalid character: ") + c);
        }
    }
    return tokens;
}

// 中缀表达式转后缀表达式 (Shunting Yard 算法)
vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> ops;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const string& t = tokens[i];
        if (isdigit(t[0]) || (t.size() > 1 && isdigit(t[1]))) {
            output.push_back(t);
        } else if (isFunction(t)) {
            ops.push(t);
        } else if (isOperator(t)) {
            while (!ops.empty() && ((isOperator(ops.top()) &&
                                     ((precedence(ops.top()) > precedence(t)) ||
                                      (precedence(ops.top()) == precedence(t) && t != "^"))) ||
                                    isFunction(ops.top()))) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(t);
        } else if (t == "(") {
            ops.push(t);
        } else if (t == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty())
                throw runtime_error("Mismatched parentheses");
            ops.pop();
            if (!ops.empty() && isFunction(ops.top())) {
                output.push_back(ops.top());
                ops.pop();
            }
        }
    }
    while (!ops.empty()) {
        if (ops.top() == "(" || ops.top() == ")")
            throw runtime_error("Mismatched parentheses");
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

// 计算后缀表达式
double evaluatePostfix(const vector<string>& postfix) {
    stack<double> st;
    for (const auto& t : postfix) {
        if (isdigit(t[0]) || (t.size() > 1 && (isdigit(t[1]) || t[1] == '.'))) {
            st.push(stod(t));
        } else if (isOperator(t)) {
            if (st.size() < 2)
                throw runtime_error("Invalid expression");
            double b = st.top();
            st.pop();
            double a = st.top();
            st.pop();
            st.push(applyOperator(a, b, t));
        } else if (isFunction(t)) {
            if (st.empty())
                throw runtime_error("Invalid expression");
            double a = st.top();
            st.pop();
            st.push(applyFunction(t, a));
        } else {
            throw runtime_error("Unknown token: " + t);
        }
    }
    if (st.size() != 1)
        throw runtime_error("Invalid expression");
    return st.top();
}

// 计算表达式：支持连续计算和函数调用
double evaluateExpression(string expr, double lastResult) {
    // 支持连续计算：替换 ans 为上一次结果
    size_t pos;
    while ((pos = expr.find("ans")) != string::npos) {
        expr.replace(pos, 3, to_string(lastResult));
    }
    auto tokens = tokenize(expr);
    auto postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

int main() {
    cout << "Calculator v1.0. Type 'exit' to quit." << endl;
    double lastResult = 0;
    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line))
            break;
        if (line == "exit")
            break;
        if (line.empty())
            continue;
        try {
            double result = evaluateExpression(line, lastResult);
            cout << result << endl;
            lastResult = result;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}

// TODO: 预留图形化界面模块扩展 (GUI interface placeholder)
