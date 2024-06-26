.. _day11-12

Day11-12: 栈与队列-2
====================

LC20-有效的括号-E
------------------

- 一组大中小括号组成的字符, 判断括号们是否有效匹配

- code-stack

    .. code:: C++

        bool isValid(string s) {
            if (s.size()%2) return false; //剪枝
            stack<char> st;
            for (auto i : s) {
                if (i == '(') {
                    st.push(')');
                } else if (i == '[') {
                    st.push(']');
                } else if (i == '{') {
                    st.push('}');
                } else {
                    if (!st.empty() && i == st.top()) {
                        st.pop();
                    } else {
                        return false;
                    }
                }
            }
            if (st.empty()) {
                return true;
            } else {
                return false;
            }
        }

    - 时间复杂度: O(n)

    - 空间复杂度: O(n)


LC1047-删除字符串中的所有相邻重复项-E
------------------------------------

- code-stack

    .. code:: C++

        string removeDuplicates(string s) {
            stack<char> st;
            for (auto c : s) {
                if (!st.empty() && c == st.top()) {
                    st.pop();
                } else {
                    st.push(c);
                }
            }
            int size = st.size();
            s.resize(size);
            while(size--) {
                s[size] = st.top();
                st.pop();
            }
            return s;
        }

    - 时间复杂度: O(n)

    - 空间复杂度: O(n)

- code-直接用字符串当栈

    .. code:: C++

        string removeDuplicates(string s) {
            string res;
            for (auto c : s) {
                if (!res.empty() && c == res.back()) {
                    res.pop_back();
                } else {
                    res.push_back(c);
                }
            }
            return res;
        }

    - 空间复杂度降为O(1), 因为返回值不计空间复杂度


LC150-逆波兰表达式求值-M
-----------------------

- 根据 **逆波兰表示法** ，求表达式的值。

- note: 逆波兰表达式-一种后缀表达式, 对于计算机来说其实比中缀表达式更友好, 因为不用考虑优先级

- code-stack

    .. code:: C++

        int evalRPN(vector<string>& tokens) {
            stack<int> st;
            int a, b;
            for (auto c : tokens) {
                if (c == "+" || c == "-" || c == "*" || c == "/") {
                    a = st.top();
                    st.pop();
                    b = st.top();
                    st.pop();
                    if (c == "+") {
                        st.push(b + a);
                    } else if (c == "-"){
                        st.push(b - a);
                    } else if (c == "*"){
                        st.push(b * a);
                    } else {
                        st.push(b / a); // 注意顺序
                    }
                    //std::cout << a << " " << b << " " << st.top() << std::endl;
                } else {
                    st.push(stoi(c));
                }
            }
            return st.top();
        }

    - 时间复杂度: O(n)

    - 空间复杂度: O(n)
