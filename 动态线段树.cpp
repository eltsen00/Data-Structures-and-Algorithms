#include <iostream>
#include <vector>
#include <functional>
using namespace std;
//动态线段树，创建时无需输入数组，在需要更新的节点时才创建节点，解决了稀疏数据的内存优化问题
//适用于数据范围很大，但实际使用的节点较少的场景
class SegmentNode {
public:
    // 该节点表示的区间范围 [l, r]
    int l, r;
    // [l, r] 区间元素的聚合值（如区间和、区间最大值等）
    int mergeVal;
    SegmentNode* left;
    SegmentNode* right;
    SegmentNode() : l(0), r(0), mergeVal(0), left(nullptr), right(nullptr) {}
    SegmentNode(int mergeVal, int l, int r) : mergeVal(mergeVal), l(l), r(r), left(nullptr), right(nullptr) {}
};

class DynamicSegmentTree {
private:
    SegmentNode* root;
    function<int(int, int)> merger;
    int defaultValue;
    
    void initChildNodeIfNeeded(SegmentNode* node) {
        if(node->l == node->r) {
            return; // 叶子节点不需要子节点
        }
        int mid = node->l + (node->r - node->l) / 2;
        if(node->left == nullptr) {
            node->left = new SegmentNode(defaultValue, node->l, mid); // 初始化左子节点
        }
        if(node->right == nullptr) {
            node->right = new SegmentNode(defaultValue, mid + 1, node->r); // 初始化右子节点
        }
    }

    void _update(SegmentNode* node, int index, int val) {
        // 找到叶子节点，更新值
        if (node->l == node->r) {
            node->mergeVal = val;
            return;
        }
        initChildNodeIfNeeded(node); // 需要时初始化子节点
        // 二分查找叶子节点
        int mid = node->l + (node->r - node->l) / 2;
        if (index <= mid) {
             // 若 index 较小，则去左子树更新
            _update(node->left, index, val);
        } else {
            // 若 index 较大，则去右子树更新
            _update(node->right, index, val);
        }
        // 后序位置，左右子树已经更新完毕，更新当前节点的聚合值
        node->mergeVal = merger(node->left->mergeVal, node->right->mergeVal);
    }

    int _query(SegmentNode* node, int queryL, int queryR) {
        if(queryR < queryL) {
            throw invalid_argument("Query range is invalid.");
        }
        if(node->l == queryL && node->r == queryR) {
            // 找到对应区间，直接返回聚合值
            return node->mergeVal;
        }
        // 未命中目标，继续向下二分查找
        int mid = node->l + (node->r - node->l) / 2;
        if (queryR <= mid) {
            // 目标区间在左子树
            return _query(node->left, queryL, queryR);
        } else if (queryL >= mid + 1) {
            // 目标区间在右子树
            return _query(node->right, queryL, queryR);
        } else {
            // node.l <= qL <= mid < qR <= node.r
            // 目标区间横跨左右子树
            // 将查询区间拆分成 [qL, mid] 和 [mid + 1, qR] 两部分，分别向左右子树查询
            // 最后将左右子树的查询结果合并
            int leftPart = _query(node->left, queryL, mid);
            int rightPart = _query(node->right, mid + 1, queryR);
            return merger(leftPart, rightPart);
        }
    }
public:
    DynamicSegmentTree(int start, int end, function<int(int, int)> merger,int initialValue = 0):merger(merger),defaultValue(initialValue) {
        if (start > end) {
            throw invalid_argument("Invalid range for segment tree.");
        }
        root = new SegmentNode(initialValue, start, end);
    }

    void update(int index, int val) {
        if (index < 0 || index > root->r) {
            throw out_of_range("Index is out of range.");
        }
        _update(root, index, val);
    }

    int query(int queryL, int queryR) {
        if (root == nullptr) {
            throw runtime_error("Segment tree is empty.");
        }
        if (queryL < 0 || queryR > root->r) {
            throw out_of_range("Query range is out of range.");
        }
        return _query(root, queryL, queryR);
    }
};