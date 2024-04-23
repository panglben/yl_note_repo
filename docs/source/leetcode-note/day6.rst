.. _day6

Day6: 哈希表-1
===============

关于哈希表 (Hash Table)
------------------------

- 空间换时间，可以快速索引/判断一个元素是否出现在集合里 (O(1))

- Hash function - 将key映射为哈希表上的索引

    index = hashFunction(name)

    hashFunction = hashCode(name) % tableSize

- Hash Collisions - 多个key映射到了同一索引

    - 拉链法: 将冲突元素存储为链表

    - 线性探测法: 向下找哈希表中的空位存放冲突元素 (需要tableSize > dataSize)

- 哈希结构

    - 数组

    - set -- std::unordered_set in C++

    - map -- std::unordered_map in C++
        
    - 注： std::set/map 与 std::multiset/multimap 的底层实现是红黑树, key是有序的

LC242-isAnagram-E
-------------------
- 思路: 只包含小写字母, 用一个长26的数组充当哈希表即可

- code  

    .. code:: C++

        bool isAnagram(string s, string t) {
            vector<int> count(26, 0);
            for (auto i : s) {
                count[i-'a'] ++;
            }
            for (auto i : t) {
                count[i-'a'] --;
            }
            for (auto c : count) {
                if (c != 0) return false; 
            }
            return true;
        }


LC349-数组交集-E
----------------

- 给定两个数组 nums1 和 nums2 ，返回它们的交集 。输出结果中的每个元素一定是 **唯一** 的。我们可以 不考虑输出结果的顺序 。

- code-set

    .. code:: C++

        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            unordered_set<int> s_nums1(nums1.begin(), nums1.end());
            unordered_set<int> s_inter;
            for (int n : nums2) {
                if ((s_nums1.find(n) != s_nums1.end())) {
                        s_inter.insert(n);
                    }
            }
            vector<int> v_inter(s_inter.begin(), s_inter.end());
            return v_inter;
        }


LC202-快乐数-E
---------------

- code-set

    .. code:: C++

        bool isHappy(int n) {
            unordered_set<int> rec;
            while (n != 1) {
                if (rec.find(n) != rec.end()) {
                    return false;
                }
                rec.insert(n);
                int sum = 0;
                while (n != 0) {
                    sum += (n%10) * (n%10); //注意优先级
                    n = n/10;
                }
                n = sum;
            }
            return true;
        }

LC1-两数之和-E
---------------

- 给定一个整数数组 nums 和一个整数目标值 target, 请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
    你可以按任意顺序返回答案。

- 思路: 存储map(n[i], i), 并检索target-n[i]是否已被记录

- code-map

    .. code:: C++

        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> map_num;
            for (int i=0; i<nums.size(); i++) {
                auto iter = map_num.find(target-nums[i]);
                if (iter != map_num.end()) {
                    return {i, iter->second};
                }
                map_num.insert({nums[i], i});
            }
            return {};
        }

- 时间复杂度: O(n)

- 空间复杂度: O(n)