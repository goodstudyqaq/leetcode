"""
Code generated by https://github.com/goodstudyqaq/leetcode-local-tester
"""
try:
    from utils.python3.help import *
except ImportError:
    pass # In leetcode environment, we don't need to import the help file.

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:

        @lru_cache(None)
        def dfs(s, wordDict):
            if not s:
                return True
            for word in wordDict:
                if s.startswith(word) and dfs(s[len(word):], wordDict):
                    return True
            return False
        
        return dfs(s, tuple(wordDict))


