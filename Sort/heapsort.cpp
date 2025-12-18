#include <vector>
#include <algorithm>

void sink(std::vector<int>& arr, int n, int index){
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n &&  arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != index){
        std::swap(arr[index], arr[largest]);
        // 递归：交换后，被交换下去的那个位置（largest）可能破坏了子树的堆性质
        // 所以要继续对那个位置进行 heapify
        sink(arr, n, largest);
    }
}

void heapsort(std::vector<int>& arr){
    int n = (int)arr.size();
    // 从“最后一个非叶子节点”开始，自底向上进行 heapify
    // 最后一个节点的索引是 n-1，其父节点索引是 (n-1-1)/2 = n/2 - 1
    for(int i = n / 2 - 1; i >= 0; i--){
        sink(arr, n, i);
    }
    for(int i = n - 1; i > 0; i--){
        std::swap(arr[0], arr[i]);
        sink(arr, i, 0);
    }
}