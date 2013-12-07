#include "boggleutil.h"
#include <iostream>

using namespace std;


void Trie::build(const set<string>& word_list)
{
  cout << "Building" << endl;
  int wordCount = 0;
  TrieNode* currNode;
  TrieNode* prevNode = 0;
  //Loops through each word in the lexicon
  for(set<string>::iterator i = word_list.begin(); i != word_list.end(); i++) {
    string currWord = *i;
    //cout << "current word = " << currWord << endl;
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
          cout << "Root :" << root->digit << endl;
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
        //cout << "currWord: " << currWord[j] << " currDigit: " <<currNode->digit <<endl;
        //Create new node in Trie to the left if digit is smaller
        if(currWord[j] < currNode->digit) {
          currNode->left = new TrieNode(currWord[j], false);
          if(currWord.length() == 1){
            currNode->end = true;
          } 
          currNode = currNode->left;
          //cout << "LeftNode " << currNode->digit << endl;
        }
        //Create new node in Trie to the right if digit is larger 
        else if(currWord[j] > currNode->digit) {
          currNode->right = new TrieNode(currWord[j], false); 
          if(currWord.length() == 1) {
            currNode->end = true;
          }
          currNode = currNode->right;
          cout << "RightNode" << currNode->digit << endl;
        }
      }
      //Create nodes down the middle for the remaining digits
      else if(j>0) {
        if(currNode->middle == 0) {
          currNode->middle = new TrieNode(currWord[j],false);
          currNode = currNode->middle;
        }
        else {
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
                currNode = currNode->left;
            }
            else {
              currNode = currNode->middle;
            }
          }
        }
      }
/*
        if(j == 1) {
          prevNode = currNode;
          currNode = currNode->middle;
        }
        while(currNode != 0) {
          prevNode = currNode;
          if(currNode->digit == currWord[j]) {
            currNode = currNode->middle;
          }
          else if(currWord[j] < currNode->digit) {
            currNode = currNode->left;
          }
          else {
            currNode = currNode->right;
          }
        }
        currNode = prevNode;
        if(currWord[j] < currNode->digit) {
          currNode->left = new TrieNode(currWord[j], false);
        }
        else if(currWord[j] > currNode->digit) {
          currNode->right = new TrieNode(currWord[j], false);
        }
        else {
          currNode->middle = new TrieNode(currWord[j], false);
        cout << "currentNode = " << currNode->digit << endl;
        }
       // cout << "currentNode = " << currNode->digit << endl;
        if((j+1) == currWord.length()) {
          currNode->end = true;
        }
      //  else {
       //   currNode->middle = new TrieNode(currWord[j], false);

        
      //  }
*/

/*
        if(currNode->middle == 0) {
          currNode->middle = new TrieNode(currWord[j], false);
          currNode = currNode->middle;
          //cout << "MiddleNode: " << currNode->digit << endl;
          if((j+1) == currWord.length()) {
            currNode->end = true;
            cout <<"END BIT" << endl;
          }
        }
        else if(currNode->middle->digit == currWord[j]) {
*/          
      }
    }
  }
}


bool Trie::find(const string& word_to_check)
{
  string wordRetrieved = "";
  int i = 0;
  TrieNode* currNode = root;
  cout << "root is" << currNode->digit << endl;
  cout << "currNodeEnd = " << currNode->end <<endl;
  cout << word_to_check[0] << endl;
  while(currNode != 0 && i < word_to_check.length()) {
  cout << "digit :" << currNode->digit << endl;
    if(wordRetrieved == word_to_check && currNode->end == true) {
      return true;
    }
    if(word_to_check[i] == currNode->digit) {
      wordRetrieved += word_to_check[i]; 
      cout << "word = " << wordRetrieved << endl;
      currNode = currNode->middle;
      i++;
    }
    else if(word_to_check[i] > currNode->digit) {
      cout << "rightshift word " << endl;
      currNode = currNode->right;
    }
    else if(word_to_check[i] < currNode->digit) {
      currNode = currNode->left;
      cout << "leftshift word" << endl;
    }
  }    
  return false;
}

TrieNode::~TrieNode()
{
}

Trie::~Trie()
{
}
