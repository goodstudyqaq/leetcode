#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#endif

typedef pair<int, int> pii;
class Solution {
   public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<pii> q(m);
        for (int i = 0; i < m; i++) {
            q[i] = {queries[i], i};
        }
        sort(q.begin(), q.end());

        int sz = logs.size();
        for (int i = 0; i < sz; i++) {
            swap(logs[i][0], logs[i][1]);
        }
        sort(logs.begin(), logs.end());
        debug(logs);

        map<int, int> M;
        int l = 0, r = 0;
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int idx = q[i].second;
            int t = q[i].first;
            while (r < sz && logs[r][0] <= t) {
                M[logs[r][1]]++;
                r++;
            }
            while (l < r && logs[l][0] < t - x) {
                M[logs[l][1]]--;
                if (M[logs[l][1]] == 0) M.erase(logs[l][1]);
                l++;
            }

            ans[idx] = n - M.size();
        }
        return ans;
    }
};