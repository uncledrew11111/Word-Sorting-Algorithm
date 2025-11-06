#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class hashTable {
public:
	hashTable(size_t capacity = 10007);
	~hashTable();

	void insert(string word);
	bool search(string word);
	void deleteWord(string word);
	int countWords(string word);
	vector<pair<int, string>> tenMostFrequentWords();

private:
	struct Entry {
		string key;
		int count;
		Entry* next;
		Entry(const string& k) : key(k), count(1), next(nullptr) {}
	};

	vector<Entry*> table;
	size_t cap;

	size_t hash(const string& key) const;
	void clear();
};

#endif // HASH_H
