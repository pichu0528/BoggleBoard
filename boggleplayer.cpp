/*****************************P3 FILE HEADER********************************/
/* Name: Pin Chu A98041513, Jessica Tran A11358012
* Instructor: Debashis Sahoo
* Filename: boggleplayer.cpp
* Date: 06/01/2015 
* Description:
* This file has all the functions to build the boggleboard, lexicon, and 
* implementation of game-play. 
* **/
/***************************************************************************/






#include "boggleplayer.h"
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

   /**
     * Constructs a BogglePlayer with an uninitialized board and lexicon.
     * Both must be initialized with data before use.
     */
    BogglePlayer::BogglePlayer(){
        rows = cols = 0;
        board_built = false;
        lexicon = NULL;
    }

   /**
    * Destructor
    */
    BogglePlayer::~BogglePlayer(){
      delete lexicon;
      lexicon = NULL;

    }

    /**
     * Initializes the BogglePlayer's Lexicon using the supplied word
     * list. Words are inserted in a case-insensitive manner.
     */
    void BogglePlayer::buildLexicon(const std::set<std::string> &word_list){
      lexicon = new Trie();   //data structure to hold lexicon

      for(std::set<std::string>::iterator it = word_list.begin(); 
          it != word_list.end(); ++it){
        //get word from set
        std::string word = *it;
        //convert word to lowercase   
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        //insert the word in the trie
        lexicon->insert(word);
      }
    
    }

    /**
     * Initializes the BogglePlayer's internal board representation
     * using the supplied multidimentional array.
     */
    void BogglePlayer::setBoard(unsigned int rows, unsigned int cols,
            std::string **diceArray){

      //given board has height = rows, width = columns
      this->rows = rows;
      this->cols = cols;
        
      //the die at row R and column C has on its face the string in the
      //position diceArray[R][C] 
      for(unsigned int r = 0; r < rows; r++){
          for(unsigned int c = 0; c < cols; c++){
            string s = diceArray[r][c];
            //convert string to lower-case to be consistent with lexicon
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            //construct BoardPos and push to the vector 'board'
            BoardPos die = BoardPos(s);
            board.push_back(die);
          }
      }
      board_built = true;

    }
    
    /**
     * Populates the supplied set with the words in the BogglePlayer's
     * lexicon that appear on the board and are longer than
     * minimum_word_length.
     *
     * Returns false if either the board or the lexicon has not been
     * initialized. Returns true otherwise.
     */
    bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length,
            std::set<std::string> *words){
      if(!board_built || lexicon==NULL){
        return false;
      }
        
      reset();

      //search every row and column
      for(int r = 0; r < this->rows; r++){
        for(int c = 0; c < this->cols; c++){
          string word_matched ="";
          getWords(r, c, minimum_word_length, word_matched, words);
        }        
      }

      return true;
    }


    /**
     * Call a helper function getWords(row, col, LexNode*, word_matched,
     * words).
     */
    void BogglePlayer::getWords(int row, int col,unsigned int minimum_word_length,
       string& word_matched, std::set<std::string>* words){

      BoardPos* tile = &board[row*this->cols+col]; //get the tile at the row and column
      tile->setVisited(true); //mark it visited

      //append the text in the tile to the word we're trying to match
      word_matched+= tile->getText(); 
      //num of characters we'll need to erase during backtracking
      int erase = tile->getText().length(); 
 
      //do some pruning by checking if word is prefix
      if(lexicon->isPrefix(word_matched)){
      //make sure word is min length specified
      if(word_matched.length() >= minimum_word_length){
        if(isInLexicon(word_matched)){
          //inserting into the set after word is matched
          words->insert(word_matched);
        }
      }

      //checking the unvisited neighbors
      for( int r = row+1; r >= row-1; r--){
        for(int c = col+1; c >= col-1; c--){
          if((r >= 0) && (c >= 0) && (r < (int)this->rows) 
              && (c < (int)this->cols)&&
              !board[r*this->cols+c].getVisited()){
            getWords(r,c, minimum_word_length, word_matched, words);
              }
            }
      }
}
      // set tile visited to false
      tile->setVisited(false);
      //erase the characters before going back up the tree
      word_matched.erase(word_matched.length()-erase,erase);
    } 


    /**
     * Determines if the given word is in the BogglePlayer's lexicon.
     * The lexicon is searched in a case-insensitive fashion.
     *
     * Returns true if the word is in the lexicon, and false if not.
     */
    bool BogglePlayer::isInLexicon(const std::string &word_to_check){
      string word = word_to_check;
      //convert word to lowercase
      transform(word.begin(), word.end(), 
          word.begin(), ::tolower);
      //check if word is in lexicon
      return lexicon->find(word);
    }

    /* resets all of the board tiles to unvisited */
    void BogglePlayer::reset(){
      for(int i = 0; i < (int)board.size(); i ++){
        board[i].setVisited(false);
        board[i].setRevisited(false);
      } 
    }

    /**
     * Determines if the given word is on the BogglePlayer's board.
     * The board is searched in a case-insensitive fashion.
     *
     * Returns a vector of integers representing the positions on the board
     * that make up the word, if the word exists on the board. Otherwise,
     * returns an empty vector.
     */
    std::vector<int> BogglePlayer::isOnBoard(const std::string &word_to_check){
      //reset();
      bool found = false; //is word on the board?
      vector<int> positionNum; //matching letter position on board
      
      string wordLC = word_to_check;
      //convert the given to lower case
      transform(wordLC.begin(), wordLC.end(),
          wordLC.begin(), ::tolower);
      
      //if the board is not built yet, return an empty vector
      if(!board_built){
        return positionNum;
      }
      else{
        
        //isOnBOard() returns a vector of the positions in the board that 
        //need to be traversed to find the word
        
        //check all the tiles on board
        for(int r = 0; r < this->rows; r++){
          for(int c = 0; c < this->cols; c++){
            //find the starting tile
            found = findStart(r, c, wordLC, 0, &positionNum);
            if(found){break;}
          }
          if(found){break;}
        }
     
        //return an empty vector if word not found
        if(!found){
          positionNum.clear();
        }

        return positionNum;
      }
    }


    /**
     * Helper function for isOnBoard()
     */ 
    bool BogglePlayer::findStart(unsigned int row, unsigned int col, 
                  const std::string &word_to_check, unsigned int word_pos,
                  vector<int> *position){
      BoardPos* tile =  &(board[(row * this->cols) + col]);
      string word = tile->getText();
      
      //if tiles doesn't match with beginning of word return false
      if(word_to_check.compare(word_pos, word.length(),word) != 0 ){
        return false;
      }

      //else call findword
      else{
        if(findWord(row, col, word_to_check, 0, position)){
          return true;
        }
      }

      return false;
    }  

    /**
     * Helper function for isOnBoard()
     */ 
    bool BogglePlayer::findWord(unsigned int row, unsigned int col, 
                  const std::string &word_to_check, unsigned int word_pos,
                  vector<int> *position){
      //start with empty stack
      stack<std::pair<BoardPos*, std::pair<int, int>>> dice;
      //set all visited to false
      reset();
      int index = 0;
      //push the start
      BoardPos* start =  &(board[(row * this->cols) + col]);
      string word = start->getText(); //chars on starting tile
      index = (row * this->cols) + col; //index of starting tile on board

      dice.push(make_pair(start, make_pair(row, col)));

      while(!dice.empty()){

        //pair which holds the tile and a pair with the tile's row and column
        pair <BoardPos*, pair<int, int>> p = dice.top();
        BoardPos* tile = p.first;
        pair<int, int> rc = p.second; //row and column of tile
        int bRow = rc.first;
        int bCol = rc.second;
        index = bRow*this->cols+bCol;
        word = tile->getText();
        dice.pop();

        //handle backtracking
        if(tile->getRevisited()){
          tile->setRevisited(false);
          tile->setVisited(false);
          //subtract the number of added characters from current position
          word_pos-= word.length();
          //pop out wrong position from vector
          position->pop_back();
        }
        //tile is not visited and it matches
        else if(word_to_check.compare(word_pos, word.length(),
           word) == 0 && !tile->getVisited()){
          tile->setVisited(true); //set visited to true
          word_pos+= word.length(); //increment the position in word
          position->push_back(index); // add board position to return vector

          if(word_pos == word_to_check.length()){
            return true; //word matches, return
          }

          tile->setRevisited(true);
 
          //push tile back onto stack
          dice.push(make_pair(tile, make_pair(bRow, bCol)));

          //push all unvisited neighbors of tile onto stack
          for(int r = (int)bRow+1; r >= (int)bRow-1; r--){
            for(int c = (int)bCol+1; c >= (int)bCol-1; c--){
              if((r >= 0) && (c >= 0) && (r < (int)this->rows) 
                  && (c < (int)this->cols)&&
                  !board[r*this->cols+c].getVisited()){
                  index = r*this->cols+c;
                  BoardPos* neighbor = (&board[index]);
                  dice.push(make_pair(neighbor, make_pair(r, c)));
                  
              }
            }
          }
        }
      }
      return false; //word not on board
    }



    /**
     * Returns a custom board for the boggle ui. The board is loaded
     * from the file custboard.txt in the current working directory.
     * The input format is expected to follow that outlined in README_brd.
     */
    void BogglePlayer::getCustomBoard(std::string **&new_board,
            unsigned int *rows, unsigned int *cols){
      /* Dummy codes, so that warnings won't show up */
      this->rows = *rows;
      this->cols = *cols;
      new_board = NULL;
    }


