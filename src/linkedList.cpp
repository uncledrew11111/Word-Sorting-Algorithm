#include "linkedList.h"

// constructor for linked list node
linkedListNode::linkedListNode() {
    current = {0, ""};
    next = nullptr;
}

// parametereized constructor for linked list node
linkedListNode::linkedListNode(pair<int, string> instancePair) {
    current = instancePair;
    next = nullptr;
}

// destructor for linked list node
linkedListNode::~linkedListNode() {
    next = nullptr;
}





// constructor for the linked list
linkedList::linkedList() {
    head = nullptr;
    listSize = 0;
}

// constrcutor for the linked list using paired values
linkedList::linkedList(pair<int, string> instancePair) {
    head = new linkedListNode(instancePair);
    listSize = 1;
}

// destructor for linked list
linkedList::~linkedList() {
    linkedListNode* current = head;
    while (current != nullptr) {
        linkedListNode* tempNode = current->next;
        delete current;
        current = tempNode;
    }
    listSize = 0;
    head = nullptr;
}

// adds node to linked list
void linkedList::addNode(pair<int, string> instancePair) {
    // make bool val that is true until node is in correct spot
    bool truth = true;
    // current node for iterating through
    linkedListNode* currentNode = head;
    linkedListNode* newNode = new linkedListNode(instancePair);
    // if list is empty, add and then move on
    if (listSize == 0) {
        head = newNode;
        listSize++;
        return;
    }
    // if the newest node is smaller than the current head, disregard and retuyrn
    if (instancePair.first < currentNode->current.first) {
        newNode->next = head;
        head = newNode;
        listSize++;
        truth = false;
    }
    // If the newest node
    while (truth == true) {
        if (instancePair.first > currentNode->current.first) {
            // if there is nothing after the current node, add it in
            if (currentNode->next == nullptr) {
                currentNode->next = newNode;
                listSize++;
                truth = false;
            }
            // if the node goes between the current and the next
            else if (instancePair.first < currentNode->next->current.first) {
                newNode->next = currentNode->next;
                currentNode->next = newNode;
                listSize++;
                truth = false;
            }
            // If it doesnt go between this and the next, and the next does exist, iterate forward
            else {
                currentNode = currentNode->next;
            }
        }
        else {
            truth = false;
        }
    }
    if (listSize > 10) {
        linkedListNode* tempNode = head;
        head = head->next;
        delete tempNode;
        listSize--;
    }
}

// returns listSize
int linkedList::getListSize() {
    return listSize;
}

// returns a vector version of the linked list in reverse order
vector<pair<int, string>> linkedList::linkedListVectorization() {
    vector<pair<int, string>> vectorToReturn;
    linkedListNode* current = head;
    // iterate through each node and append its values to the vector
    while (current != nullptr) {
        vectorToReturn.push_back(current->current);
        current = current->next;
    }
    return vectorToReturn;
}