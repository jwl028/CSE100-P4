#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

class Trie 
{
  private:
    TrieNode* root;

  public:
    Trie() : root(0) { };
    void build (const set<string>& word_list);
};

class TrieNode
{
  public:
    char digit;
    bool end;
    TrieNode* left;
    TrieNode* right;
    TrieNode* middle;

    TrieNode(char digit, 
             bool end, 
             TrieNode* left = 0, 
             TrieNode* right = 0, 
             TrieNode* middle = 0) 
      : digit(digit), end(end), left(left), right(right), middle(middle) { }
};
