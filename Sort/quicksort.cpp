#include <vector>
#include <algorithm>
#include <iterator>

template <typename Iterator>
void modern_quicksort(Iterator begin, Iterator end) {
    if(begin == end || std::distance(begin, end) < 2) return;
    auto distance = std::distance(begin, end);
    auto pivot = *next(begin, distance / 2);
    Iterator middle1 = std::partition(begin, end, [pivot](const auto& em) { return em < pivot; });
    Iterator middle2 = std::partition(middle1, end, [pivot](const auto& em) { return !(pivot < em); });
    modern_quicksort(begin, middle1);
    modern_quicksort(middle2, end);
}

int partition(std::vector<int>& arr, int low, int high){
    int ramdomIndex = low + rand() % (high - low + 1);
    int pivot = arr[ramdomIndex];
    std::swap(arr[ramdomIndex], arr[low]);
    // mark 指向小于 pivot 的最后一个元素的位置
    // 初始时，小于区域为空，所以 mark = low
    int mark = low;
    for(int i = low + 1; i <= high; i++){
        if(arr[i] < pivot){
            mark++; // 扩大小于 pivot 的区域
            std::swap(arr[mark], arr[i]); // 将当前小于 pivot 的元素交换到 mark 位置
        }
    }
    
    // 最后将 pivot (在 arr[low]) 放到中间正确的位置 (arr[mark])
    std::swap(arr[low], arr[mark]);
    return mark;
}

void quicksort(std::vector<int>& arr, int low, int high){
    if(low < high){
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}
