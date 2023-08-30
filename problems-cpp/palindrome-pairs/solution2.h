#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#elif __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#else
#define debug(...) 42
#endif

struct Tree {
    int index, childs[26];
} rever[1500000], order[1500000];
int kids[1500000][27];  // 第一位存储孩子个数
unordered_map<int, vector<int>> nodes, rev_nodes;

class Solution {
   private:
    unordered_set<int> lens;
    vector<vector<int>> result;
    int reverCnt = 0, orderCnt = 0;

   public:
    void insert(string& word, int index) {
        int p1 = 0, p2 = 0, ch = 0;
        int n = word.size();
        for (int i = 0; i < n; ++i) {
            ch = word[i] - 'a';
            if (!order[p1].childs[ch]) {
                order[p1].childs[ch] = ++orderCnt;
                kids[p1][++kids[p1][0]] = ch;
            }
            p1 = order[p1].childs[ch];

            ch = word[n - 1 - i] - 'a';
            if (!rever[p2].childs[ch]) {
                rever[p2].childs[ch] = ++reverCnt;
            }
            p2 = rever[p2].childs[ch];

            // 若当前i为words中某个单词长度 - 1，则当前节点存储经过哪些单词
            if (lens.find(i) != lens.end()) {
                nodes[p1].emplace_back(index);
                rev_nodes[p2].emplace_back(index);
            }
        }
        order[p1].index = rever[p2].index = index;
    }

    bool isPalindrome(const string& word, int i, int j) {
        while (i < j) {
            if (word[i++] != word[j--]) return false;
        }
        return true;
    }

    void dfsFindAllPalindromePair(const int& node1, const int& node2, const vector<string>& words) {
        int idx = order[node1].index, len = 0;
        // 若当前trie节点为单词的末尾终止字符，则在另一个树中查找经过该节点的所有单词，其剩余子串的能否形成前缀树
        if (idx) {
            len = words[idx - 1].size() + 1;
            // 查找另一前缀树对应节点所经过的所有单词
            for (auto&& j : rev_nodes[node2]) {
                // 与trie当前节点单词不为同一单词
                if (j != idx) {
                    // 此时rev翻转串剩余字符构成回文，则将 {trie, j}单词对加入结果集。这个包括了正好为trie翻转串的情况
                    if (isPalindrome(words[j - 1], 0, words[j - 1].size() - len)) {
                        result.emplace_back(vector<int>{idx - 1, j - 1});
                    }
                }
            }
        }
        idx = rever[node2].index;
        // 若当前rev_trie节点为单词的末尾终止字符，则在另一个树中查找长度超过该节点的所有单词，其剩余子串的能否形成前缀树
        if (idx) {
            len = words[idx - 1].size();
            // 查找另一前缀树对应节点所经过的所有单词
            for (auto&& i : nodes[node1]) {
                // 正序前缀树中长度长于当前rev_trie节点的单词。该条件就已经同时筛去了不与trie或rev_trie为同一单词这两点
                if (words[i - 1].size() > len) {
                    // 此时rev翻转串剩余字符构成回文，则将 {trie, j}单词对加入结果集。
                    if (isPalindrome(words[i - 1], len, words[i - 1].size() - 1)) {
                        result.emplace_back(vector<int>{i - 1, idx - 1});
                    }
                }
            }
        }
        // 从正序前缀树找翻转前缀树。若正序前缀树遍历完了，那么trie此时一定为叶子结点也为单词末尾字符，无论此时翻转前缀树是否遍历到叶子结点，
        // 其rev_trie后是否还有子节点，在上面第一个if就已经处理和判别了rev_trie剩余子串是否为回文这点，并加入了结果数组，因此不需重复考虑。
        for (int i = 1; i <= kids[node1][0]; ++i) {
            // 只有两个数同时存在相同节点才能往下找
            if (rever[node2].childs[kids[node1][i]]) {
                dfsFindAllPalindromePair(order[node1].childs[kids[node1][i]], rever[node2].childs[kids[node1][i]], words);
            }
        }
    }

    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size(), null_idx = -1;

        for (auto&& word : words) {
            lens.emplace(word.size() - 1);
        }
        vector<int> self_rev = {};  // 存储所有自回文串
        for (int i = 0; i < n; ++i) {
            // 判断是否为自回文，放在前面好不让空串加入前缀树
            if (isPalindrome(words[i], 0, words[i].size() - 1)) {
                if (words[i] == "") {
                    null_idx = i;
                    continue;
                }
                self_rev.emplace_back(i);
            }
            insert(words[i], i + 1);
        }
        // 若存在空串，则先与所有自回文拼成单词对
        if (null_idx != -1) {
            for (auto&& j : self_rev) {
                result.emplace_back(vector<int>{null_idx, j});
                result.emplace_back(vector<int>{j, null_idx});
            }
        }
        dfsFindAllPalindromePair(0, 0, words);
        memset(rever, 0, (reverCnt + 1) * sizeof(Tree));
        memset(order, 0, (orderCnt + 1) * sizeof(Tree));
        memset(kids, 0, (orderCnt + 1) * sizeof(kids[0]));
        nodes.erase(nodes.begin(), nodes.end());
        rev_nodes.erase(rev_nodes.begin(), rev_nodes.end());
        return result;
    }
};
