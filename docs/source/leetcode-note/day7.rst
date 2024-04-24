.. _day7

Day7: 哈希表-2
==============

LC454-四数相加2-M
------------------

- 给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：

    - 0 <= i, j, k, l < n
    - nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

- 本题很简单, 因为只需要统计元组数, 且不需要去重

- code-map

    .. code:: C++

        int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
            unordered_map<int, int> map_sum1p2;
            int res = 0;
            for (int n1 : nums1) {
                for (int n2 : nums2) {
                    // 新关键词的值会初始化为0, 不需要额外判断
                    map_sum1p2[n1+n2] ++;
                    /* auto iter = map_sum1p2.find(n1 + n2);
                    if (iter == map_sum1p2.end()) {
                        map_sum1p2.insert({n1 + n2, 1});
                    } else {
                        iter->second ++;
                    } */
                }
            }
            for (int n3 : nums3) {
                for (int n4 : nums4) {
                    auto iter = map_sum1p2.find(0 - n3 - n4);
                    if (iter != map_sum1p2.end()) {
                        res += iter->second;
                    }
                }
            }
            return res;
        }
    
- 时间复杂度: \ :math:`O(n^2)`\
- 空间复杂度: \ :math:`O(n^2)`\


LC383-赎金信-E
--------------

- 给你两个字符串: ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

    如果可以，返回 true ；否则返回 false 。

    magazine 中的每个字符只能在 ransomNote 中使用一次。

- 只含小写字母, 类似isAnagram, 用数组当哈希表

- code

    .. code:: C++

        bool canConstruct(string ransomNote, string magazine) {
            vector<int> rec_magzine(26, 0);
            for (auto m : magazine) {
                rec_magzine[m-'a'] ++;
            }
            for (auto n : ransomNote) {
                rec_magzine[n-'a'] --;
                if (rec_magzine[n-'a'] < 0) return false;
            }
            return true;
        }


LC15-三数之和-M
----------------

- 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请

    返回所有和为 \ *0*\  且 **不重复** 的三元组。

- 理解如何去重

- code-双指针

    .. code:: C++

        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> res;
            sort(nums.begin(), nums.end());

            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > 0) {
                    break;
                }
                if (i > 0 && nums[i] == nums[i-1]) {
                    // 去重 a
                    continue;
                }
                // 注意 left 初值 和 循环判断条件
                int left = i + 1, right = nums.size()-1;
                while (left < right) {
                    int sum = nums[i] + nums[left] + nums[right];
                    if (sum < 0) {
                        left ++;
                    } else if (sum > 0) {
                        right --;
                    } else {
                        res.push_back({nums[i], nums[left], nums[right]});
                        // 去重b和c
                        while (left < right && nums[left] == nums[left+1]) {
                            left ++;
                        }
                        while (left < right && nums[right] == nums[right-1]) {
                            right --;
                        }
                        left ++;
                        right --;
                    }
                }
            }
            return res;
        }

- 时间复杂度: \ :math:`O(n^2)` \


LC18-四数之和-M
----------------

- 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且 **不重复** 的四元组 [nums[a], nums[b], nums[c], nums[d]] 
    （若两个四元组元素一一对应，则认为两个四元组重复）：
    0 <= a, b, c, d < n
    a、b、c 和 d 互不相同
    nums[a] + nums[b] + nums[c] + nums[d] == target
    你可以按 \*任意顺序*\ 返回答案 。

- 三数之和plus, 外面嵌套一层for循环即可, 但因为target不固定为0了, 剪枝处理时要额外注意

- code-双指针

    .. code:: C++

        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            vector<vector<int>> res;
            sort(nums.begin(), nums.end());

            for (int a = 0; a < nums.size(); a++) {
                if (nums[a] >= 0 && nums[a] > target) {
                    // 注意不能只靠nums[a]>target判断，因为负数加上去可以让sum变小
                    break; // 剪枝
                }
                if (a > 0 && nums[a] == nums[a-1]) {
                    continue; // 去重
                }
                for (int b = a + 1; b < nums.size(); b++) {
                    if (nums[a] + nums[b] > target && nums[b] >= 0) {
                            break; // 剪枝
                    }
                    if (b > a + 1 && nums[b] == nums[b-1]) {
                        // 要加上 b > a + 1 判断, 不然b和a一样时会被误伤
                        continue; // 去重
                    }
                    int left = b + 1, right = nums.size() - 1;
                    while(left < right) {
                        // 防止溢出，因为有狠毒的算例 - -|||
                        long sum = (long) nums[a] + nums[b] + nums[left] + nums[right];
                        if (sum < target) {
                            left ++;
                        } else if (sum > target) {
                            right --;
                        } else {
                            res.push_back({nums[a], nums[b], nums[left], nums[right]});
                            while (left < right && nums[left]==nums[left+1]) {
                                left ++; // 去重
                            }
                            while (left < right && nums[right]==nums[right-1])
                            {
                                right --; // 去重
                            }
                            left ++;
                            right --;
                        }
                    }
                }
            }
            return res;
        }

- 时间复杂度: \ :math:`O(n^3)` \