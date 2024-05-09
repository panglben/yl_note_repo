#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include <algorithm>
using std::vector;
using std::stack, std::queue;
using std::cout, std::cin, std::endl;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class RecurTrave {
public:
    void preorder(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) {
            return;
        }
        vec.push_back(cur->val);
        preorder(cur->left, vec);
        preorder(cur->right, vec);
    }

    vector<int> preorderTrave(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }

    void inorder(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) {
            return;
        }
        inorder(cur->left, vec);
        vec.push_back(cur->val);
        inorder(cur->right, vec);
    }

    vector<int> inorderTrave(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }

    void postorder(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) {
            return;
        }
        postorder(cur->left, vec);
        postorder(cur->right, vec);
        vec.push_back(cur->val);
    }

    vector<int> postorderTrave(TreeNode* root) {
        vector<int> res;
        postorder(root, res);
        return res;
    }
};

class IterTrave {
public: 
    vector<int> preorderTrave(TreeNode* root) {
        // 前序, 访问元素与处理元素一致 (mid-node)
        stack<TreeNode*> st;
        vector<int> res;

        if (root == nullptr) {
            return res;
        }
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            res.push_back(cur->val);
            st.pop();
            // 入栈 中-右左, 出栈 中-左右
            if (cur->right != nullptr) {
                st.push(cur->right);
            }

            if (cur->left != nullptr) {
                st.push(cur->left);
            }
        }
        return res;
    }

    vector<int> inorderTrave(TreeNode* root) {
        // 中序, 访问节点与处理节点不一致, 需额外使用一个指针来访问节点
        stack<TreeNode*> st;
        vector<int> res;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                // 访问, 直到最底层的left-node
                st.push(cur);
                cur = cur->left;
            } else {
                // 开始处理栈中的数据
                cur = st.top();
                res.push_back(cur->val);
                st.pop();
                cur = cur->right;
            }
        }
        return res;
    }

    vector<int> inorderTrave2(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> res;

        if (root != nullptr) {
            st.push(root);
        }

        while (!st.empty()) {
            TreeNode* cur = st.top();
            if (cur != nullptr) {
                st.pop();
                // 切换遍历方式时, 修改以下入栈顺序即可
                if (cur->right) st.push(cur->right);
                st.push(cur);
                st.push(nullptr);
                if (cur->left) st.push(cur->left);
            } else {
                st.pop();
                cur = st.top();
                res.push_back(cur->val);
                st.pop();
            }
        }

        return res;
    }

    vector<int> postorderTrave(TreeNode* root) {
        // 后序, 调整前序中左右节点入栈顺序后, 反转数组
        stack<TreeNode*> st;
        vector<int> res;

        if (root == nullptr) {
            return res;
        }
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            res.push_back(cur->val);
            st.pop();

            if (cur->left != nullptr) {
                st.push(cur->left);
            }

            if (cur->right != nullptr) {
                st.push(cur->right);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<vector<int>> levelOrderTrave(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> que;

        if (root == nullptr) {
            return res;
        }

        que.push(root);
        while (!que.empty()) {
            vector<int> vec;
            int size = que.size();
            while (size--) {
                TreeNode* cur = que.front();
                vec.push_back(cur->val);
                que.pop();
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
            res.push_back(vec);
        }

        return res;
    }
};

int main()
{
    TreeNode* left = new TreeNode(2);
    TreeNode* right = new TreeNode(3);
    TreeNode* root = new TreeNode(1, left, right);

    left->left = new TreeNode(4);
    left->right = new TreeNode(5);

    right->left = new TreeNode(6);
    right->right = new TreeNode(7);

    RecurTrave rec;
    vector<int> vec;
    vec = rec.preorderTrave(root);
    for (auto n : vec) {
        cout << n << " ";
    }
    cout << endl;

    IterTrave it;
    vector<int> vec2;
    vec2 = it.inorderTrave2(root);
    for (auto n : vec2) {
        cout << n << " ";
    }
    cout << endl;

    vector<vector<int>> levelVec;
    levelVec = it.levelOrderTrave(root);
    cout << levelVec.size() << endl;

    for (auto v : levelVec) {
        cout << '[';
        for (auto n : v) {
            cout << n << " ";
        }
        cout << ']' << endl;
    }
}
