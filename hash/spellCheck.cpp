/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Authors:
 *    John Wood and Etienne Beaulac (group 3)
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "spellCheck.h"
#include "hash.h"
#include "vector.h"
using namespace std;

/***********************************************************************
 * GET FILE NAME
 * Get a filename from the user
 ************************************************************************/
string getFilename()
{
   string filename;
   cout << "What file do you want to check? ";
   cin >> filename;
   return filename;
}

/***********************************************************************
 * CREATE HASH FROM FILE
 * Creates a hash by reading in the file and inserting the words into the hash
 ************************************************************************/
void createHashFromFile(string filename, SHash & hash)
{
   // cout << filename << endl;
   ifstream fin(filename.c_str());
   if (fin.fail())
   {
      cout << "ERROR: Unable to read file.\n";
      return;
   }

   string temp;
   while (fin >> temp)
      hash.insert(temp);

   fin.close();
}

/***********************************************************************
 * CHECK SPELLING
 * Displays whether a word is misspelled or not based off of the dictionary
 * hash and our misspelled words.
 ************************************************************************/
void checkSpelling(string filename, const SHash & dictionary, vector <string> & misspelled)
{
   ifstream fin(filename.c_str());
   if (fin.fail())
   {
      cout << "ERROR: Unable to read file.\n";
      return;
   }

   string temp;
   while (fin >> temp)
   {
      string lowercase = temp;
      transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
      if (!dictionary.find(lowercase))
         misspelled.push_back(temp);
   }

   fin.close();
}

/*****************************************
 * FIND MOST EFFICIENT
 * This function is designed to find the best size possible for the hash
 * by finding a good equilibrium between empty buckets and biggest bucket
 ****************************************/
void findMostEfficient()
{
   int emptyBuckets = 1000;
   int biggestBucket = 1000;
   int bestNumberFound = 0;

   for (int i = 1500; i > 5; --i)
   {
      SHash hashDictionary(i);
      createHashFromFile("/home/cs235/week12/dictionary.txt", hashDictionary);
      hashDictionary.computeEfficiency();
      if (hashDictionary.getEmptyBuckets() < 5 && hashDictionary.getBiggestBucket() < biggestBucket)
      {
         bestNumberFound = i;
         biggestBucket = hashDictionary.getBiggestBucket();
         emptyBuckets = hashDictionary.getEmptyBuckets();
      }
   }

   cout << "BEST NUMBER: " << bestNumberFound << " with " << emptyBuckets
        << " empty buckets and " << biggestBucket << " biggest size." << endl;
}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   // We found 379 from the findMostEfficient function
   SHash hashDictionary(379);
   vector <string> misspelledWords;

   createHashFromFile("/home/cs235/week12/dictionary.txt", hashDictionary);
   checkSpelling(getFilename(), hashDictionary, misspelledWords);

   if (misspelledWords.empty())
      cout << "File contains no spelling errors\n";
   else
   {
      cout << "Misspelled: ";
      for (int i = 0; i < misspelledWords.size(); ++i)
      {
         cout << misspelledWords[i];
         if (i + 1 < misspelledWords.size())
            cout << ", ";
      }
      cout << endl;
   }

   // findMostEfficient();
}
