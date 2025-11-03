# C++ Word Sorting Algorithm

## Problem

When dealing with really large text files like books, articles, or online discussions, it can take a long time to search for specific words and/or find how often they appear. A simple "scan through everything" approach becomes too slow as the file grows. We want to build a program that can store, search, and count words in a large dataset using efficient data structures.

## Motivation

Fast text search is essential for large data technology that handles massive amounts of text. These tools can better help readers quickly find any topic they are looking for in a text. Also, the more efficient they are (both memory and time wise), the less frustrating they are on the user's end (which is important from a business and social standpoint). Our goal is to find which data structure (Trie or Hash Table) offers faster lookups and better memory efficiency. This comparison will also help us understand how real-world search and autocomplete systems work.

## Features

We will know that we've solved the problem when:
- Our program can load and process at least 100k words from a dataset
- Both the Trie and the Hash Table versions can correctly insert and find words
- We can measure and compare build time, lookup time, and memory usage for both methods
- We can show word frequencies, display the top 10 most common words, and handle user searches instantly
- There is a good user experience for loading data, choosing a structure, and viewing results

## Data

Currently, we plan to use free public domain books from Project Gutenberg. These texts will contain well over 100,000 words.

**Link:** https://www.gutenberg.org/

The dataset will have two fields: word (string) for each token and line_number (integer) for the word's position in the text. Before inserting into the hash/trie, we will remove punctuation, convert to lowercase, and split the text into individual words.

## Tools

**Language:** C++

**Libraries:** `<fstream>` for reading files, `<chrono>` for timing, `<iomanip>` for formatted output.

**Editor:** VS Code & CLion

## Visuals

*Wireframe concepts are subject to change. This is an initial proof of concept

## Strategy

We'll build and compare two data structures from scratch:

1. **Trie (Prefix Tree):** Stores each word letter by letter which makes prefix searches very fast.
2. **Hash Table:** Stores each word with a custom hash function and resolves collisions using chaining.

We'll store each word and how often it appears in both structures, then time how long it takes to insert and search. After that, we'll compare their speed and memory use, saving the results to see which one performs better.

## Building the Project

To compile and run the project:

```bash
make
```

To test the compiled program:

```bash
make test
```

To clean build files:

```bash
make clean
```
