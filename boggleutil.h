/*****************************P3 FILE HEADER********************************/
/* Name: Pin Chu A98041513, Jessica Tran A11358012
* Instructor: Debashis Sahoo
* Filename: boggleutil.h
* Date: 06/01/2015 
* Description:
* This files implement different classes including the individual tile for
* the boggleboard, trie data structure for the lexicon, and the node class 
* for the trie.
**/
/***************************************************************************/




// Kyle Barron-Kraus <kbarronk>

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <cctype>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <set>

using namespace std;

/**
 * Class that represents a position on the Boggle Board.
 *
 * Each position contains its sanitized string that represents the
 * characters on that board position, as well as a boolean that
 * marks the board position as visited by a given search algorithm.
 */
class BoardPos {
  public:
    /**
     * Constructs a BoardPos with the given text. Text must have been
     * sanitized by the caller.
     */
    BoardPos(const std::string &text);

    /**
     * Destructor
     */ 
    ~BoardPos();

    /**
     * Returns the characters on this BoardPos.
     */
    const std::string &getText() const;
    
    /**
     * Returns whether this BoardPos has been visited or not.
     */
    bool getVisited() const;

    /**
     * Sets whether this BoardPos has been visited or not.
     */
    void setVisited(bool visited);

    /**
     * Returns whether this BoardPos has been visited or not.
     */
    bool getRevisited() const;

    /**
     * Sets whether this BoardPos has been visited or not.
     */
    void setRevisited(bool revisited);


  private:
    /**
     * The characters that this BoardPos contains.
     */
    const std::string text;

    /**
     * Whether this BoardPos has been visited or not.
     */
    bool visited;

    /** 
     * whether this BoardPos has been revisited
     */
    bool revisited;

};

/**
 * class for nodes inside the Trie class
 */
class Node{
  public:
    /**
     * constructor for node
     */
    Node();

    /**
     * destructor for node
     */
    ~Node();


    /**
     * whether or not this is a trie key
     */
    bool end;

    /**
     * vector of the 26 alphabet characters
     * aka pointers children nodes
     */
    std::vector<Node*> children;


};

/**
 * Implement class for Trie
 */
class Trie{
  public:
    /**
     * constructor for Trie which holds lexicon
     */
    Trie();

    /**
     * Trie destructor
     */
    ~Trie();

    /**
     * used to insert a word into the lexicon
     */
    bool insert(const std::string& key);

    /**
     * used to find a word in the lexicon
     */
    bool find(const std::string& key);

    /*used to prune lexicon and speed up getAllValidWords*/
    bool isPrefix(const std::string& key); 


    /* accessor method for trie root*/
    Node * getRoot();

  private:
    /**
     * Trie root
     */
    Node * root;

    /* helper postorder recursive function for destructor*/
    void deleteAllNodes(Node *&current);
};



#endif // BOGGLEUTIL_H
