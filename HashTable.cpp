#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s; 
  hashTable = new list<WordEntry>[size]; 
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
  unsigned int initialVal, hashMultiplier, hash;
  hash = initialVal = 5381;
  hashMultiplier = 33;
  for (char character : s) {
    hash *= hashMultiplier;
    // add ASCII value of character, ignoring case
    hash += tolower(character);
  }
  
  return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
  /* Based on the list<WordEntry>, I think we're using the
     chaining technique, which means we might have multiple words
     mapped to a single bucket.
     To find the word (if it already exists) here and in getAverage(),
     we have to look through the entries in the bucket one by one
     and update the entry if found to already exist. */
  
  int hash = computeHash(s);
  WordEntry newEntry(s, score);
  list<WordEntry> &bucket = hashTable[hash];
  
  for (WordEntry &entry : bucket) {
    // search for word
    if (entry.getWord() == s) {
      // update word's score & appearances
      entry.addNewAppearance(score);
      return;
    }
  }
  
  // bucket doesn't contain s yet (may be empty)
  bucket.push_back(newEntry);
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
  int hash = computeHash(s);
  list<WordEntry> &bucket = hashTable[hash];
  
  for (WordEntry &entry : bucket) {
    if (entry.getWord() == s) {
      // return average score/sentiment of found word
      return entry.getAverage();
    }
  }
  
  // return neutral result
  return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
// https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/8/section/2
bool HashTable::contains(const string &s) {
  int hash = computeHash(s);
  list<WordEntry> :: iterator entry;
  list<WordEntry> &bucket = hashTable[hash];
  
  // iterate through list & search for item
  for (entry = bucket.begin(); entry != bucket.end(); ++entry) {
    // if item found, return true
    if (entry->getWord() == s) {
      return true;
    }
  }
  
  // item not found in hash table
  return false;
}
