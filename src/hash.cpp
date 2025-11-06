#include "hash.h"
#include <algorithm>

hashTable::hashTable(size_t capacity) : table(capacity, nullptr), cap(capacity) {}

hashTable::~hashTable() {
	clear();
}

size_t hashTable::hash(const string& key) const {
	// simple custom hash (djb2-like but toned down)
	unsigned long h = 5381;
	for (unsigned char c : key) {
		h = ((h << 5) + h) + c; // h * 33 + c
	}
	return h % cap;
}

void hashTable::insert(string word) {
	size_t idx = hash(word);
	Entry* cur = table[idx];
	while (cur) {
		if (cur->key == word) {
			cur->count++;
			return;
		}
		cur = cur->next;
	}
	Entry* e = new Entry(word);
	e->next = table[idx];
	table[idx] = e;
}

bool hashTable::search(string word) {
	size_t idx = hash(word);
	Entry* cur = table[idx];
	while (cur) {
		if (cur->key == word) return true;
		cur = cur->next;
	}
	return false;
}

void hashTable::deleteWord(string word) {
	size_t idx = hash(word);
	Entry* cur = table[idx];
	Entry* prev = nullptr;
	while (cur) {
		if (cur->key == word) {
			cur->count--;
			if (cur->count <= 0) {
				if (prev) prev->next = cur->next; else table[idx] = cur->next;
				delete cur;
			}
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

int hashTable::countWords(string word) {
	size_t idx = hash(word);
	Entry* cur = table[idx];
	while (cur) {
		if (cur->key == word) return cur->count;
		cur = cur->next;
	}
	return 0;
}

vector<pair<int, string>> hashTable::tenMostFrequentWords() {
	vector<pair<int, string>> all;
	all.reserve(128);
	for (auto head : table) {
		for (Entry* cur = head; cur; cur = cur->next) {
			if (cur->count > 0) all.push_back({cur->count, cur->key});
		}
	}
	sort(all.begin(), all.end(), [](const auto& a, const auto& b) {
		if (a.first != b.first) return a.first > b.first; // higher count first
		return a.second < b.second; // then alphabetical
	});
	if (all.size() > 10) all.resize(10);
	return all;
}

void hashTable::clear() {
	for (auto& head : table) {
		Entry* cur = head;
		while (cur) {
			Entry* nxt = cur->next;
			delete cur;
			cur = nxt;
		}
		head = nullptr;
	}
}
