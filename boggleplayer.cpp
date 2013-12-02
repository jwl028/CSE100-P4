#include "boggleplayer.h"

using std::vector;
using std::set;
using std::string;

void buildLexicon(const set<string>& word_list)
{
  set<string> wordlist = word_list;
  Trie trie = new Trie();
  trie.build(wordlist);
}
   
void setBoard(unsigned int rows, unsigned int cols, string** diceArray)
{
}
 
bool getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
}

bool isInLexicon(const string& word_to_check)
{
}


vector<int> isOnBoard(const string& word_to_check)
{
}
 
void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
}

~BaseBogglePlayer()
{
}

