#include "boggleplayer.h"
#include "boggleutil.h"
#include <iostream>
#include <cctype>
#include <algorithm>

using std::vector;
using std::set;
using std::string;


void BogglePlayer::buildLexicon(const set<string>& word_list)
{
  set<string> wordlist = word_list;
  Trie* trie = new Trie();
  trie->build(wordlist);
  std::cout << "TRIE BUILT!" << std::endl;
}


void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray)
{
  //clearBoard();
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
      std::cout << boggleboard[i][j] << " ";
    }
     std::cout << std::endl;
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
  //return trie->find(word_to_check);
  /*string wordRetrieved = 0;
  int i = 0;
  TrieNode* currNode = root;
  while(currNode != NULL) {
    if(word_to_check[i] == currNode->digit && currNode->end == false) {
      wordRetrieved += word_to_check[i]; 
      currNode = currNode->middle;
      i++;
    }
    else if(word_to_check[i] > currNode->digit && currNode->end ==false) {
      currNode = currNode->right;
    }
    else if(word_to_check[i] < currNode->digit && currNode->end ==false) {
      currNode = currNode->left;
    }
  }    
  return wordRetrieved == word_to_check;
  */
}


vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
{
  //clearVisited();
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
        std::cout<<"running" <<std::endl;
        wordPath = visitNeighbors(i,j, word.substr(boggleboard[i][j].length()), wordPath);
        wordPath.pop_back();
        if(!wordPath.empty()){
          return wordPath;
        }   
      }
    }
  }
  return wordPath;	
  
}
 
vector<int> BogglePlayer::visitNeighbors(unsigned int row, unsigned int col, string substring, vector<int> neighborNodePaths)
{
  //bool wordFound = false;
  std::cout<<"row:" <<row << "col" << col<< std::endl;
  vector<int> word_path;
  std::cout<<"here"<< std::endl;
  neighborNodePaths.push_back(row*rows + col);
  word_path = neighborNodePaths;
  std::cout<<neighborNodePaths.back()<< std::endl;
  std::cout<<"string: " << substring<< std::endl;
  visited[row][col] = true;
 // std::cout<<boggleboard[row+1][col] << std::endl;
  if(substring.empty()) {
   // wordFound = true;
   neighborNodePaths.push_back(-1);
  std::cout<<"empty"<< std::endl;
    return neighborNodePaths;    
  }
  if(row >= 1) {
    if(boggleboard[row-1][col] == substring.substr(0,boggleboard[row-1][col].length()) && visited[row-1][col] == false && word_path.back() != -1) {
      std::cout<<"up"<<std::endl;
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
      std::cout<<"right went through" << std::endl;
      word_path = visitNeighbors(row, col+1, substring.substr(boggleboard[row][col+1].length()),neighborNodePaths);
    }
  }
  if(row+1 < rows) {
    if(boggleboard[row+1][col] == substring.substr(0,boggleboard[row+1][col].length()) && visited[row+1][col] == false && word_path.back() != -1) {
      std::cout<<"bottom went through" << std::endl;
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
      std::cout<<"diag rightwent through" << std::endl;
      std::cout<<"substring:" << substring << std::endl;
      word_path = visitNeighbors(row+1, col+1, substring.substr(boggleboard[row+1][col+1].length()),neighborNodePaths);
    }
  }
  //vector<int> emptyVector;
std::cout<<"end-row= "<< row << "col= " <<col<<std::endl;
std::cout <<"word_path_size" << word_path.size() << "wordlength " <<word.length() << std::endl;
  if(word_path.back() != -1) {
    visited[row][col] = false;
    word_path.pop_back();
  }
  std::cout << "wordback: " << word_path.back() << std::endl;
  return word_path;
}


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

