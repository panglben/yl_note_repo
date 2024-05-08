.. _day14

Day14: 二叉树-1
================


关于二叉树 (Binary Tree)
------------------------

关于树
``````
- 节点: 父节点, 子树, 兄弟节点
- 度, 层次

种类
````
- 满二叉树
- 完全二叉树
    只有最下面两层节点的度可以小于2, 并且最下层的叶节点集中在靠左的若干位置上。
- 二叉查找/搜索树 (Binary Search Tree)
- 平衡二叉搜索树 (AVL树)
    左右子树高度差不超过1, 且左右子树均为AVL树
    - C++中map、set、multimap, multiset的底层实现

存储方式
````````
- 链式存储: 链表--节点元素 + 左指针 + 右指针
    
    .. code:: C++

        struct TreeNode {
            int val;
            TreeNode* left;
            TreeNode* right;
            TreeNode(int x) : val(x), left(NULL), right(NULL) {}
            TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
        }

- 顺序存储: 数组--[i]的左孩子: [2i+1], 右孩子[2i+2]

遍历方式
````````

- 深度优先遍历
    前/中/后序遍历 (递归法, 迭代法)

- 广度优先遍历
    层次遍历 (迭代法)


二叉树的递归遍历
----------------

- code

    .. code:: C++

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

- 时间复杂度: O(n) - 每个节点被遍历一次
- 空间复杂度: O(n) - 递归过程中  **栈**  的开销, 平均情况为O(logn), 最坏情况(链状分布)为O(n)

二叉树的迭代遍历
----------------
- 递归法中隐式维护了一个栈, 迭代法将该栈显示地模拟出来

- code

    .. code:: C++

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
        };  


二叉树的统一迭代法
-------------------

- 在访问过蛋还未处理的mid-node入栈后, 跟一个空指针做标记, 可以写出统一风格的迭代法前/中/后序遍历
    跟递归法类似, 只要调整左中右的入栈顺序即可

- code: 

    .. code:: C++

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