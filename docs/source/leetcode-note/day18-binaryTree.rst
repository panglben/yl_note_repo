.. _day18

Day18: 二叉树-2
================

二叉树的层序遍历
-----------------

- 辅助数据结构---队列

- code

    .. code:: C++

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


LC226-反转二叉树-E
------------------
- 除递归中序遍历外, 其他遍历方式都可以用, 遍历node并交换左右孩子即可
    
- 层序遍历版
    .. code:: C++

        TreeNode* invertTree(TreeNode* root) {
            queue<TreeNode*> que;
            if (root == nullptr) return root;

            que.push(root);
            while (!que.empty()) {
                int size = que.size();
                while (size--) {
                    TreeNode* cur = que.front();
                    TreeNode* temp;
                    que.pop();
                    if (cur->left) que.push(cur->left);
                    if (cur->right) que.push(cur->right);

                    temp = cur->left;
                    cur->left = cur->right;
                    cur->right = temp;
                }
            }

            return root;
        }

- 递归前序版
    .. code:: C++

        TreeNode* invertTree(TreeNode* root) {
            if (root == nullptr) return root;
            swap(root->left, root->right);
            invertTree(root->left);
            invertTree(root->right);
            return root;
        }

- 迭代前序版
    .. code:: C++

        TreeNode* invertTree(TreeNode* root) {
            stack<TreeNode*> st;
            if (root == nullptr) return root;
            st.push(root);
            while (!st.empty())
            {
                TreeNode* cur = st.top();
                swap(cur->left, cur->right);
                st.pop();
                if (cur->right) st.push(cur->right);
                if (cur->left) st.push(cur->left);
            }
            return root;
        }


LC101-对称二叉树-E
-------------------

- 判断二叉树是否对称--比较根节点的两个子树是否镜像

- 递归版
    .. code:: C++

        bool SymCompare(TreeNode* left, TreeNode* right) {
            if (!left && !right) {
                return true;
            } else if (!left || !right ) {
                return false;
            } else if (left->val != right->val) {
                return false;
            }

            bool outer = SymCompare(left->left, right->right);
            bool inner = SymCompare(left->right, right->left);
            return (outer&&inner);
        }

        bool isSymmetric(TreeNode* root) {
            if (!root) return true;
            return SymCompare(root->left, root->right);
        }

- 迭代版-队列辅助
    .. code:: C++

        bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> que;
        if (!root) return true;
        que.push(root->left);
        que.push(root->right);

        while(!que.empty()) {
            TreeNode* left = que.front();
            que.pop();
            TreeNode* right = que.front();
            que.pop();

            if (!left && !right) {
                continue;
            } else if (!left || !right) {
                return false;
            } else if (left->val != right->val) {
                return false;
            }

            que.push(left->left);
            que.push(right->right);
            que.push(left->right);
            que.push(right->left);
        }

        return true;
    }



