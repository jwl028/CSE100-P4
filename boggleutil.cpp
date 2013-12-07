//------------------------------------------------
// Filename: boggleutil.cpp
// Author: Jimmy Li
// Date: 12/6/2013
// Rev-Date: 12/6/2013
//
// Description: Methods characteristic to Trie data structures 
//
//-------------------------------------------------
#include "boggleutil.h"
#include <iostream>

using namespace std;

//------------------------------------------------------------------
// build(const set<string>& word_list): Constructs a Trie tree 
//
// Input: const set<string>& word_list 
// Output: <none>
//-------------------------------------------------------------------

void Trie::build(const set<string>& word_list)
{
  int wordCount = 0;
  TrieNode* currNode;
  TrieNode* prevNode = 0;
  //Loops through each word in the lexicon
  for(set<string>::iterator i = word_list.begin(); i != word_list.end(); i++) {
    string currWord = *i;
    wordCount++;
    //Loops through each digit in each word
    for(int unsigned j = 0; j < currWord.length(); j++) {
      //First digit of first word is the root 
      if(j == 0 && wordCount == 1) {
        root = new TrieNode(currWord[j], false);
        if(currWord.length() == 1) {
          root->end = true;
        }
        currNode = root;
      }
      //Determines the placement of the first letter of the following words
      else if(j == 0 && wordCount != 1) {
        currNode = root;
        //Current node will point past the desired node
        while(currNode != NULL) {
          prevNode = currNode;
          //Traverse left if digit is smaller
          if(currWord[j] < currNode->digit) {
            currNode = currNode->left;
          }
          //Traverse right if digit is bigger
          else if(currWord[j] > currNode->digit) {
            currNode = currNode->right;
          }
          //Exit loop if digit is equal
          else {
            currNode = NULL;
          }
        }
        //Sets the current node back to the previous node for modification
        currNode = prevNode;
        //Create new node in Trie to the left if digit is smaller
        if(currWord[j] < currNode->digit) {
          currNode->left = new TrieNode(currWord[j], false);
          if(currWord.length() == 1){
            currNode->end = true;
          } 
          currNode = currNode->left;
        }
        //Create new node in Trie to the right if digit is larger 
        else if(currWord[j] > currNode->digit) {
          currNode->right = new TrieNode(currWord[j], false); 
          if(currWord.length() == 1) {
            currNode->end = true;
          }
          currNode = currNode->right;
        }
      }
      //Create nodes down the middle for the remaining digits
      else if(j>0) {
        if(currNode->middle == 0) {
          currNode->middle = new TrieNode(currWord[j],false);
          currNode = currNode->middle;
        }
        else {
          currNode = currNode->middle;
          while(currNode->digit != currWord[j]) {
            if(currWord[j] < currNode->digit) {
              if(currNode->left == 0) {
                currNode->left = new TrieNode(currWord[j],false);
              }
              currNode = currNode->left;
            }
            else if(currWord[j] > currNode->digit) {
              if(currNode->right == 0) {
                currNode->right = new TrieNode(currWord[j],false);
              }
              currNode = currNode->right;
            }
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------
// isPrefix(const string& word_to_check): Checks if prefix is valid in lexicon 
//
// Input: const string& word_to_check 
// Output: bool
//-------------------------------------------------------------------

bool Trie::isPrefix(const string& word_to_check)
{
  int i = 0;
  TrieNode* currNode = root;
  //Traverse from root of Trie all the way down until past the last node
  while(currNode != 0 && i < word_to_check.length()){
    if(currNode->digit == word_to_check[i]) {
      currNode = currNode->middle;
      i++;
    }
    else if(word_to_check[i] < currNode->digit) {
      currNode = currNode->left;
    }
    else if(word_to_check[i] > currNode->digit) {
      currNode = currNode->right;
    }
  }
  //If the prefix can be formed from the Trie then return true
  if(i == word_to_check.length()) {
    return true;
  }
  else {
    return false;
  }
}

//------------------------------------------------------------------
// find(const string& word_to_check): Checks if word is valid in lexicon 
//
// Input: const string& word_to_check
// Output: bool
//-------------------------------------------------------------------

bool Trie::find(const string& word_to_check)
{
  string wordRetrieved = "";
  int i = 0;
  TrieNode* currNode = root;
  //Traverse from root down the Trie
  while(currNode != 0 && i < word_to_check.length()) {
    //Returns true if word can be constructed
    if(wordRetrieved == word_to_check && currNode->end == true) {
      return true;
    }
    //Construct word based on Trie
    if(word_to_check[i] == currNode->digit) {
      wordRetrieved += word_to_check[i]; 
      currNode = currNode->middle;
      i++;
    }
    else if(word_to_check[i] > currNode->digit) {
      currNode = currNode->right;
    }
    else if(word_to_check[i] < currNode->digit) {
      currNode = currNode->left;
    }
  }    
  //If the word can be fully constructed then it should equate to the passed
  //in string
  return wordRetrieved == word_to_check;
}

TrieNode::~TrieNode()
{
}

Trie::~Trie()
{
}
