/*
Code generated by https://github.com/goodstudyqaq/leetcode-local-tester
*/
#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#elif __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#else
#define debug(...) 42
#endif

typedef array<int, 3> a3;
class FreqStack {
   public:
    vector<stack<int>> V;
    unordered_map<int, int> M;

    FreqStack() {
        V.push_back(stack<int>{});
        V.push_back(stack<int>{});
    }
    void push(int val) {
        debug("push", val);
        if (M.count(val)) {
            M[val]++;
            int cnt = M[val];
            if (cnt < V.size()) {
                V[cnt].push(val);
            } else {
                stack<int> tmp;
                tmp.push(val);
                V.push_back(tmp);
            }
        } else {
            V[1].push(val);
            M[val] = 1;
        }
        debug(val, M[val]);
    }

    int pop() {
        debug("pop");
        int res = V.back().top();
        V.back().pop();
        if (V.back().size() == 0) {
            V.pop_back();
        }
        M[res]--;
        if (M[res] == 0) M.erase(res);
        return res;

    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */