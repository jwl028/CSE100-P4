#include "boggleplayer.h"
#include "boggleutil.h"

using std::vector;
using std::set;
using std::string;


void BogglePlayer::buildLexicon(const set<string>& word_list)
{
  //set<string> wordlist = word_list;
  //Trie trie = new Trie();
  //trie.build(wordlist);
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
  for(int unsigned i=0; i < rows; i++) {
    delete[] visited[i];
  }
  delete[] visited;
}


bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
}



bool BogglePlayer::isInLexicon(const string& word_to_check)
{
}


vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
{
  clearVisited();
  vector<int> wordPath;
  if(setBoardCalled == false) {
    return wordPath;
  }
  visited = new bool*[rows];
  for(unsigned int r = 0; r < rows; r++) {
    visited[r] = new bool[cols];
  } 
  for(unsigned int a = 0; a < rows; a++){
    for(unsigned int b = 0; b < cols; b++) {
      visited[a][b] = false;
    }
  }
  for(unsigned int i = 0; i < rows; i++) {
    for(unsigned int j = 0; j < cols; j++) {
      if(boggleboard[i][j] == word_to_check.substr(0,boggleboard[i][j].length()) && visited[i][j] == false) {
        wordPath = visitNeighbors(i,j, word_to_check.substr(boggleboard[i][j].length()), wordPath);   
      }
    }
  }
  return wordPath;	
  
}
 
vector<int> BogglePlayer::visitNeighbors(unsigned int row, unsigned int col, string substring, vector<int> neighborNodePaths)
{
  neighborNodePaths.push_back(row*rows + col);
  visited[row][col] = true;
  if(substring.empty()) {
    return neighborNodePaths;    
  }
  if(row >= 1) {
    if(boggleboard[row-1][col] == substring.substr(0,boggleboard[row-1][col].length()) && visited[row-1][col] == false) {
      return visitNeighbors(row-1, col, substring.substr(boggleboard[row-1][col].length()),neighborNodePaths);
    }
  }
  if(row >= 1 && col >=1) {
    if(boggleboard[row-1][col-1] == substring.substr(0,boggleboard[row-1][col-1].length()) && visited[row-1][col-1] == false) {
      return visitNeighbors(row-1, col-1, substring.substr(boggleboard[row-1][col-1].length()),neighborNodePaths);
    }
  }
  if(row >= 1 && col+1 <=cols) {
    if(boggleboard[row-1][col+1] == substring.substr(0,boggleboard[row-1][col+1].length()) && visited[row-1][col+1] == false) {
      return visitNeighbors(row-1, col+1, substring.substr(boggleboard[row-1][col+1].length()),neighborNodePaths);
    }
  }
  if(col >= 1) {
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
  if(row+1 <=rows && col >=1) {
    if(boggleboard[row+1][col-1] == substring.substr(0,boggleboard[row+1][col-1].length()) && visited[row+1][col-1] == false) {
      return visitNeighbors(row+1, col-1, substring.substr(boggleboard[row+1][col-1].length()),neighborNodePaths);
    }
  }
  if(row+1 <=rows && col+1 <=cols) {
    if(boggleboard[row+1][col+1] == substring.substr(0,boggleboard[row+1][col+1].length()) && visited[row+1][col+1] == false) {
      return visitNeighbors(row+1, col+1, substring.substr(boggleboard[row+1][col+1].length()),neighborNodePaths);
    }
  }
  vector<int> emptyVector;
  return emptyVector;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
}


