#include <vector>
#include <iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;


class linkedListNode {
public:
    pair<int, string> current;
    linkedListNode* next;
    linkedListNode();
    linkedListNode(pair<int, string> instancePair);
    ~linkedListNode();
};



class linkedList {
    private:
      linkedListNode* head;
      int listSize;
    public:
      linkedList();
      linkedList(pair<int, string> instancePair);
      void addNode(pair<int, string> instancePair);
      ~linkedList();
      int getListSize();
        vector<pair<int, string>> linkedListVectorization();
};
#endif //LINKEDLIST_H
