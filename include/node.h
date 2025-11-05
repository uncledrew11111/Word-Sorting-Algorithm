#include <iostream>
using namespace std;
#ifndef NODE_H
#define NODE_H

class node {
    public:
        node();
        ~node();
        node* children[128];
        node* previous;
        int instanceCount;
        string word;
};

#endif //NODE_H
