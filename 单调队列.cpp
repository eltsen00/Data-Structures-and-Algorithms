// 单调队列可以用来解决滑动窗口中的最大值/最小值问题，因为窗口的长度可以直接通过right - left + 1计算得出，而最大值/最小值不行，所以要通过单调队列的队首元素直接获得。
#include<deque>
#include<vector>
#include<stdexcept>
using namespace std;

// 单调队列的通用实现，可以高效维护最大值和最小值,相较于普通队列，增加了快速获取最大值和最小值的功能
template <typename E>
class MonotonicQueue {
private:
    deque<E> data;      // 存储队列中的所有元素
    deque<E> maxData;   // 存储当前队列中的最大值，单调递减
    deque<E> minData;   // 存储当前队列中的最小值，单调递增
public:
    // 标准队列 API，向队尾加入元素
    void push(E elem){
        data.push_back(elem);
        // 更新最大值队列
        while (!maxData.empty() && maxData.back() < elem) {
            maxData.pop_back();
        }
        maxData.push_back(elem);
        // 更新最小值队列
        while (!minData.empty() && minData.back() > elem) {
            minData.pop_back();
        }
        minData.push_back(elem);
    }

    // 标准队列 API，从队头弹出元素，符合先进先出的顺序
    E pop(){
        if (data.empty()) {
            throw runtime_error("Queue is empty");
        }
        E front = data.front();
        data.pop_front();
        // 更新最大值队列
        if (front == maxData.front()) {
            maxData.pop_front();
        }
        // 更新最小值队列
        if (front == minData.front()) {
            minData.pop_front();
        }
        return front;
    }

    E front(){
        if (data.empty()) {
            throw runtime_error("Queue is empty");
        }
        return data.front();
    }

    E back(){
        if (data.empty()) {
            throw runtime_error("Queue is empty");
        }
        return data.back();
    }

    // 标准队列 API，返回队列中的元素个数
    int size(){
        return data.size();
    }

    // 单调队列特有 API，O(1) 时间计算队列中元素的最大值
    E max(){
        if (maxData.empty()) {
            throw runtime_error("Queue is empty");
        }
        return maxData.front();
    }

    // 单调队列特有 API，O(1) 时间计算队列中元素的最小值
    E min(){
        if (minData.empty()) {
            throw runtime_error("Queue is empty");
        }
        return minData.front();
    }
};

// 单调队列的另外一种实现方式，直接在滑动窗口问题中使用索引来维护单调队列
// 它不关心离开窗口的那个值到底是多少。
// 它只关心时间（也就是索引 i），因为时间一旦过去了，这个值就永远不会再回来了。
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> window;
    vector<int> res;
    for(int i=0;i<nums.size();i++){
        // 淘汰过期元素
        while(!window.empty()&&window.front()<=i-k){
            window.pop_front();
        }
        // 入队前，保持单调递减
        while(!window.empty()&&nums[window.back()]<nums[i]){
            window.pop_back();
        }
        // 入队
        window.push_back(i);
        // 符合条件时，输出当前窗口的最大值
        if(i>=k-1){
            res.push_back(nums[window.front()]);
        }
    }
    return res;
}
