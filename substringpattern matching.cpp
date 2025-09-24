#include <bits/stdc++.h>
using namespace std;

// Naive substring search
vector<int> naiveSearch(const string &text, const string &pattern) {
	vector<int> positions;
	int n = text.size(), m = pattern.size();
	for (int i = 0; i <= n - m; i++) {
		int j = 0;
		while (j < m && text[i + j] == pattern[j]) j++;
		if (j == m) positions.push_back(i);
	}
	return positions;
}

// KMP algorithm
vector<int> computeLPS(const string &pattern) {
	int m = pattern.size();
	vector<int> lps(m, 0);
	int len = 0, i = 1;
	while (i < m) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		} else {
			if (len != 0) len = lps[len - 1];
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
	return lps;
}

vector<int> KMPSearch(const string &text, const string &pattern) {
	vector<int> positions;
	vector<int> lps = computeLPS(pattern);
	int n = text.size(), m = pattern.size();
	int i = 0, j = 0;
	while (i < n) {
		if (pattern[j] == text[i]) {
			i++;
			j++;
		}
		if (j == m) {
			positions.push_back(i - j);
			j = lps[j - 1];
		}
		else if (i < n && pattern[j] != text[i]) {
			if (j != 0) j = lps[j - 1];
			else i++;
		}
	}
	return positions;
}

// Rabin-Karp algorithm
vector<int> rabinKarp(const string &text, const string &pattern, int prime = 101) {
	vector<int> positions;
	int n = text.size(), m = pattern.size();
	if (m > n) return positions;

	long long pHash = 0, tHash = 0, h = 1;
	for (int i = 0; i < m - 1; i++) h = (h * 256) % prime;

	for (int i = 0; i < m; i++) {
		pHash = (256 * pHash + pattern[i]) % prime;
		tHash = (256 * tHash + text[i]) % prime;
	}

	for (int i = 0; i <= n - m; i++) {
		if (pHash == tHash) {
			int j = 0;
			while (j < m && text[i + j] == pattern[j]) j++;
			if (j == m) positions.push_back(i);
		}
		if (i < n - m) {
			tHash = (256 * (tHash - text[i] * h) + text[i + m]) % prime;
			if (tHash < 0) tHash += prime;
		}
	}
	return positions;
}

// Count occurrences of a substring (using naive)
int countOccurrences(const string &text, const string &pattern) {
	return naiveSearch(text, pattern).size();
}

// Longest common prefix of two strings
string longestCommonPrefix(const string &a, const string &b) {
	int n = min(a.size(), b.size()), i = 0;
	while (i < n && a[i] == b[i]) i++;
	return a.substr(0, i);
}

// Testing
int main() {
	string text = "ababcababcabc";
	string pattern = "abc";

	cout << "Naive Search positions: ";
	for (int pos : naiveSearch(text, pattern)) cout << pos << " ";
	cout << "\n";

	cout << "KMP Search positions: ";
	for (int pos : KMPSearch(text, pattern)) cout << pos << " ";
	cout << "\n";

	cout << "Rabin-Karp Search positions: ";
	for (int pos : rabinKarp(text, pattern)) cout << pos << " ";
	cout << "\n";

	cout << "Count of occurrences: " << countOccurrences(text, pattern) << "\n";

	string a = "flower", b = "flow";
	cout << "Longest Common Prefix of '" << a << "' and '" << b << "': " << longestCommonPrefix(a, b) << "\n";

	return 0;
}
