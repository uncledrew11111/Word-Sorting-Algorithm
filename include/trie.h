#include <iostream>
#include <vector>

#include "linkedList.h"
#include "node.h"
using namespace std;
#ifndef TRIE_H
#define TRIE_H

class trie {
    public:
        node* root;
        trie();
        ~trie();
        void insert(string word);
        void insert(const string& word, node* currentNode, int index);
        bool search(string word);
        bool search(const string& word, node* currentNode);
        node* searchLastNode(string word);
        node* searchLastNode(const string& word, node* currentNode, int index);
        void deleteWord(string word);
        int childCounter(node* currentNode);
        bool startsWith(string prefix);
        bool startsWith(const string& prefix, node* currentNode);
        int countWords(string word);
        vector<pair<int, string>> tenMostFrequentWords();
        void tenMostFrequentWords(node* currentNode, linkedList& frequencyList);
};

#endif //TRIE_H
