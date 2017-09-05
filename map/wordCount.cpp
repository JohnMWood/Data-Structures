/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    John Wood and Etienne Beaulac (group 3)
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::endl;
using std::cout;
using std::cin;
using namespace custom;

/*****************************************************
 * READ FILE
 * Read in the file and put the words into the map
 * that has been passed in by reference
 *****************************************************/
void readFile(map <string, Count> & counts, const string & fileName)
{
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Could not open " << fileName << endl;
      return;
   }

   string temp;
   while (fin >> temp)
      counts[temp]++;
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string filename;
   map <string, Count> words;
   string tempWord;

   cout << "What is the filename to be counted? ";
   cin >> filename;

   readFile(words, filename);
   cout << "What word whose frequency is to be found. Type ! when done" << endl;

   cout << "> ";
   cin >> tempWord;
   while (tempWord != "!")
   {
      cout << "\t" << tempWord << " : " << words[tempWord] << endl;
      cout << "> ";
      cin >> tempWord;
   }
}
