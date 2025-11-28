//前缀和数组只能实现动态查询，不能实现动态修改。对于希望对整个区间进行查询，同时支持动态修改元素的场景，是线段树结构的应用场景。
//线段树是一棵完全二叉树，叶子节点存储数组的元素值，非叶子节点存储其子节点的区间信息（如区间和、区间最大值等）。在修改元素时，只需更新对应的叶子节点，并递归更新其父节点，确保区间信息的正确性。线段树的时间复杂度均为O(log n)，适用于需要频繁进行区间查询和修改的场景。

//链式线段树是一种基于链表实现的线段树，在插入和删除操作时更加灵活，能够更好地应对元素的动态变化。
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

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

class SegmentTree {
private:
    SegmentNode* root;
    function<int(int, int)> merger;
    // 构建线段树,将 nums[l..r] 中的元素构建成线段树，返回根节点
    SegmentNode* build(const vector<int>& arr, int l, int r) {
        // 区间内只有一个元素，直接返回叶子节点
        if (l == r) {
            return new SegmentNode(arr[l], l, r);
        }
        // 从中间切分，递归构建左右子树
        int mid = l + (r - l) / 2;
        SegmentNode* node = new SegmentNode();
        node->l = l;
        node->r = r;
        node->left = build(arr, l, mid);
        node->right = build(arr, mid + 1, r); //使用mid + 1的原因是因为mid已经被左子树使用了
        // 计算当前节点的聚合值
        node->mergeVal = merger(node->left->mergeVal, node->right->mergeVal);
        return node;
    }

    void _update(SegmentNode* node, int index, int val) {
        // 找到叶子节点，更新值
        if (node->l == node->r) {
            node->mergeVal = val;
            return;
        }
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
    SegmentTree(const vector<int>& arr, function<int(int, int)> merger) {
        if (arr.empty()) {
            root = nullptr;
            return;
        }
        this->merger = merger;
        root = build(arr, 0, arr.size() - 1);
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

//数组实现线段树,数组储存线段树的merger值
//对于索引为 i 的节点，它的左子节点索引为 2 * i + 1，右子节点索引为 2 * i + 2
//数组元素个数为 n，那么存储线段树的数组容量应该初始化为 4×n，因为第五层的非空节点数估算为 n，但是包含空指针的话肯定就是 2n 了，则满二叉树的节点数为 4n - 1
class ArraySegmentTree {
private:
    vector<int> tree;
    int n; //元素个数
    function<int(int, int)> merger;

    int leftChild(int index) {
        return 2 * index + 1;
    }

    int rightChild(int index) {
        return 2 * index + 2;
    }

    // 对 nums[l..r] 区间的元素构建线段树，rootIndex 是根节点
    void build(const vector<int>& arr, int rootIndex, int l, int r) {
        if (l == r) {
            tree[rootIndex] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(rootIndex);
        int rightTreeIndex = rightChild(rootIndex);
        build(arr, leftTreeIndex, l, mid);
        build(arr, rightTreeIndex, mid + 1, r);
        tree[rootIndex] = merger(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    //以l，r指示当前节点表示的区间范围，index表示要更新的元素索引，val表示要更新的值
    void _update(int rootIndex, int l, int r, int index, int val) {
        if(l == r && rootIndex < tree.size() && l == index && rootIndex == index) {
            tree[index] = val;
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            // 若 index 较小，则去左子树更新
            _update(leftChild(rootIndex), l, mid, index, val);
        } else {
            // 若 index 较大，则去右子树更新
            _update(rightChild(rootIndex), mid + 1, r, index, val);
        }

        // 后序位置，左右子树已经更新完毕，更新当前节点的聚合值
        tree[rootIndex] = merger(tree[leftChild(rootIndex)], tree[rightChild(rootIndex)]);
    }

    //以l，r指示当前节点表示的区间范围，queryL，queryR表示要查询的区间范围
    int _query(int rootIndex, int l, int r, int queryL, int queryR){
        if(queryR < queryL){
            throw invalid_argument("Query range is invalid.");
        }
        if(l == queryL && r == queryR){
            return tree[rootIndex];
        }
        int mid = l + (r - l) / 2;
        int leftRootIndex = leftChild(rootIndex);
        int rightRootIndex = rightChild(rootIndex);
        if (queryR <= mid) {
            // node.l <= qL <= qR <= mid
            // 目标区间完全在左子树中
            return _query(leftRootIndex, l, mid, queryL, queryR);
        } else if (queryL > mid) {
            // mid < qL <= qR <= node.r
            // 目标区间完全在右子树中
            return _query(rightRootIndex, mid + 1, r, queryL, queryR);
        } else {
            // node.l <= qL <= mid < qR <= node.r
            // 目标区间横跨左右子树
            // 将查询区间拆分成 [qL, mid] 和 [mid + 1, qR] 两部分，分别向左右子树查询
            return merger(_query(leftRootIndex, l, mid, queryL, mid), _query(rightRootIndex, mid + 1, r, mid + 1, queryR));
        }
    }
public:
    ArraySegmentTree(const vector<int>& arr, function<int(int, int)> merger) {
        if (arr.empty()) {
            tree = {};
            n = 0;
            return;
        }
        this->merger = merger;
        n = arr.size();
        tree = vector<int>(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int index, int val) {
        if (index < 0 || index >= n) {
            throw out_of_range("Index is out of range.");
        }
        _update(0, 0, n - 1, index, val);
    }

    int query(int queryL, int queryR) {
        if (n == 0) {
            throw runtime_error("Segment tree is empty.");
        }
        if (queryL < 0 || queryR >= n) {
            throw out_of_range("Query range is out of range.");
        }
        return _query(0, 0, n - 1, queryL, queryR);
    }
};