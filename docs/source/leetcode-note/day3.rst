.. _day3

Day3: 链表-1
============

关于链表 (Linked List)
----------------------

- 链表结构:

    - 单链表 -- 若非特别说明, 后文链表均指单链表

        - ListNode - var + pointer to the next node
        
        - 节点定义:
        
        .. code:: c++

            struct ListNode {
                int val;
                ListNode *next;
                ListNode() : val(0), next(nullptr) {}
                ListNode(int x) : val(x), next(nullptr) {}
                ListNode(int x, ListNode *next) : val(x), next(next) {}
            };


    - 双链表

    - 循环链表

LC203-移除链表元素
------------------

- 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

- note: C++里最好手动清理一下被删的node

- code

    .. code:: c++

        ListNode* removeElements(ListNode* head, int val) {
            ListNode* dummyHead = new ListNode(0, head);
            ListNode* curr = dummyHead;
            while (curr->next != nullptr) {
                if (curr->next->val == val) {
                    ListNode* temp = curr->next;
                    curr->next = curr->next->next;
                    delete temp;
                } else {
                    curr = curr->next;
                }
            }
            return dummyHead->next;
        }

LC707-设计链表-M
----------------

- 自己设计一个链表类, 实现addAtHead/Tail/Index, 和deleteAtIndex功能

- code

    .. code:: c++

        class MyLinkedList {
        public:
            struct ListNode {
                int val;
                ListNode* next;
                ListNode() : val(0), next(nullptr) {}
                ListNode(int x) : val(x), next(nullptr) {}
                ListNode(int x, ListNode* next) : val(x), next(next) {}
            };

            MyLinkedList() {
                _dummyHead = new ListNode(0);
                _size = 0;
            }
            
            int get(int index) {
                if (index<0 || index>=_size) return -1;
                else {
                    ListNode* curr = _dummyHead->next;
                    while (index--) {
                        curr = curr->next;
                    }
                    return curr->val;
                }
            }
            
            void addAtHead(int val) {
                ListNode* newNode = new ListNode(val, _dummyHead->next);
                _dummyHead->next = newNode;
                _size ++;
            }
            
            void addAtTail(int val) {
                ListNode* newNode = new ListNode(val);

                ListNode* curr = _dummyHead;
                int n = _size;
                while (n--) {
                    curr = curr->next;
                }
                curr->next = newNode;
                _size ++;
            }
            
            void addAtIndex(int index, int val) {
                if (index > _size) return;
                else if (index <= 0) {
                    addAtHead(val);
                } else if (index == _size) {
                    addAtTail(val);
                } else{
                    ListNode* newNode = new ListNode(val);
                    ListNode* curr = _dummyHead;
                    while (index--) {
                        curr = curr->next;
                    }
                    newNode->next = curr->next;
                    curr->next = newNode;
                    _size ++;
                }
            }
            
            void deleteAtIndex(int index) {
                if (index >= 0 && index < _size) {
                    // find the one before node[index]
                    ListNode* curr = _dummyHead;
                    while (index--) {
                        curr = curr->next;
                    }
                    ListNode* temp = curr->next;
                    curr->next = curr->next->next;
                    delete temp;
                    _size --;
                }
            }

        private:
            ListNode* _dummyHead;
            int _size;
        };

LC206-反转链表
--------------

Todo