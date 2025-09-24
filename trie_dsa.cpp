#include <bits/stdc++.h>
using namespace std;

// ------------------ BASIC TRIE IMPLEMENTATION ------------------

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return true;
    }
};

// ------------------ TRIE PROBLEMS ------------------

// 1. Longest Word with All Prefixes Present
string longestWordWithPrefixes(vector<string>& words) {
    Trie t;
    for (auto& w : words) t.insert(w);
    string ans;
    function<void(TrieNode*, string)> dfs = [&](TrieNode* node, string cur) {
        if (!node->isEnd && node != t.root) return;
        if (cur.size() > ans.size() || (cur.size() == ans.size() && cur < ans))
            ans = cur;
        for (auto& p : node->children)
            dfs(p.second, cur + p.first);
    };
    dfs(*(TrieNode**)(&t), ""); // hack: use root pointer
    return ans;
}

// 2. Autocomplete Suggestions
vector<string> autocomplete(vector<string>& dict, string prefix) {
    Trie t;
    for (auto& w : dict) t.insert(w);
    vector<string> res;
    function<void(TrieNode*, string)> dfs = [&](TrieNode* node, string cur) {
        if (node->isEnd) res.push_back(cur);
        for (auto& p : node->children) dfs(p.second, cur + p.first);
    };
    TrieNode* node = *(TrieNode**)(&t);
    for (char c : prefix) {
        if (!node->children[c]) return {};
        node = node->children[c];
    }
    dfs(node, prefix);
    return res;
}

// 3. Word Break Problem
bool wordBreak(string s, vector<string>& dict) {
    Trie t;
    for (auto& w : dict) t.insert(w);
    int n = s.size();
    vector<int> dp(n+1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        if (!dp[i]) continue;
        TrieNode* node = *(TrieNode**)(&t);
        for (int j = i; j < n; j++) {
            if (!node->children[s[j]]) break;
            node = node->children[s[j]];
            if (node->isEnd) dp[j+1] = 1;
        }
    }
    return dp[n];
}

// 4. Maximum XOR Pair
class TrieXOR {
    struct Node { Node* next[2]{}; };
    Node* root;
public:
    TrieXOR() { root = new Node(); }
    void insert(int num) {
        Node* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->next[bit]) node->next[bit] = new Node();
            node = node->next[bit];
        }
    }
    int maxXOR(int num) {
        Node* node = root;
        int ans = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->next[1-bit]) {
                ans |= (1 << i);
                node = node->next[1-bit];
            } else node = node->next[bit];
        }
        return ans;
    }
};

// 5. Replace Words with Root (LeetCode 648)
string replaceWords(vector<string>& dict, string sentence) {
    Trie t;
    for (auto& w : dict) t.insert(w);
    stringstream ss(sentence), out;
    string word;
    while (ss >> word) {
        TrieNode* node = *(TrieNode**)(&t);
        string prefix;
        bool replaced = false;
        for (char c : word) {
            if (!node->children[c]) break;
            prefix += c;
            node = node->children[c];
            if (node->isEnd) {
                out << prefix << " ";
                replaced = true;
                break;
            }
        }
        if (!replaced) out << word << " ";
    }
    string res = out.str();
    res.pop_back();
    return res;
}

// ------------------ MAIN ------------------
int main() {
    Trie t;
    t.insert("apple");
    cout << "Search apple: " << t.search("apple") << endl;
    cout << "Starts with app: " << t.startsWith("app") << endl;

    vector<string> words = {"w","wo","wor","worl","world","banana"};
    cout << "Longest word with prefixes: " << longestWordWithPrefixes(words) << endl;

    vector<string> dict = {"dog","deer","deal"};
    vector<string> autoC = autocomplete(dict, "de");
    cout << "Autocomplete for 'de': ";
    for (auto& s : autoC) cout << s << " ";
    cout << endl;

    vector<string> wbDict = {"leet","code"};
    cout << "Word break leetcode: " << wordBreak("leetcode", wbDict) << endl;

    TrieXOR tx;
    vector<int> arr = {3,10,5,25,2,8};
    for (int n : arr) tx.insert(n);
    int maxX = 0;
    for (int n : arr) maxX = max(maxX, tx.maxXOR(n));
    cout << "Max XOR pair: " << maxX << endl;

    vector<string> roots = {"cat","bat","rat"};
    string sent = "the cattle was rattled by the battery";
    cout << "Replace words: " << replaceWords(roots, sent) << endl;

    return 0;
}
