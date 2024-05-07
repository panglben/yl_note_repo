.. _day10

Day10: 栈与队列-1
==================

关于 栈 (stack) 与队列 (queue)
------------------------------

- 对外提供时间复杂度O(1)的 push/pop/top 接口, 不提供遍历功能和迭代器

- 底层实现可以是vector, deque, list, 对于SGI STL, 默认底层结构为deque


LC232-用栈实现队列-E
--------------------

- 用两个栈实现队列

- 分入栈和出栈, push直接进入栈, pop时弹出栈, 出栈为空的时候从入栈把数据倒进来

- code

    .. code:: C++

        class MyQueue {
        public:
            stack<int> stIn;
            stack<int> stOut;

            MyQueue() {
                
            }
            
            void push(int x) {
                stIn.push(x);
            }
            
            int pop() {
                if (stOut.empty()) {
                    // stOut为空的时候, 从stIn里倒入数据
                    while(!stIn.empty()) {
                        stOut.push(stIn.top());
                        stIn.pop();
                    }
                }
                int res = stOut.top();
                stOut.pop();
                return res;
            }
            
            int peek() {
                int res = this->pop();
                stOut.push(res);
                return res;
            }
            
            bool empty() {
                return (stIn.empty() && stOut.empty());
            }
        };

- 时间复杂度: pop/top为O(n), push/empty为O(1)

- 空间复杂度: O(n)


LC225-用队列实现栈-E
--------------------

- 用两个队列实现栈

- 队列倒进另一个队列, 顺序不会变, 所以与上一题思路不同, 用一个备份队列实现弹出操作, 也可以原地push回去直到找到原队列末尾

- code-两个队列版

    .. code:: C++

        class MyStack {
        public:
            deque<int> deq;
            deque<int> deqBack;

            MyStack() {

            }
            
            void push(int x) {
                deq.push_back(x);
            }
            
            int pop() {
                int res;
                while (deq.size() > 1) {
                    deqBack.push_back(deq.front());
                    deq.pop_front();
                }
                res = deq.front();
                deq.pop_front();
                deq = deqBack;
                while (!deqBack.empty()) {
                    deqBack.pop_front();
                }
                return res;
            }
            
            int top() {
                int res = this->pop();
                deq.push_back(res);
                return res;
            }
            
            bool empty() {
                return deq.empty();
            }
        };        

- code-单队列实现

    .. code:: C++

        int pop() {
            int res;
            int size = deq.size() - 1;
            while (size --) {
                deq.push_back(deq.front());
                deq.pop_front();
            }
            res = deq.front();
            deq.pop_front();
            return res;
        }

- 时间复杂度: pop/top为O(n), push/empty为O(1)

- 空间复杂度: O(n)