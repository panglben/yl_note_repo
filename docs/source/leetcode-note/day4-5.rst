.. _day4-5

Day4-5: 链表-2
==============

LC24-两两交换链表节点
---------------------

- 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换)。

- code-循环-分类版

    .. code:: C++

        ListNode* swapPairs(ListNode* head) {
            ListNode* dummyHead = new ListNode(0, head);
            ListNode* temp = nullptr;
            ListNode* curr = dummyHead->next;
            ListNode* pre = dummyHead;
            int idx = 0;
            while (curr != nullptr) {
                if (idx%2 == 1) {
                    temp = curr->next;
                    curr->next = pre->next;
                    pre->next->next = temp;
                    pre->next = curr;
                    pre = curr->next;
                    curr = temp;
                } else {
                    curr = curr->next;
                }
                idx ++;
            }
            return dummyHead->next;
        }   

- code-递归
    `参考1 <https://lyl0724.github.io/2020/01/25/1/>`_

    .. code:: C++

        ListNode* swapPairs(ListNode* head) {
            if (head == nullptr || head->next == nullptr) {
                return head;
            }

            ListNode* next = head->next;
            head->next = swapPairs(next->next);
            next->next = head;
            return next;
        }   


LC19-删除链表倒数第N个节点-M
----------------------------

- 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

- 思路: 快指针先走n步, 满指针后走, 定位到 [倒数第 (n+1) 个] (即, 第(sz-n)个) 节点, 删除其next Node

- code-快慢指针

    .. code:: C++

        ListNode* removeNthFromEnd(ListNode* head, int n) {
            ListNode* dummyHead = new ListNode(0, head);
            ListNode* fast = dummyHead;
            ListNode* slow = dummyHead;
            while (n--) {
                fast = fast->next;
            }
            // 定位到倒数第(n+1)个node, 删除其next
            while (fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
            ListNode* temp = slow->next;
            slow->next = slow->next->next;
            delete temp;
            return dummyHead->next;
        }


面试题02.07-S
-------------

- 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null

- code-链表拼接
    一个指针遍历A+B, 另一个遍历B+A, 两个指针必定相遇于交点 or nullptr

    `参考2 <https://leetcode.cn/problems/intersection-of-two-linked-lists/solutions/12624/intersection-of-two-linked-lists-shuang-zhi-zhen-l/>`_

    .. code:: C++

        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            ListNode* wA_B = headA;
            ListNode* wB_A = headB;
            while (wA_B != wB_A) {
                wA_B = wA_B ? wA_B->next : headB;
                wB_A = wB_A ? wB_A->next : headA;
            }
            return wA_B;
        }

LC142-环形链表2-M
-----------------

- 判断链表是否有环并返回入环点

- 思路: 设入环点为x, 环长y, 快指针一次走两步, 满指针一次走一步, 若存在环, 快慢指针必定相遇于环中 (x+m), 且入环点 x = (N-1)y + y - m, N为正整数, 可由此找到入环点。

- code:

    .. code:: C++

        ListNode *detectCycle(ListNode *head) {
            ListNode* fast = head;
            ListNode* slow = head;
            while (fast != nullptr && fast->next !=nullptr) {
                fast = fast->next->next;
                slow = slow->next;
                if (fast == slow) {
                    ListNode* h = head;
                    while (h!=slow) {
                        h = h->next;
                        slow = slow->next;
                    }
                    return h;
                }
            }
            return NULL;
        }