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


LC15-三数之和
----------------


LC18-四数之和
--------------