#include<bits/stdc++.h>
using namespace std;
//要修改节点就要用root->left/right = ...，然后返回root，不能直接root->left/right = ...，否则会断开
class BST {
public:
    BST(int x) : val(x), left(NULL), right(NULL) {}
    BST() : val(0), left(NULL), right(NULL) {}
    BST(const BST& other) : val(other.val), left(nullptr), right(nullptr) {
        if (other.left) {
            left = new BST(*other.left);
        }
        if (other.right) {
            right = new BST(*other.right);
        }
    }
    bool isVaildBST(BST* root) {
        return _isVaildBST(root, nullptr, nullptr);
    }
    BST* insert(BST* root, int val) {
        //利用返回值来连接插入节点后的树
        //找到了插入位置就创建新节点返回
        if (root == nullptr) return new BST(val);
        if (val < root->val) {
            root->left = insert(root->left, val);
        }
        else {
            root->right = insert(root->right, val);
        }
        //返回插入节点后的树的根节点，使root左右子树不会断开
        return root;
    }

    BST* search(BST* root, int val) {
        //找不到返回nullptr
        if (root == nullptr) {
            return nullptr;
        }
        //找到了就返回该节点
        if (root->val == val){
            return root;
        }
        //根据二叉搜索树的性质决定往左子树还是右子树找
        else if (val < root->val) {
            return search(root->left, val);
        }
        else if (val > root->val) {
            return search(root->right, val);
        }
        //最后的返回值用来防止编译器报错
        return nullptr;
    }

    BST* deleteNode(BST* root, int key) {
        //利用返回值nullptr来删除节点
        //找不到就返回nullptr
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val == key) {
            //找到了要删除的节点
            if(root->left==nullptr&&root->right==nullptr){
                //要删除的节点是叶子节点
                delete root;
                root = nullptr;
                return nullptr;
            }
            else if(root->left==nullptr){
                //要删除的节点只有右子树
                BST* rightChild = root->right;
                delete root;
                return rightChild;
            }
            else if(root->right==nullptr){
                //要删除的节点只有左子树
                BST* leftChild = root->left;
                delete root;
                return leftChild;
            }
            else{
                //要删除的节点有左右子树
                //找到右子树的最小节点
                BST* minNode = root->right;
                while(minNode->left!=nullptr){
                    minNode = minNode->left;
                }
                //通过操作指针实现真正的删除
                //复制一个minNode,以免在下面递归调用deleteNode时minNode被释放
                BST* copyNode = new BST(*minNode);
                root->right = deleteNode(root->right, minNode->val);//注意，在递归调用deleteNode后，minNode已经被释放了
                copyNode->left = root->left;
                copyNode->right = root->right;
                delete root;
                return copyNode;
            }
        }
        else if (key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        //返回删除后的树的根节点，使root左右子树不会断开，但是也可以在找到删除节点时返回
        return root;
    }

private:
    int val;
    BST *left;
    BST *right;
    bool _isVaildBST(BST* root, BST* min, BST* max) {
        if (root == nullptr) return true;
        if (min != nullptr && root->val <= min->val) return false;
        if (max != nullptr && root->val >= max->val) return false;
        return _isVaildBST(root->left, min, root) 
            && _isVaildBST(root->right, root, max);
    }
};

int main() {
    BST* root = new BST(5);
    root = root->insert(root, 3);
    return 0;
}