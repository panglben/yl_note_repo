.. _day13

Day13: 栈与队列-3
==================

STL-优先级队列
--------------

- 原型定义: priority_queue<Type, Container, Functional>

    - Type: 数据类型, 默认为int

    - Container: 容器类型, 默认为vector<int>

    - Functional: 比较的方式, 默认为std仿函数less<int> (大顶堆), 小顶堆对应仿函数为more<int>

- 实质: 给出队列接口的 **堆**

LC239-滑动窗口最大值-H
-----------------------

- 给你一个整数数组 nums, 有一个大小为 *k* 的滑动窗口从数组的最左侧移动到数组的最右侧。

    你只可以看到在滑动窗口内的 *k* 个数字。滑动窗口每次只向右移动一位。

    返回 *滑动窗口中的最大值* 。

- 思路: 自定义一个单调队列, 底层实现是deque

- code

    .. code:: C++

        class myMonoQue {
        public:
            deque<int> que;

            void push(int value) {
                // 比value大的都弹出, 确保队列内back->front单调递增
                while (!que.empty() && value > que.back()) {
                    que.pop_back();
                }
                que.push_back(value);
            }

            void pop(int value) {
                if (value == que.front()) {
                    que.pop_front();
                }
            }

            int front() {
                return que.front();
            }

        };

        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            vector<int> res;
            myMonoQue que;
            for (int i = 0; i < k; i++) {
                que.push(nums[i]);
            }
            res.push_back(que.front());
            for (int i = k; i < nums.size(); i++) {
                que.pop(nums[i-k]);
                que.push(nums[i]);
                res.push_back(que.front());
            }
            return res;
        }                   

    - 时间复杂度: O(n)

    - 空间复杂度: O(k)


LC347-前K个高频元素-M
----------------------

- 给你一个整数数组 *nums* 和一个整数 *k* , 请你返回其中出现频率前 *k* 高的元素。
    你可以按 *任意顺序* 返回答案。

- 构建内部为 **小顶堆** 的大小为 *k* 的优先级队列
    弹出最小元素, 才能保证堆中积累的时前k个最大元素

- code: priority_queue / min_heap

    ..code:: C++

        // min-heap
        class myMore {
        public:
            bool operator()(const pair<int, int>& lhs,const pair<int, int>& rhs) {
                return lhs.second > rhs.second;
            }
        };

        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int, int> mapFreq;
            for (int n : nums) {
                mapFreq[n]++;
            }

            priority_queue<pair<int, int>, vector<pair<int, int>>, myMore> pri_que;

            for (auto iter = mapFreq.begin(); iter != mapFreq.end(); iter++) {
                pri_que.push(*iter);
                if (pri_que.size() > k) {
                    pri_que.pop();
                }
            }
            
            vector<int> res;
            for (int i = 0; i < k; i++) {
                res.push_back(pri_que.top().first);
                pri_que.pop();
            }

            return res;
        }

    - 时间复杂度: O(nlogk) - 维护堆的时间复杂度为logk

    - 空间复杂度: O(k)