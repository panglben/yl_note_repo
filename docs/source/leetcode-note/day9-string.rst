.. _day9

Day9: 字符串-2 (KMP算法)
========================

KMP算法
-------

- 在字符串中寻找是否存在特定子串(模式串)

- prefix-table
    - 保存最长相等前后缀的长度
    - 原理: 匹配失败于后缀之后, 那么移动到前缀后重新匹配即可, 不需要重头匹配

- next数组
    一般相当于 前缀表 - 1, 起始位置为-1, 方便回退


应用1: LC28-找出字符串中第一个匹配项的下标-E
-------------------------------------------

- 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。

- code

    .. code:: C++

        void getNext(int* next, const string& s) {
            // 初始化
            int j = -1;
            next[0] = j;

            for (int i = 1; i < s.size(); i++) {
                while (j >= 0 && s[i] != s[j+1]) {
                    j = next[j];
                }
                if (s[i] == s[j+1]) {
                    j++;
                }
                next[i] = j;
            }
        }

        int strStr(string haystack, string needle) {
            if (needle.size() == 0 || needle.size()>haystack.size()) {
                return -1;
            }
            vector<int> next(needle.size());
            getNext(&next[0], needle);
            int j = -1;
            for (int i = 0; i < haystack.size(); i ++) {
                while (j >= 0 && haystack[i] != needle[j+1]) {
                    j = next[j];
                }
                if (haystack[i] == needle[j+1]) {
                    j++;
                    if (j == (needle.size() - 1)) {
                        return (i - needle.size() + 1);
                    }
                }
            }
            return -1;
        }

应用2: LC459-重复的子字符串
---------------------------

- 给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。

- code

    .. code:: C++

        void getNext(int* next, string s) {
            int j = -1;
            next[0] = -1;
            for (int i = 1; i < s.size(); i++) {
                while (j >= 0 && s[i] != s[j+1]) {
                    j = next[j];
                }
                if (s[i] == s[j + 1]) {
                    j ++;
                }
                next[i] = j;
            }
        }

        bool repeatedSubstringPattern(string s) {
            int len = s.size();
            vector<int> next(len);
            getNext(&next[0], s);
            if (next[len-1] >= 0) {
                if (len % (len - next[len - 1] - 1) == 0) {
                    return true;
                }
            }
            return false;
        }