#include "boggleplayer.h"
#include "boggleutil.h"

using std::vector;
using std::set;
using std::string;

void BogglePlayer::buildLexicon(const set<string>& word_list)
{
  set<string> wordlist = word_list;
  Trie trie = new Trie();
  trie.build(wordlist);
}
   
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray)
{
  clearBoard();
  this->rows = rows;
  this->cols = cols;
  boggleboard = new string*[rows];
  for(unsigned int r = 0; r < rows; r++) {
    boggleboard[r] = new string[cols];
  }
  for(unsigned int i = 0; i < rows; i++) {
    for(unsigned int j = 0; j < cols; j++) {
      boggleboard[i][j] = diceArray[i][j];
    }
  }
}

void BogglePlayer::clearBoard()
{
  for(unsigned int i=0; i < rows; i++) {
    delete[] boggleboard[i];
  }
  delete[] boggleboard;
}
 
bool getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
}

bool isInLexicon(const string& word_to_check)
{
}


vector<int> isOnBoard(const string& word_to_check)
{
  vector<int> wordPath;

  
}
 
void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
}

~BogglePlayer()
{
}

