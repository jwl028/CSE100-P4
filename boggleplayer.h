#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include <set>
#include <vector>
#include <string>
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
    ~BogglePlayer() {}

  private:
    unsigned int rows;
    unsigned int cols;
    string **boggleboard;
    bool **visited;
    bool setBoardCalled = false;
    void clearBoard();
    void clearVisited();
    vector<int> visitNeighbors(int row, int col, string substring, vector<int> neighborNodePaths)
};

#endif // BOGGLEPLAYER_H
