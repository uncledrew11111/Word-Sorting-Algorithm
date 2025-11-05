#include "trie.h"
#include <algorithm>
#include <bits/ranges_algo.h>

// trie constructor
trie::trie() {
    root = new node();
}



// trie deconstructor
trie::~trie() {
    delete root;
}



// Allows for insertion function without having to declare that its for the root in the main
void trie::insert(string word) {
    insert(word, this->root, 0);
}



// trie function for inserting word into it (is recursive)
// indexing included to improve efficiency so new word doesn't have to be created each time
// Passing word as const reference improves effieicny even more for the same reason
void trie::insert(const string& word, node* currentNode, int index) {
    // if recursive stent is over, set last letter to be the end of a word
    // increase instance of ending word if its a duplicate
    if (word.length() <= index) {
        // for "most frequent word" purposes
        currentNode->word = word;
        currentNode->instanceCount++;
        return;
    }
    char insertedLetter = (unsigned char) word[index];
    // If node has instance of the prefix already existing, make a new instance for it
    if (currentNode->children[insertedLetter] == nullptr) {
        currentNode->children[insertedLetter] = new node();
        // Sets previous node to be current node for efficient deletion purposes
        currentNode->children[insertedLetter]->previous = currentNode;
    }
    // recursively move on to next digit fo the word and remove the first
    insert(word, currentNode->children[insertedLetter], index + 1);
}



// Allows for search function without having to declare that its for the root in the main
bool trie::search(string word) {
    return search(word, this->root);
}



// trie function for searching whether a word is in the trie
// indexing included to improve efficiency so new word doesn't have to be created each time
// Passing word as const reference improves effieicny even more for the same reason
bool trie::search(const string& word, node* currentNode) {
    // sets the current node to be the last letter of the word in the tree
    currentNode = searchLastNode(word, currentNode, 0);
    bool value = true;
    // If previous last letter does not exist, then it means the word does not exist in the trie
    // will also return false if the instanceCounter = 0 (eg if "apple" is wa word, "app" should return false)
    if (currentNode == nullptr) {
        value = false;
    }
    else if (currentNode->instanceCount <= 0) {
        value = false;
    }
    return value;
}



// Allows for searchLastNode function without having to declare that its for the root in the main
node* trie::searchLastNode(string word) {
    return searchLastNode(word, root, 0);
}



// trie function for searching whether a word is in the trie
// returns a pointer to the last letter of the word if it does, returns null if it doesnt
// indexing included to improve efficiency so new word doesn't have to be created each time
// Passing word as const reference improves effieicny even more for the same reason
node* trie::searchLastNode(const string& word, node* currentNode, int index) {
    //ends recursive loop if the word no longer exists
    if (word.length() <= index) {
        return currentNode;
    }
    if (currentNode == nullptr) {
        return nullptr;
    }
    char searchedLetter = (unsigned char) word[index];
    // checks to see if the next letter is already in the trie (recursively moves forward through word if so)
    if (currentNode->children[searchedLetter] != nullptr) {
        // returns the node (nullptr if it doesnt exist, the last letter if it does)
        return searchLastNode(word, currentNode->children[searchedLetter], index + 1);
    }
    // if the next letter does not exist, then the word does not exist
    return nullptr;
}



// trie function that deletes word from trie
void trie::deleteWord(string word) {
    int index = 1;
    // Finds node pointing to final letter of word
    node* finalNode = this->searchLastNode(word);
    // Fail safe for if word does not exist
    if (finalNode == nullptr || finalNode->instanceCount <= 0) {
        return;
    }
    // delete one of the word's instances
    finalNode->instanceCount--;
    int newInstanceCount = finalNode->instanceCount;
    // continues deletion until there are no more of the unconnected letters left in the word
    while (finalNode != nullptr && finalNode->instanceCount < 1 && childCounter(finalNode) < 1) {
        node* tempFinalNode = finalNode;
        finalNode = finalNode->previous;
        // if node before final node exists (final ndde is not the root)
        if (finalNode != nullptr) {
            // sets child to nullptr to prevent memory issues
            finalNode->children[(unsigned char)word[word.length() - index]] = nullptr;
        }
        delete tempFinalNode;
        index++;
    }
}



//v trie function which counts how many children a given node has
int trie::childCounter(node* currentNode) {
    int childCount = 0;
    // Iterates through each child node
    for (int i = 0; i < 128; i++) {
        // If a child exists, add 1 to the count
        if (currentNode->children[i] != nullptr) {
            childCount++;
        }
    }
    return childCount;
}



// Allows for startsWith function without having to declare that its for the root in the main
bool trie::startsWith(string word) {
    return startsWith(word, this->root);
}



// trie function that checks whether a word exists which starts with the given prefix (eg. "ap" would be true if "apple" was in the trie))
// indexing included to improve efficiency so new word doesn't have to be created each time
// Passing word as const reference improves effieicny even more for the same reason
bool trie::startsWith(const string& prefix, node* currentNode) {
    // search returns whether a word exists, and prefix would count as a word
    // Thus, simply removing the instance check would return whether its in the word ir not

    // sets the current node to be the last letter of the word in the tree
    currentNode = searchLastNode(prefix, currentNode, 0);
    bool value = true;
    // If previous last letter does not exist, then it means the word does not exist in the trie
    // will also return false if the instanceCounter = 0 (eg if "apple" is wa word, "app" should return false)
    if (currentNode == nullptr) {
        value = false;
    }
    return value;
}



// trie function that returns the total number of word instances in the trie (only includes full words)
int trie::countWords(string word) {
    node* currentNode = searchLastNode(word, root, 0);
    if (currentNode == nullptr) {
        return 0;
    }
    return currentNode->instanceCount;
}



// Allows for startsWith function without having to declare that its for the root in the main
vector<pair<int, string>> trie::tenMostFrequentWords() {
    linkedList frequencyList = linkedList();
    tenMostFrequentWords(this->root, frequencyList);
    return frequencyList.linkedListVectorization();
}


// potentially switch to heap to make sorting useless and convert to o(n) instead
void trie::tenMostFrequentWords(node* currentNode, linkedList& frequencyList) {
    // currentNode!= nullptr added for when root is currentNode
    if (currentNode == nullptr) {
        return;
    }
    // Add node to frequency list
    // Linked list does logic for emplacement
    frequencyList.addNode({currentNode->instanceCount, currentNode->word});
    // look through each node and recursively go through any that may exist
    for (int i=0; i<128; i++) {
        if (currentNode->children[i] != nullptr) {
            tenMostFrequentWords(currentNode->children[i], frequencyList);
        }
    }
}