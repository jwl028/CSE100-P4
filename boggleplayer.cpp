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
  setBoardCalled = true;
}

void BogglePlayer::clearBoard()
{
  for(unsigned int i=0; i < rows; i++) {
    delete[] boggleboard[i];
  }
  delete[] boggleboard;
}

void BogglePlayer::clearVisited()
{
  for(int i=0; i < rows; i++) {
    delete[] visited[i];
  }
  delete[] visited;
}
 
bool getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
}

bool isInLexicon(const string& word_to_check)
{
}


vector<int> isOnBoard(const string& word_to_check)
{
  clearVisited();
  vector<int> wordPath;
  if(setBoardCalled == false) {
    return 0;
  }
  visited = new bool*[rows];
  for(int r = 0; r < rows; r++) {
    visited[r] = new bool[cols];
  } 
  for(int a = 0; a < rows; a++){
    for(int b = 0; b < cols; b++) {
      visited[a][b] = false;
    }
  }
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      if(boggleboard[i][j] == word_to_check.substr(0,boggleboard[i][j].length()) && visited[i][j] == false) {
        wordPath = visitNeighbors(i,j, word_to_check.substr(boggleboard[i][j].length()), wordPath);   
      }
    }
  }
  return wordPath;	
  
}
 
vector<int> visitNeighbors(int row, int col, string substring, vector<int> neighborNodePaths)
{
  neighborNodePaths.push_back(row*rows + col);
  visited[row][col] = true;
  if(substring.empty()) {
    return neighborNodePaths;    
  }
  if(row-1 >= 0) {
    if(boggleboard[row-1][col] == substring.substr(0,boggleboard[row-1][col].length()) && visited[row-1][col] == false) {
      return visitNeighbors(row-1, col, substring.substr(boggleboard[row-1][col].length()),neighborNodePaths);
    }
  }
  if(row-1 >= 0 && col-1 >=0) {
    if(boggleboard[row-1][col-1] == substring.substr(0,boggleboard[row-1][col-1].length()) && visited[row-1][col-1] == false) {
      return visitNeighbors(row-1, col-1, substring.substr(boggleboard[row-1][col-1].length()),neighborNodePaths);
    }
  }
  if(row-1 >= && col+1 <=cols) {
    if(boggleboard[row-1][col+1] == substring.substr(0,boggleboard[row-1][col+1].length()) && visited[row-1][col+1] == false) {
      return visitNeighbors(row-1, col+1, substring.substr(boggleboard[row-1][col+1].length()),neighborNodePaths);
    }
  }
  if(col-1 >= 0) {
    if(boggleboard[row][col-1] == substring.substr(0,boggleboard[row][col-1].length()) && visited[row][col-1] == false) {
      return visitNeighbors(row, col-1, substring.substr(boggleboard[row][col-1].length()),neighborNodePaths);
    }
  }
  if(col+1 <=cols) {
    if(boggleboard[row][col+1] == substring.substr(0,boggleboard[row][col+1].length()) && visited[row][col+1] == false) {
      return visitNeighbors(row, col+1, substring.substr(boggleboard[row][col+1].length()),neighborNodePaths);
    }
  }
  if(row+1 <= rows) {
    if(boggleboard[row+1][col] == substring.substr(0,boggleboard[row+1][col].length()) && visited[row+1][col] == false) {
      return visitNeighbors(row+1, col, substring.substr(boggleboard[row+1][col].length()),neighborNodePaths);
    }
  }
  if(row+1 <=rows && col-1 >=0) {
    if(boggleboard[row+1][col-1] == substring.substr(0,boggleboard[row+1][col-1].length()) && visited[row+1][col-1] == false) {
      return visitNeighbors(row+1, col-1, substring.substr(boggleboard[row+1][col-1].length()),neighborNodePaths);
    }
  }
  if(row+1 <=rows && col+1 <=cols) {
    if(boggleboard[row+1][col+1] == substring.substr(0,boggleboard[row+1][col+1].length()) && visited[row+1][col+1] == false) {
      return visitNeighbors(row+1, col+1, substring.substr(boggleboard[row+1][col+1].length()),neighborNodePaths);
    }
  }
  return 0;
}

void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
}

~BogglePlayer()
{
}

