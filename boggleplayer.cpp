//------------------------------------------------
// Filename: boggleplayer.cpp
// Author: Jimmy Li
// Date: 12/6/2013
// Rev-Date: 12/6/2013
//
// Description: Boggleplayer methods 
//
//-------------------------------------------------

#include "boggleplayer.h"
#include "boggleutil.h"
#include <iostream>
#include <cctype>
#include <algorithm>

using std::vector;
using std::set;
using std::string;

//------------------------------------------------------------------
// buildLexicon(const set<string>& word_list): Constructs the Lexicon 
//                                             using a Trie data structure 
//
// Input: const set<string>& word_list 
// Output: <none>
//-------------------------------------------------------------------

void BogglePlayer::buildLexicon(const set<string>& word_list)
{
  set<string> wordlist = word_list;
  trie.build(wordlist);
  buildLexiconCalled = true;
}

//------------------------------------------------------------------
// setBoard(unsigned int rows, unsigned int cols, string** diceArray):
// Constructs the boggleboard. 
//
// Input: unsigned int rows, unsigned int cols, string** diceArray 
// Output: <none>
//-------------------------------------------------------------------

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
      string lowercase = diceArray[i][j];
      std::transform(lowercase.begin(),lowercase.end(),lowercase.begin(),::tolower);
      boggleboard[i][j] = lowercase;
    }
  }
  setBoardCalled = true;
}

//------------------------------------------------------------------
// clearBoard(): Deletes the boggleboard
//
// Input: <none> 
// Output: <none>
//-------------------------------------------------------------------

void BogglePlayer::clearBoard()
{
  for(unsigned int i=0; i < rows; i++) {
    delete[] boggleboard[i];
  }
  delete[] boggleboard;
}

//------------------------------------------------------------------
// clearVisited(): Deletes the boolean tracking node visits 
//
// Input: <none> 
// Output: <none>
//-------------------------------------------------------------------

void BogglePlayer::clearVisited()
{
  for(int unsigned i=0; i < rows; i++) {
    delete[] visited[i];
  }
  delete[] visited;
}

//------------------------------------------------------------------
// getAllValidWords(unsigned int minimum_word_length, set<string>* words): 
// Compiles all the words that can be made on the board that are also valid
// in the lexicon
// Input: unsigned int minimum_word_length, set<string>* words
// Output: bool
//-------------------------------------------------------------------

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
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
      visit(i, j, boggleboard[i][j], minimum_word_length, words); 
    }
  }
  clearVisited();
  if(setBoardCalled == true && buildLexiconCalled == true) {
    return true;
  }
  else {
    return false;
  }

}

//------------------------------------------------------------------
// visit(unsigned int row, unsigned int col, string substr, unsigned int minimum         _word_length, set<string>* words): 
// Compiles all the words that can be made on the board that are also valid
// in the lexicon (Helper method)
// Input: unsigned int row, unsigned int col, string substr, unsigned int minimu          m_word_length, set<string>* words
// Output: bool
//-------------------------------------------------------------------

void BogglePlayer::visit(unsigned int row, unsigned int col, string substr, unsigned int min, set<string>* words) 
{
  string substring = substr;
  visited[row][col] = true;
  if(trie.isPrefix(substring) == false) {
    visited[row][col] = false;
    return;
  }
  if(substring.length() >= min) {
    if(isInLexicon(substring) == true) {
      words->insert(substring);
    }
  }
  if(row >= 1) {
    if(visited[row-1][col] == false) {
      visit(row-1, col, substring+boggleboard[row-1][col],min, words);
    }
  }
  if(row >= 1 && col >=1) {
    if(visited[row-1][col-1] == false) {
      visit(row-1, col-1, substring+(boggleboard[row-1][col-1]),min, words);
    }
  }
  if(row >= 1 && col+1 <cols) {
    if(visited[row-1][col+1] == false) {
      visit(row-1, col+1, substring+(boggleboard[row-1][col+1]),min, words);
    }
  }
  if(col >= 1) {
    if(visited[row][col-1] == false) {
      visit(row, col-1, substring+boggleboard[row][col-1],min,words);
    }
  }
  if(col+1 < cols) {
    if(visited[row][col+1] == false) {
      visit(row, col+1, substring+(boggleboard[row][col+1]),min, words);
    }
  }
  if(row+1 < rows) {
    if(visited[row+1][col] == false) {
      visit(row+1, col, substring+(boggleboard[row+1][col]),min, words);
    }
  }
  if(row+1 < rows && col >=1) {
    if(visited[row+1][col-1] == false) {
      visit(row+1, col-1, substring+(boggleboard[row+1][col-1]),min, words);
    }
  }
  if(row+1 <rows && col+1 <cols) {
    if(visited[row+1][col+1] == false) {
      visit(row+1, col+1, substring+(boggleboard[row+1][col+1]),min, words);
    }
  }
  visited[row][col] = false;

}



//------------------------------------------------------------------
//isInLexicon(const string* word_to_check): Checks if word is in Lexicon 
//
// Input: const string& word_to_check 
// Output: bool
//-------------------------------------------------------------------
bool BogglePlayer::isInLexicon(const string& word_to_check)
{
  if(buildLexiconCalled == false) {
    return false;
  }
  return trie.find(word_to_check);
}

//------------------------------------------------------------------
//isOnBoard(const string& word_to_check): Checks if word is on the board 
//
// Input: const string& word_to_check 
// Output: vector<int> 
//-------------------------------------------------------------------

vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
{
  word = word_to_check; 
  std::transform(word.begin(),word.end(),word.begin(),::tolower);
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
      if(boggleboard[i][j] == word.substr(0,boggleboard[i][j].length()) && visited[i][j] == false) {
        wordPath = visitNeighbors(i,j, word.substr(boggleboard[i][j].length()), wordPath);
        wordPath.pop_back();
        if(!wordPath.empty()){
          clearVisited();
          return wordPath;
        }   
      }
    }
  }
  clearVisited();
  return wordPath;	
}
 
//------------------------------------------------------------------
// visitNeighbors(unsigned int row, unsigned int col, string substring, 
//                vector<int> neighborNodePaths): Helper method that checks the //                                                neighbors for a valid path 
//
// Input: unsigned int row, unsigned int col, string substring, vector<int> 
//        neighborNodePaths
// Output: vector<int> 
//-------------------------------------------------------------------

vector<int> BogglePlayer::visitNeighbors(unsigned int row, unsigned int col, string substring, vector<int> neighborNodePaths)
{
  vector<int> word_path;
  neighborNodePaths.push_back(row*rows + col);
  word_path = neighborNodePaths;
  visited[row][col] = true;
  if(substring.empty()) {
   neighborNodePaths.push_back(-1);
    return neighborNodePaths;    
  }
  if(row >= 1) {
    if(boggleboard[row-1][col] == substring.substr(0,boggleboard[row-1][col].length()) && visited[row-1][col] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row-1, col, substring.substr(boggleboard[row-1][col].length()),neighborNodePaths);
    }
  }
  if(row >= 1 && col >=1) {
    if(boggleboard[row-1][col-1] == substring.substr(0,boggleboard[row-1][col-1].length()) && visited[row-1][col-1] == false && word_path.back() != -1 ) {
      word_path = visitNeighbors(row-1, col-1, substring.substr(boggleboard[row-1][col-1].length()),neighborNodePaths);
    }
  }
  if(row >= 1 && col+1 <cols) {
    if(boggleboard[row-1][col+1] == substring.substr(0,boggleboard[row-1][col+1].length()) && visited[row-1][col+1] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row-1, col+1, substring.substr(boggleboard[row-1][col+1].length()),neighborNodePaths);
    }
  }
  if(col >= 1) {
    if(boggleboard[row][col-1] == substring.substr(0,boggleboard[row][col-1].length()) && visited[row][col-1] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row, col-1, substring.substr(boggleboard[row][col-1].length()),neighborNodePaths);
    }
  }
  if(col+1 < cols) {
    if(boggleboard[row][col+1] == substring.substr(0,boggleboard[row][col+1].length()) && visited[row][col+1] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row, col+1, substring.substr(boggleboard[row][col+1].length()),neighborNodePaths);
    }
  }
  if(row+1 < rows) {
    if(boggleboard[row+1][col] == substring.substr(0,boggleboard[row+1][col].length()) && visited[row+1][col] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row+1, col, substring.substr(boggleboard[row+1][col].length()),neighborNodePaths);
    }
  }
  if(row+1 < rows && col >=1) {
    if(boggleboard[row+1][col-1] == substring.substr(0,boggleboard[row+1][col-1].length()) && visited[row+1][col-1] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row+1, col-1, substring.substr(boggleboard[row+1][col-1].length()),neighborNodePaths);
    }
  }
  if(row+1 <rows && col+1 <cols) {
    if(boggleboard[row+1][col+1] == substring.substr(0,boggleboard[row+1][col+1].length()) && visited[row+1][col+1] == false && word_path.back() != -1) {
      word_path = visitNeighbors(row+1, col+1, substring.substr(boggleboard[row+1][col+1].length()),neighborNodePaths);
    }
  }
  if(word_path.back() != -1) {
    visited[row][col] = false;
    word_path.pop_back();
  }
  return word_path;
}

//------------------------------------------------------------------
// getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols): //                Creates a custom board 
//
// Input: string** &new_board, unsigned int *rows, unsigned int *cols
// Output: <none>
//-------------------------------------------------------------------

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
  string custom1[] =  {"t","e","s","t"}; 
  string custom2[] =  {"a","b","c","d"};
  string custom3[] =  {"a","b","c","d"};
  string custom4[] =  {"a","b","c","d"};
  new_board = new string*[4];
  for(unsigned int r=0; r < 4; r++){
    new_board[r] = new string[4];
  }
  for(int j =0; j <4; j++){
    new_board[0][j] = custom1[j]; 
    new_board[1][j] = custom2[j];
    new_board[2][j] = custom3[j];
    new_board[3][j] = custom4[j];
  }
}

BogglePlayer::~BogglePlayer()
{
}

