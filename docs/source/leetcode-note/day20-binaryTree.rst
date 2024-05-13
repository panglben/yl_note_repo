.. _day20

Day19: 二叉树-4
================

LC110-平衡二叉树
--------------------
- 平衡二叉树定义
    一个二叉树 **每个节点** 的左右两个子树的高度差的绝对值不超过1

    - 平衡二叉树的每个子树都是平衡二叉树

- code-后序遍历
    .. code:: C++

        int getHeight(TreeNode* cur) {
            if (cur == nullptr) return 0;
            int leftHeight = getHeight(cur->left);
            if (leftHeight == -1) return -1;
            int rightHeight = getHeight(cur->right);
            if (rightHeight == -1) return -1;

            if (abs(rightHeight-leftHeight) > 1) return -1;
            return max(rightHeight, leftHeight) + 1;
        }
        bool isBalanced(TreeNode* root) {
            return getHeight(root) == -1 ? false:true;
        }


LC257-二叉树的所有路径
------------------------


LC404-左叶子之和
------------------------