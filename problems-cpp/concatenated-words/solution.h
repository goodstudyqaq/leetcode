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

/*
@brief Trie
@docs docs/trie.md
*/

struct TrieNode {
    vector<int> nxt;
    bool is_finish;
    TrieNode(int char_size) {
        nxt.resize(char_size, -1);
        is_finish = false;
    }
    // 一些 hook 函数，用于 Trie 算法以及 ac 自动机, 可以覆盖这些函数来实现一些功能

    // 当加入到字典树后，对最终的节点(当前节点)进行一些操作
    void update_when_finish_in_trie() {
        is_finish = true;
    };

    // 当加入到字典树时，根据当前节点和子节点的信息，对当前节点进行一些操作
    void update_when_push_in_trie(TrieNode &child_node){};

    // 当构建 fail 函数时，根据当前节点和 fail 节点的信息，对当前节点进行一些操作
    void update_when_build_fail(TrieNode &fail_node){};
};

template <typename T = TrieNode>
struct Trie {
   public:
    vector<T> nodes;
    int root;

    int char_size;
    int margin;

    Trie(int char_size, int margin) : root(0), char_size(char_size), margin(margin) {
        nodes.push_back(T(char_size));
    }

    void add(const string &s, int s_idx, int node_idx) {
        /*
         * 将字符串 s 的 s_idx 位置开始的后缀加入到字典树中. node_idx 为当前节点的下标
         */
        if (s_idx == s.size()) {
            // 完成加入
            nodes[node_idx].update_when_finish_in_trie();
        } else {
            const int c = s[s_idx] - margin;
            if (nodes[node_idx].nxt[c] == -1) {
                nodes[node_idx].nxt[c] = nodes.size();
                nodes.push_back(T(char_size));
            }
            add(s, s_idx + 1, nodes[node_idx].nxt[c]);
            // 根据当前节点的子节点更新当前节点
            nodes[node_idx].update_when_push_in_trie(nodes[nodes[node_idx].nxt[c]]);
        }
    }

    void add(const string &s) {
        add(s, 0, root);
    }

    int go(int now, char it) {
        int res = nodes[now].nxt[it - margin];
        return res;
    }
};

class Solution {
   public:
    vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
        sort(words.begin(), words.end(), [&](string &a, string b) {
            return a.size() < b.size();
        });
        Trie trie(26, 'a');
        int n = words.size();
        vector<int> vis;

        function<bool(int, string &)> dfs = [&](int idx, string &s) -> bool {
            if (idx == s.size()) {
                return true;
            }
            if (vis[idx] != -1) return vis[idx];
            int now = trie.root;
            for (int i = idx; i < s.size(); i++) {
                int go = trie.go(now, s[i]);
                if (go == -1) return vis[idx] = false;
                now = go;
                if (trie.nodes[now].is_finish) {
                    if (dfs(i + 1, s)) return vis[idx] = true;
                }
            }
            return vis[idx] = false;
        };
        auto check = [&](string &s) {
            vis.resize(s.size());
            for (int i = 0; i < s.size(); i++) vis[i] = -1;
            return dfs(0, s);
        };
        vector<string> ans;
        for (int i = 0; i < n; i++) {
            if (check(words[i])) {
                ans.push_back(words[i]);
            }
            trie.add(words[i]);
        }
        return ans;
    }
};