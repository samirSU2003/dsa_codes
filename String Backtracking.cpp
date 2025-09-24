#include <bits/stdc++.h>
using namespace std;

// 1. All Permutations of a String
void permuteStringUtil(string& s,int l,int r,vector<string>& res){
    if(l==r) { res.push_back(s); return; }
    for(int i=l;i<=r;i++){
        swap(s[l],s[i]);
        permuteStringUtil(s,l+1,r,res);
        swap(s[l],s[i]);
    }
}
vector<string> permuteString(string s){
    vector<string> res;
    permuteStringUtil(s,0,s.size()-1,res);
    return res;
}

// 2. All Subsequences of a String
void subseqStringUtil(string& s,int idx,string curr,vector<string>& res){
    if(idx==s.size()){ res.push_back(curr); return; }
    subseqStringUtil(s,idx+1,curr,res);
    subseqStringUtil(s,idx+1,curr+s[idx],res);
}
vector<string> subseqString(string s){
    vector<string> res;
    subseqStringUtil(s,0,"",res);
    return res;
}

// 3. Letter Case Permutations
void letterCaseUtil(string& s,int idx,vector<string>& res){
    if(idx==s.size()){ res.push_back(s); return; }
    letterCaseUtil(s,idx+1,res);
    if(isalpha(s[idx])){
        s[idx]^=32; // toggle case
        letterCaseUtil(s,idx+1,res);
        s[idx]^=32;
    }
}
vector<string> letterCasePermutation(string s){
    vector<string> res;
    letterCaseUtil(s,0,res);
    return res;
}

// 4. Palindrome Partitioning
bool isPalindrome(const string& s,int l,int r){
    while(l<r) if(s[l++]!=s[r--]) return false;
    return true;
}
void palindromePartitionUtil(string& s,int idx,vector<string>& path,vector<vector<string>>& res){
    if(idx==s.size()){ res.push_back(path); return; }
    for(int i=idx;i<s.size();i++){
        if(isPalindrome(s,idx,i)){
            path.push_back(s.substr(idx,i-idx+1));
            palindromePartitionUtil(s,i+1,path,res);
            path.pop_back();
        }
    }
}
vector<vector<string>> palindromePartition(string s){
    vector<vector<string>> res;
    vector<string> path;
    palindromePartitionUtil(s,0,path,res);
    return res;
}

// 5. Word Search on Grid (Boggle Solver)
bool dfsWordGrid(vector<vector<char>>& board,string& word,int i,int j,int idx){
    if(idx==word.size()) return true;
    if(i<0||j<0||i>=board.size()||j>=board[0].size()||board[i][j]!=word[idx]) return false;
    char c=board[i][j]; board[i][j]='#';
    bool found=dfsWordGrid(board,word,i+1,j,idx+1)||
               dfsWordGrid(board,word,i-1,j,idx+1)||
               dfsWordGrid(board,word,i,j+1,idx+1)||
               dfsWordGrid(board,word,i,j-1,idx+1);
    board[i][j]=c;
    return found;
}
bool existWordGrid(vector<vector<char>>& board,string word){
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[0].size();j++)
            if(dfsWordGrid(board,word,i,j,0)) return true;
    return false;
}

// ------------------ MAIN ------------------
int main(){
    string s="abc";
    vector<string> perm=permuteString(s);
    cout<<"Permutations: "; for(auto &x:perm) cout<<x<<" "; cout<<endl;

    vector<string> subseq=subseqString(s);
    cout<<"Subsequences: "; for(auto &x:subseq) cout<<x<<" "; cout<<endl;

    string s2="a1b2";
    vector<string> lc=letterCasePermutation(s2);
    cout<<"Letter Case Permutations: "; for(auto &x:lc) cout<<x<<" "; cout<<endl;

    string s3="aab";
    vector<vector<string>> pp=palindromePartition(s3);
    cout<<"Palindrome Partitions:"<<endl;
    for(auto &v:pp){ for(auto &w:v) cout<<w<<" "; cout<<endl; }

    vector<vector<char>> board={{'A','B','C','E'},
                                {'S','F','C','S'},
                                {'A','D','E','E'}};
    cout<<"Word 'ABCCED' exists: "<<existWordGrid(board,"ABCCED")<<endl;

    return 0;
}
