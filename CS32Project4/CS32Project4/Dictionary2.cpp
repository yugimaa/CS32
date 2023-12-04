// Dictionary.cpp


// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include<vector> /
using namespace std;

void removeNonLetters(string& s);

void generateNextPermutation(string& permutation);

unsigned int hashFunction(string& word, int bucketnumber)
{
    unsigned int hashValue = 0;

    //Go through each letter in string and add up the numbers
    for (string::iterator it = word.begin(); it != word.end(); it++)
    {
        hashValue += static_cast<unsigned int>(*it);
    }

    //Reduce the hash value to fit within the table size
    hashValue %= bucketnumber;
    return hashValue;
}


//This class does the real work of the implementation.
class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets) : m_numBuckets(maxBuckets), m_buckets(maxBuckets) {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    vector<list<string>> m_buckets; //vector of lists (buckets for lists)
    int m_numBuckets;
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if (!word.empty())
    {
        int index = hashFunction(word, m_numBuckets); //get hash value
        m_buckets[index].push_back(word); //insert word into list of the correct bucket 
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string permutation = letters;

    //modify this bit (prob)
    //for every permutation, gets its hash table value and look for it. If it exists, call calbakc with that
    do
    {
        int index = hashFunction(permutation, m_numBuckets); //get index number of bucket
        list<string> bucketContent = m_buckets[index]; //set m_words as list inside bucket
        for (list<string>::iterator it = bucketContent.begin(); it != bucketContent.end(); it++) //traverse list until match is found
        {
            if (*it == permutation) //if match is found
            {
                string s = *it;
                callback(s); //call callback with permutation
            }
        }
        generateNextPermutation(permutation);
    } while (permutation != letters);
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
