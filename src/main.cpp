#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <random>

#include "trie.h"
#include "hash.h"

using namespace std;
using namespace std::chrono;

// clean up the token so it's just lowercase letters
string cleanWord(const string& token) {

    string w;
    for (char c : token) {
        if (isalpha((unsigned char)c)) {
            w.push_back((char)tolower((unsigned char)c));
        }
    }
    return w;

}

// read all the cleaned words from the file
vector<string> loadWords(const string& filename) {

    ifstream in(filename);
    vector<string> words;

    if (!in) {
        cerr << "Error: could not open file: " << filename << endl;
        return words;
    }

    string token;
    while (in >> token) {
        string w = cleanWord(token);
        if (!w.empty()) {
            words.push_back(w);
        }

    }

    cout << "Loaded " << words.size() << " cleaned words from file.\n";
    return words;
}

// function to list the top 10 words and thier frequencies
void printTopWords(const vector<pair<int, string>>& top) {

    cout << "Rank\tCount\tWord\n";
    int rank = 1;
    for (const auto& p : top) {
        cout << rank++ << "\t" << p.first << "\t" << p.second << "\n";
    }

}

// timing Trie and HashTable lookups with random words
void benchmarkLookups(const vector<string>& words, trie& t, hashTable& h) {
    if (words.empty()) {
        cout << "No words loaded, cannot benchmark.\n";
        return;

    }

    // sampling up to 1000 random words as queries
    size_t numQueries = min<size_t>(1000, words.size());
    vector<string> queries;
    queries.reserve(numQueries);

    mt19937 rng(random_device{}());
    uniform_int_distribution<size_t> dist(0, words.size() - 1);

    for (size_t i = 0; i < numQueries; ++i) {
        queries.push_back(words[dist(rng)]);
    }

    auto startTrie = high_resolution_clock::now();
    for (const auto& q : queries) {
        t.search(q);
    }
    auto endTrie = high_resolution_clock::now();

    auto startHash = high_resolution_clock::now();
    for (const auto& q : queries) {
        h.search(q);
    }
    auto endHash = high_resolution_clock::now();

    auto trieMs = duration_cast<milliseconds>(endTrie - startTrie).count();
    auto hashMs = duration_cast<milliseconds>(endHash - startHash).count();

    cout << "\nLookup benchmark on " << numQueries << " random queries:\n";
    cout << "Trie      : " << trieMs << " ms\n";
    cout << "Hash table: " << hashMs << " ms\n";
}

int main() {
    // ask user for file path and load data
    string filename;
    cout << "Enter path to text file (e.g. shakespeare.txt): ";
    getline(cin, filename);

    if (filename.empty()) {
        cout << "No file provided. Exiting.\n";
        return 0;

    }

    vector<string> words = loadWords(filename);
    if (words.empty()) {
        cout << "No words loaded. Exiting.\n";
        return 0;
    }

    // build the Trie and Hash Table, and then time how long it takes
    trie t;
    hashTable h;

    cout << "\nBuilding Trie...\n";
    auto startTrie = high_resolution_clock::now();
    for (const auto& w : words) {
        t.insert(w);
    }
    auto endTrie = high_resolution_clock::now();
    auto trieBuildMs = duration_cast<milliseconds>(endTrie - startTrie).count();

    cout << "Building Hash Table...\n";
    auto startHash = high_resolution_clock::now();
    for (const auto& w : words) {
        h.insert(w);
    }
    auto endHash = high_resolution_clock::now();
    auto hashBuildMs = duration_cast<milliseconds>(endHash - startHash).count();

    cout << "\n=== Build summary ===\n";
    cout << "Trie build time      : " << trieBuildMs << " ms\n";
    cout << "Hash table build time: " << hashBuildMs << " ms\n";

    // Simple menu for searching, top 10, and benchmarking
    int choice = -1;

    while (choice != 4) {
        cout << "\n==== WordSort Menu ====\n";
        cout << "1. Search for a word\n";
        cout << "2. Show top 10 most frequent words\n";
        cout << "3. Run lookup benchmark\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            break; // invalid input -> exit
        }

        if (choice == 1) {
            string q;
            cout << "Enter word to search: ";
            cin >> q;
            q = cleanWord(q);

            int trieCount = t.countWords(q);
            int hashCount = h.countWords(q);

            cout << "\nResults for \"" << q << "\":\n";
            cout << "Trie count      : " << trieCount << "\n";
            cout << "Hash table count: " << hashCount << "\n";


        } else if (choice == 2) {
            cout << "\nTop 10 words (Trie):\n";
            auto topTrie = t.tenMostFrequentWords();
            printTopWords(topTrie);

            cout << "\nTop 10 words (Hash Table):\n";
            auto topHash = h.tenMostFrequentWords();
            printTopWords(topHash);


        } else if (choice == 3) {
            benchmarkLookups(words, t, h);


        } else if (choice != 4) {
            cout << "Invalid option. Please choose 1–4.\n";
        }

    }

    cout << "Exiting WordSort.\n";
    return 0;
    
}
