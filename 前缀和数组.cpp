#include <vector>
using namespace std;
//一维前缀和
class NumArray {
    // 前缀和数组
    std::vector<int> preSum; // preSum[i] 记录数组 nums 在区间 [0, i-1] 的元素和

    // 输入一个数组，构造前缀和
    public:
    NumArray(std::vector<int>& nums) {
        // preSum[0] = 0，便于计算累加和
        preSum.resize(nums.size() + 1);
        // 计算 nums 的累加和
        for (int i = 1; i < preSum.size(); i++) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
    }

    // 查询闭区间 [left, right] 的累加和
    int sumRange(int left, int right) {
        return preSum[right + 1] - preSum[left];
    }
};

//二维前缀和
class NumMatrix {
    // preSum[i][j] 记录矩阵 [0, 0, i-1, j-1] 的元素和
    std::vector<std::vector<int>> preSum;

public:
    NumMatrix(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        if (m == 0 || n == 0) return;
        // 构造前缀和矩阵
        preSum.resize(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 计算每个矩阵 [0, 0, i, j] 的元素和
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] + matrix[i - 1][j - 1] - preSum[i-1][j-1];
            }
        }
    }
    
    // 计算子矩阵 [x1, y1, x2, y2] 的元素和
    int sumRegion(int x1, int y1, int x2, int y2) {
        // 目标矩阵之和由四个相邻矩阵运算获得
        return preSum[x2+1][y2+1] - preSum[x1][y2+1] - preSum[x2+1][y1] + preSum[x1][y1];
    }
};