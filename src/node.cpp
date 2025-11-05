#include "node.h"

// node constructor
node::node() {
    // sets instance counter to be 0
    this->instanceCount = 0;
    this->previous = nullptr;
    // sets each child to be null to prevent errors
    for (int i=0; i<128; i++) {
        children[i] = nullptr;
    }
}

// node deconstructor
node::~node() {
    // iterates through each node and deletes all the children
    for (int i=0; i<128; i++) {
      if (children[i] != nullptr) {
        delete children[i];
        children[i] = nullptr;
      }
    }
    this->previous = nullptr;
}