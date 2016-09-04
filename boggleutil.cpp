/*****************************P3 FILE HEADER********************************/
/* Name: Pin Chu A98041513, Jessica Tran A11358012
* Instructor: Debashis Sahoo
* Filename: boggleutil.cpp
* Date: 06/01/2015 
* Description:
* This files implement different classes including the individual tile for
* the boggleboard, trie data structure for the lexicon, and the node class 
* for the trie.
**/
/***************************************************************************/




#include "boggleutil.h"
#include<iostream>
#define OFFSET 97
#define ALPHABET 26


/**
  * Constructs a BoardPos with the given text. Text must have been
  * sanitized by the caller.
  */
BoardPos::BoardPos(const std::string &text) : text(text){

   this->visited = false;
   this->revisited = false;
}

BoardPos::~BoardPos(){}

/**
 * Returns the characters on this BoardPos.
 */
const std::string &BoardPos::getText() const{
   
   return this->text;
}

/**
 * Returns whether this BoardPos has been visited or not.
 */
bool BoardPos::getVisited() const{

   return this->visited; 
}

/**
 * Sets whether this BoardPos has been visited or not.
 */
void BoardPos::setVisited(bool visited){
   
   this->visited = visited;
}

/**
 * Returns whether this BoardPos has been visited or not.
 */
bool BoardPos::getRevisited() const{

   return this->revisited; 
}

/**
 * Sets whether this BoardPos has been visited or not.
 */
void BoardPos::setRevisited(bool revisited){
   
   this->revisited = revisited;
}


/**
 * constructor for Trie which holds lexicon
 */
Trie::Trie(){
  root = new Node();
}

/**
 * Trie destructor
 */
Trie::~Trie(){
  deleteAllNodes(root);
}

/**
 * Helper method to recursively delete nodes in Trie
 * using postorder traversal
 */
void Trie::deleteAllNodes(Node *&current){
  //if node is null then return
  if (current == NULL){return;}
  for(int i = (ALPHABET-1); i >= 0; i-- ){
      deleteAllNodes(current->children[i]);
  }
  //visit
  delete current;
  current = NULL;
}

/**
 * used to insert a word into the lexicon
 */
bool Trie::insert(const string& key){
  unsigned int i = 0;
  Node * current = root;
  int digit = 0;

  while( i < key.length()){
    //get the char at the current index of word
    digit = (int) key[i];
    //assign the value and insert if not already in trie 
    if(current->children[digit - OFFSET] == NULL){
      current->children[digit - OFFSET] = new Node();
    }
    current = current->children[digit - OFFSET];
    i++;
  }

  //mark that the end is true for end of word
  current -> end = true;

  return true;
}

/**
 * used to find a word in the lexicon
 */
bool Trie::find(const string& key){

  Node * current = root; //root node of trie 
  unsigned int i = 0;
  while(i <= key.length()){
    //return false if node is not there or i out of bounds
    if(current == NULL || i > key.length()){return false;}
    //if end is marked true and i is word length we've found it!
    if(current->end && i == key.length() ){return true;}
    if(i >= key.length()){return false;}
    int digit = (int)key[i]; //get next letter in word

    //go to node corresponding to letter
    current = current->children[digit - OFFSET];
    i++;
  }

  return false; 
}

/**
 * used to find a word in the lexicon
 */
bool Trie::isPrefix(const string& key){

  Node * current = root; //root node of trie 
  unsigned int i = 0;
  while(i < key.length()){
    //if node for letter not there, no word with this beginning sequence exists
    if(current == NULL){return false;}

    int digit = (int)key[i];
    current = current->children[digit - OFFSET];
    i++;
  }

  return true; 
}



/* accessor for tie root*/
Node* Trie:: getRoot(){
  return this->root;
}

/**
 * constructor for node
 */
Node::Node(): children(ALPHABET, NULL){
  end = false;
}

/**
 * destructor for node
 */
Node::~Node(){

}


