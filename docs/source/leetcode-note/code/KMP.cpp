#include<iostream>
#include<vector>
#include<string>
using std::vector, std::string;

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

// 在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）
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

int main()
{
    string t = "abcdabcdabcd";
    vector<int> next(t.size());
    getNext(&next[0], t);

    std::cout << "";
    for (auto i : next) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}