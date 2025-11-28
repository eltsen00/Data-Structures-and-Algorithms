#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class AllInOneSegmentTree {
    struct SegmentNode {
        int l, r;
        int mergeValue;
        SegmentNode* left;
        SegmentNode* right;

        // 累加懒标记, 为 0 表示无懒更新
        int lazyAdd;

        // 赋值懒标记
        int lazyAssign;
        bool hasLazyAssign;

        SegmentNode(int l, int r, int mergeValue) : l(l), r(r), mergeValue(mergeValue), left(nullptr), right(nullptr), lazyAdd(0), lazyAssign(0), hasLazyAssign(false) {}
    };

private:
    SegmentNode* root;
    int defaultValue;
    string type;

    // 查询闭区间 [qL, qR] 的聚合值
    int _query(SegmentNode* node, int qL, int qR) {
        if (node->r < qL || node->l > qR) {
            throw invalid_argument("Invalid query range");
        }
        if (qL <= node->l && node->r <= qR) {
            return node->mergeValue;
        }

        initChildrenIfNeeded(node);
        pushDown(node);

        int mid = node->l + (node->r - node->l) / 2;
        if (qR <= mid) {
            return _query(node->left, qL, qR);
        } else if (qL > mid) {
            return _query(node->right, qL, qR);
        } else {
            int leftResult = _query(node->left, qL, mid);
            int rightResult = _query(node->right, mid + 1, qR);
            return merge(leftResult, rightResult);
        }
    }

    // 计算区间 [l, r] 赋值为 val 后的 mergeValue
    int computeRangeValue(int l, int r, int val) {
        if (type == "sum") {
            return (r - l + 1) * val;
        } else {
            return val;
        }
    }

    // 根据区间长度更新 mergeValue，加上 delta
    int applyAddToValue(SegmentNode* node, int delta) {
        if (type == "sum") {
            return node->mergeValue + (node->r - node->l + 1) * delta;
        } else {
            return node->mergeValue + delta;
        }
    }

    // 动态创建线段树节点
    void initChildrenIfNeeded(SegmentNode* node) {
        if (node->l == node->r) {
            return;
        }
        int mid = node->l + (node->r - node->l) / 2;
        if (node->left == nullptr) {
            int leftMergeValue = computeRangeValue(node->l, mid, defaultValue);
            node->left = new SegmentNode(node->l, mid, leftMergeValue);
        }
        if (node->right == nullptr) {
            int rightMergeValue = computeRangeValue(mid + 1, node->r, defaultValue);
            node->right = new SegmentNode(mid + 1, node->r, rightMergeValue);
        }
    }

    // 下传懒标记，保证子节点的数据正确
    void pushDown(SegmentNode* node) {
        if (node->hasLazyAssign) {
            applyAssign(node->left, node->lazyAssign);
            applyAssign(node->right, node->lazyAssign);
            node->hasLazyAssign = false;
            node->lazyAssign = 0;
        }
        if (node->lazyAdd != 0) {
            applyAdd(node->left, node->lazyAdd);
            applyAdd(node->right, node->lazyAdd);
            node->lazyAdd = 0;
        }
    }

    // 将赋值懒标记下传到子节点
    void applyAssign(SegmentNode* child, int val) {
        child->hasLazyAssign = true;
        child->lazyAssign = val;
        child->lazyAdd = 0;
        child->mergeValue = computeRangeValue(child->l, child->r, val);
    }

    // 将累加懒标记下传到子节点
    void applyAdd(SegmentNode* child, int delta) {
        if (child->hasLazyAssign) {
            child->lazyAssign += delta;
            child->mergeValue = computeRangeValue(child->l, child->r, child->lazyAssign);
        } else {
            child->lazyAdd += delta;
            child->mergeValue = applyAddToValue(child, delta);
        }
    }

    // 区间累加：将闭区间 [qL, qR] 增加 delta（可为负数）
    void _rangeAdd(SegmentNode* node, int qL, int qR, int delta) {
        if (node->r < qL || node->l > qR) {
            throw invalid_argument("Invalid update range");
        }
        if (qL <= node->l && node->r <= qR) {
            if (node->hasLazyAssign) {
                node->lazyAssign += delta;
                node->mergeValue = computeRangeValue(node->l, node->r, node->lazyAssign);
            } else {
                node->lazyAdd += delta;
                node->mergeValue = applyAddToValue(node, delta);
            }
            return;
        }
        initChildrenIfNeeded(node);
        pushDown(node);

        int mid = node->l + (node->r - node->l) / 2;
        if (qL <= mid) {
            _rangeAdd(node->left, qL, qR, delta);
        }
        if (qR > mid) {
            _rangeAdd(node->right, qL, qR, delta);
        }
        node->mergeValue = merge(node->left->mergeValue, node->right->mergeValue);
    }
    
    // 区间赋值：将闭区间 [qL, qR] 赋值为 val
    void _rangeUpdate(SegmentNode* node, int qL, int qR, int val) {
        if (node->r < qL || node->l > qR) {
            throw invalid_argument("Invalid update range");
        }
        if (qL <= node->l && node->r <= qR) {
            node->hasLazyAssign = true;
            node->lazyAssign = val;
            node->lazyAdd = 0;
            node->mergeValue = computeRangeValue(node->l, node->r, val);
            return;
        }

        initChildrenIfNeeded(node);
        pushDown(node);

        int mid = node->l + (node->r - node->l) / 2;
        if (qR <= mid) {
            _rangeUpdate(node->left, qL, qR, val);
        } else if (qL > mid) {
            _rangeUpdate(node->right, qL, qR, val);
        } else {
            _rangeUpdate(node->left, qL, mid, val);
            _rangeUpdate(node->right, mid + 1, qR, val);
        }
        node->mergeValue = merge(node->left->mergeValue, node->right->mergeValue);
    }

public:
    AllInOneSegmentTree(int start, int end, int defaultValue, string type) {
        if (type == "sum" || type == "max" || type == "min") {
            this->type = type;
        } else {
            throw invalid_argument("Invalid type, must be sum, max, or min");
        }
        this->defaultValue = defaultValue;
        int rootMergeValue = computeRangeValue(start, end, defaultValue);
        this->root = new SegmentNode(start, end, rootMergeValue);
    }

    // 根据类型合并左右子节点的值
    int merge(int leftVal, int rightVal) {
        if (type == "sum") {
            return leftVal + rightVal;
        } else if (type == "max") {
            return max(leftVal, rightVal);
        } else if (type == "min") {
            return min(leftVal, rightVal);
        }
        throw invalid_argument("Invalid type");
    }

    // 单点赋值：将索引 index 赋值为 val
    void update(int index, int val) {
        rangeUpdate(index, index, val);
    }

    // 区间赋值：将闭区间 [qL, qR] 赋值为 val
    void rangeUpdate(int qL, int qR, int val) {
        _rangeUpdate(root, qL, qR, val);
    }

    // 单点累加：将索引 index 增加 delta（可为负数）
    void add(int index, int delta) {
        rangeAdd(index, index, delta);
    }

    // 区间累加：将闭区间 [qL, qR] 增加 delta（可为负数）
    void rangeAdd(int qL, int qR, int delta) {
        _rangeAdd(root, qL, qR, delta);
    }

    // 查询闭区间 [qL, qR] 的聚合值
    int query(int qL, int qR) {
        return _query(root, qL, qR);
    }
};