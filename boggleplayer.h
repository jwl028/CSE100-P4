//------------------------------------------------
// Filename: boggleplayer.h
// Author: Jimmy Li
// Date: 12/6/2013
// Rev-Date: 12/6/2013
//
// Description: Boggleplayer class 
//
//-------------------------------------------------

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include <set>
#include <vector>
#include <string>
#include "baseboggleplayer.h"
#include "boggleutil.h"

using std::vector;
using std::set;
using std::string;

class BogglePlayer : public BaseBogglePlayer {
  public:
    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
    ~BogglePlayer(); 

  private:
    unsigned int rows;
    unsigned int cols;
    string word;
    string **boggleboard;
    bool **visited;
    bool setBoardCalled;
    bool buildLexiconCalled;
    void clearBoard();
    void clearVisited();
    void visit(unsigned int i, unsigned int j, string substr, unsigned int min, set<string>* words);
    vector<int> visitNeighbors(unsigned int row, unsigned int col, string substring, vector<int> neighborNodePaths);
    Trie trie;
};

#endif // BOGGLEPLAYER_H
