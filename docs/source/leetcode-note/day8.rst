.. _day8

Day8: 字符串-1
===============

LC344-反转字符串
----------------

- 编写一个函数, 其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。
    不要给另外的数组分配额外的空间, 你必须 **原地修改输入数组** , 使用 O(1) 的额外空间解决这一问题。

- code

    .. code:: C++

        void reverseString(vector<char>& s) {
            for (int i = 0; i < s.size()/2; i++) {
                swap(s[i], s[s.size()-1-i]);
            }
        }

LC541-反转字符串2
-----------------

- 给定一个字符串 s 和一个整数 k, 从字符串开头算起, 每计数至 2k 个字符, 就反转这 2k 字符中的前 k 个字符。

    - 如果剩余字符少于 k 个, 则将剩余字符全部反转。

    - 如果剩余字符小于 2k 但大于或等于 k 个, 则反转前 k 个字符, 其余字符保持原样。

- code-AC初版

    .. code:: C++

        string reverseStr(string s, int k) {
            int ini = 0;
            for (int group = 0; group < s.size()/2/k; group++) {
                for (int i = 0; i < k/2; i++) {
                    swap(s[ini+i], s[ini+k-i-1]);
                }
                ini += 2*k;
            }
            int remain = s.size()%(2*k);
            ini = s.size() - remain;
            if (remain > k) {
                for (int i = 0; i < k/2; i++) {
                    swap(s[ini+i], s[ini+k-i-1]);
                }
            } else {
                for (int i = 0; i < remain/2; i++) {
                    swap(s[ini+i], s[s.size()-i-1]);
                }
            }
            return s;
        }

- code-看题解后的改进版

    .. code:: C++

        void My_reverse(string& s, int start, int end) {
            for (int i = start, j = end; i< j; i++, j--) {
                swap(s[i], s[j]);
            }
        }

        string reverseStr(string s, int k) {
            for (int i = 0; i < s.size(); i += (2*k)) {
                if (i + k <= s.size()) {
                    My_reverse(s, i, i+k-1);
                } else {
                    My_reverse(s, i, s.size()-1);
                }
            }
            return s;
        }


KamaC54-替换数字
----------------

- https://kamacoder.com/problempage.php?pid=1064

- 给定一个字符串 s, 它包含小写字母和数字字符, 请编写一个函数, 将字符串中的字母字符保持不变, 而将每个数字字符替换为number。

- 思路1 - 准备额外空间给新数组

- 思路2 - 扩容原数组, **从后向前** 填充

- 接下来几题都有些类似, 如果准备额外空间存储新数组就会很简单, 但是限定在原数组上操作会比较难


LC151-反转字符串里的单词
-------------------------

- code: AC初版-准备额外空间给新数组

    .. code:: C++
        string reverseWords(string s) {
            string res;
            string word;
            bool isWord = false;
            for (int i = s.size() - 1; i >= 0; i--) {
                if (isWord) {
                    if (s[i] != ' ') {
                        word += s[i];
                    } else {
                        for (int j = word.size()-1; j >= 0; j--) {
                            res += word[j];
                        }
                        res += " ";
                        isWord = false;
                        word = "";
                    }
                } else {
                    if (s[i] != ' ') {
                        word += s[i];
                        isWord = true;
                    } else {
                        continue;
                    }
                }
            }
            if (isWord) {
                std::cout << word << std::endl;
                for (int j = word.size()-1; j >= 0; j--) {
                    res += word[j];
                }
            } else {
                res.pop_back();
            }
            return res;
        }

- code: 题解版本-双指针整体反转并去除额外空格 + 局部反转

KamaC55-右旋转字符串
--------------------

- https://kamacoder.com/problempage.php?pid=1065

- 字符串的右旋转操作是把字符串尾部的若干个字符转移到字符串的前面。给定一个字符串 s 和一个正整数 k
    请编写一个函数, 将字符串中的后面 k 个字符移到字符串的前面, 实现字符串的右旋转操作。

- 整体反转 + 两个子串额外反转