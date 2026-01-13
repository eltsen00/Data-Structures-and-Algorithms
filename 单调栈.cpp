//主要用于解决“下一个更大元素 (Next Greater Element)”或“下一个更小元素 (Next Smaller Element)”这类问题
/*对单调栈的理解：
    单调 (Monotonic)：它指的是栈内从*栈底到栈顶*的元素，始终保持着单调递增或单调递减的顺序。
    单调栈的核心思想是：通过“破坏”单调性来找到答案。
        为了维持栈的单调性，当一个新元素准备入栈时，我们需要进行一个特殊的检查：对于单调递增栈 (Next Smaller Element)，不断地将栈顶元素弹出，直到栈顶元素小于 x（或者栈为空）。然后，再将新元素 x 压入栈中。对于单调递减栈 (Next Greater Element)，不断地将栈顶元素弹出，直到栈顶元素大于 x（或者栈为空）。然后，再将新元素 x 压入栈中。
    关键点：元素被弹出的那一刻，就是我们找到答案的时刻！ 那个导致它被弹出的新元素，通常就是它在某个方向上（左或右）第一个满足特定条件（更大或更小）的元素。（在元素被弹出时得到答案，赋值）*/
#include<bits/stdc++.h>
using namespace std;

vector<int> calculateGreaterElement(vector<int>& nums) {
    int n = (int)nums.size();
    // 存放答案的数组
    vector<int> res(n,-1);
    stack<int> s; 
    for(int i=0;i<nums.size();i++){
        // 维护一个单调递减栈
        while(!s.empty() && nums[s.top()]<nums[i]){ //元素被弹出的一刻，就是我们找到答案的时刻
            int topIndex = s.top(); // 取出栈顶索引
            s.pop(); // 弹出
            res[topIndex] = nums[i]; // 记录结果
        }
        s.push(i); // 将当前元素的索引入栈
    }
    return res;
}

int main() {
    vector<int> nums = {2, 1, 2, 4, 3};
    vector<int> result = calculateGreaterElement(nums);
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}