#include "boggleutil.h"

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
    for(int j = 0; j < currWord.length(); j++) {
      //First digit of first word is the root 
      if(j == 0 && wordCount == 1) {
        root = new TrieNode(currWord[j], false);
        currNode = root;
      }
      //Determines the placement of the first letter of the following words
      else if(j == 0 && wordCount != 1) {
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
          currNode = currNode->left;
        }
        //Create new node in Trie to the right if digit is larger 
        else if(currWord[j] > currNode->digit) {
          currNode->right = new TrieNode(currWord[j], false); 
          currNode = currNode->right;
        }
      }
      //Create nodes down the middle for the remaining digits
      else {
        currNode->middle = new TrieNode(currWord[j], false);
        currNode = currNode->middle;
        if((j+1) == currWord.length()) {
          currNode->end = true;
        }
      }
    }
  }
}


