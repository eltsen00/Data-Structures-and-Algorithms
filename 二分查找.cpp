#include <bits/stdc++.h>
using namespace std;
// 二分查找的三种变体：
int binary_search(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < target) {
            left = mid + 1;
        }
        else if(nums[mid] > target) {
            right = mid - 1;
        }
        else if(nums[mid] == target) {
            // 直接返回
            return mid;
        }
    }
    // 直接返回
    return -1;
}

int left_bound(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < target) {
            left = mid + 1;
        }
        else if(nums[mid] > target) {
            right = mid - 1;
        }
        else if(nums[mid] == target) {
            // 别返回，锁定左侧边界
            right = mid - 1;
        }
    }
    // 判断 target 是否存在于 nums 中
    if(left < 0 || left >= nums.size()) {
        return -1;
    }
    // 判断一下 nums[left] 是不是 target
    return nums[left] == target ? left : -1;
}

int right_bound(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < target) {
            left = mid + 1;
        }
        else if(nums[mid] > target) {
            right = mid - 1;
        }
        else if(nums[mid] == target) {
            // 别返回，锁定右侧边界
            left = mid + 1;
        }
    }
    // 由于 while 的结束条件是 right == left - 1，且现在在求右边界, 所以用 right 替代 left - 1 更好记
    if(right < 0 || right >= nums.size()) {
        return -1;
    }
    return nums[right] == target ? right : -1;
}

int main() {
    vector<int> nums = {1, 2, 2, 3, 4, 5, 5, 5, 6};
    int target = 5;

    int index = binary_search(nums, target);
    cout << "Binary Search Index: " << index << endl;

    int leftIndex = left_bound(nums, target);
    cout << "Left Bound Index: " << leftIndex << endl;

    int rightIndex = right_bound(nums, target);
    cout << "Right Bound Index: " << rightIndex << endl;

    return 0;
}