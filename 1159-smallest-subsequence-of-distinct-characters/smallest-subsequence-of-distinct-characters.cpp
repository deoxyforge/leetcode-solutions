class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> cnt(26, 0);
        vector<bool> vis(26, false);

        for (char c : s)
            cnt[c - 'a']++;

        string st;

        for (char c : s) {
            cnt[c - 'a']--;

            if (vis[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   cnt[st.back() - 'a'] > 0) {
                vis[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            vis[c - 'a'] = true;
        }

        return st;
    }
};