/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {
  if(argc > 1 || argv[1]){
    cerr << "incorrect num of arguments" << endl;
    return -1;
  }

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  string wordA("PikaCHU");
  //string wordA("canibal");
  string wordX("x");
  string wordZ("Z");
  string wordG("g");
  lex.insert(wordA);
  lex.insert("tt");
  lex.insert("tttt");
  lex.insert("pinWhEeL");
  lex.insert("pinwheel");
  //string row0[] = {"D","C"};
  //string row1[] = {"b","A"};
  string row0[] = {"w", "n", "p", "I"};
  string row1[] = {"h", "a", "pi", "cHu"};
  string row2[] = {"e", "K", "pik", "a"};
  string row3[] = {"e", "l", "ttt", "t"};
/*  string row0[]={"l","a","b","k"};
  string row1[]={"p","c","i","z"};
  string row2[]={"s","a","n","x"};
  string row3[] = {"A", "n", "x", "p"};*/
  string* board[] = {row0,row1, row2, row3};
  set<string> words;
  vector<int> locations;
  int test[] = {7, 8, 5};
  vector <int> testSol (test, test + sizeof(test)/sizeof(int));
  p->buildLexicon(lex);

  p->setBoard(4, 4, board);

  if(p->isInLexicon(wordX)) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }
  if(p->isInLexicon("n")) {
    std::cerr << "Apparent problem with isInLexicon #4." << std::endl;
    return -1;
  }
  if(p->isInLexicon("ec")) {
    std::cerr << "Apparent problem with isInLexicon #4." << std::endl;
    return -1;
  }

  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }

  if(p->isInLexicon("t")) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }
  if(p->isInLexicon("ttt")) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }

  
  if(!p->isInLexicon("pinwheel")) {
    std::cerr << "Apparent problem with isInLexicon #7." << std::endl;
    return -1;
  }


  if(!p->isInLexicon("pINwheel")) {
    std::cerr << "Apparent problem with isInLexicon #3." << std::endl;
    return -1;
  }

    if(p-> isOnBoard("pinwheel").size() <= 0){
    std::cerr << "Apparent problem with isOnBoard #8." << std::endl;
    return -1;
  }
  if(p-> isOnBoard("pinwheel").size() <= 0){
    std::cerr << "Apparent problem with isOnBoard #9." << std::endl;
    return -1;
  }


  if(p-> isOnBoard("t").size() <= 0){
    std::cerr << "Apparent problem with isOnBoard #5." << std::endl;
    return -1;
  }
  if(p-> isOnBoard("tt").size() > 0){
    std::cerr << "Apparent problem with isOnBoard #6." << std::endl;
    return -1;
  }


  if(p-> isOnBoard(wordG).size() > 0){
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);

  if(locations.size() != 3){// || locations != testSol) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);

  if(locations.size() != 3){
 // if(locations.size() != 3 || locations != testSol) {
    std::cerr << "Apparent problem with isOnBoard #3." << std::endl;
    return -1;
  }
 
  
  if(!p->getAllValidWords(3,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  }

  //std::cerr << "word's size: " << words.size() << endl;
  
  if(words.size() != 3) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  } 
  delete p;
  return 0;

}
