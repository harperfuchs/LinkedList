//
// Created by fuchs on 2/13/2023.
//
#include <iostream>
#include <vector>
#pragma once
using namespace std;

template<typename T>
class LinkedList{
public:
    struct Node{
        // Data you are storing
        // A pointer to the next node
        // A pointer to the previous node
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    // A pointer to the head
    // A node pointer to the tail
    // How many nodes are there
    // Behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    // Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    // Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertBefore(Node* node, const T& data);
    void InsertAfter(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    // Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    // Big Three
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;
};

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    const Node* currentPrint = node;
    cout << currentPrint -> data << endl;
    if((currentPrint -> prev) != nullptr){
        currentPrint = currentPrint -> prev;
        PrintReverseRecursive(currentPrint);
    }
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    const Node* currentPrint = node;
    cout << currentPrint -> data << endl;
    if((currentPrint -> next) != nullptr){
        currentPrint = currentPrint -> next;
        PrintForwardRecursive(currentPrint);
    }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if(index > (nodeCount -1) || index < 0){
        return false;
    }
    Node* remove = GetNode(index);
    Node* beforeRem = remove -> prev;
    Node* afterRem = remove -> next;
    beforeRem -> next = afterRem;
    afterRem -> prev = beforeRem;
    delete remove;
    nodeCount--;
    return true;
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    // remove all nodes that contain the given data
    Node* current = head;
    Node* remove = nullptr;
    unsigned int removeCount = 0;
    //unsigned int counter = 0;
    while(current){
        if((current -> data) != data) {
            remove = current;
            current = current->next;
        }
        else{
            if (current == head){
                current = current -> next;
                RemoveHead();
            }
            else if(current == tail){
                current = nullptr;
                RemoveTail();
            }
            Node* temp = current;
            remove -> next = current -> next;
            if(current -> next != nullptr){
                current -> next -> prev = remove;
            }
            current = current -> next;
            delete temp;
            removeCount++;
        }
    }
    return removeCount;
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
    // remove the tail
    Node* remove = tail;
    tail = tail -> prev;
    tail -> next = nullptr;
    delete remove;
    nodeCount--;
    if(nodeCount == 0){
        head = tail = nullptr;
        return false;
    }
    return true;
}

template<typename T>
bool LinkedList<T>::RemoveHead() {
    // remove the head
    if(nodeCount == 0){
        head = tail = nullptr;
        return false;
    }
    else if(nodeCount == 1){
        delete head;
        nodeCount--;
        return false;
    }
    Node* remove = head;
    head = head -> next;
    head -> prev = nullptr;
    delete remove;
    nodeCount--;
    return true;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    // overload == to compare each node in both linked lists
    T data1;
    T data2;
    if(nodeCount == rhs.nodeCount){
        for(int i = 0; i < (int)nodeCount; i++){
            data1 = this -> operator[](i);
            data2 = rhs[i];
            if(data1 != data2){
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    // insert node at index
    if(index == nodeCount){
        AddTail(data);
    }
    else if(index == 0){
        AddHead(data);
    }
    else{
        Node* current = GetNode(index);
        InsertBefore(current, data);
    }
}

template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &data) {
    // insert a node after the given node
    Node* temp = node -> next;
    Node* newNode = new Node;
    newNode -> data = data;
    node -> next = newNode;
    temp -> prev = newNode;
    newNode -> prev = node;
    newNode -> next = temp;
    nodeCount ++;
}

template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node *node, const T &data) {
    // insert a node before the given node
    Node* temp = node -> prev;
    Node* newNode = new Node;
    newNode -> data = data;
    node -> prev = newNode;
    temp -> next = newNode;
    newNode -> prev = temp;
    newNode -> next = node;
    nodeCount ++;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    //copy constructor
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
    for(int  i = 0; i < (int)list.nodeCount; i++){ // copy all nodes from original linked list
        const Node* current = list.GetNode(i);
        AddTail(current -> data);
    }
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    //copy assignment operator
    Clear(); // delete existing data
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
    for(int  i = 0; i < (int)rhs.nodeCount; i++){ // copy all nodes from original linked list
        const Node* current = rhs.GetNode(i);
        AddTail(current -> data);
    }
    return *this;
}

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    // overload de-referencing operator to use to find at index
    Node* indexPtr = nullptr;
    indexPtr = GetNode(index);
    return indexPtr -> data;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    // find all nodes w specified value and add them to a vector to be accessed later
    Node* current = head;
    while(current != nullptr){
        if(current -> data == value){
            outData.push_back(current);
        }
        current = current -> next;
    }
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const{
    // const version of find
    // finds node with the matching data
    Node* current = head;
    while(current != nullptr){
        if((current -> data) == data){
            return current;
        }
        current = current -> next;
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    // Find node that matches the specified data
    Node* current = head;
    while(current != nullptr){ // search until end
        if((current -> data) == data){
            return current;
        }
        current = current -> next;
    }
    return nullptr;
}

template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    // const version of overloading []
    const Node* indexPtr = GetNode(index);
    return indexPtr -> data;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const {
    //const version of getNode
    //looking for a node at a specific index
    if(index >= (nodeCount) || index < 0){
        throw out_of_range("Out of range.");
    }
    unsigned int count = 0;
    Node* current = head;
    while(count != index){
        current = current -> next;
        count++;
    }
    return current;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
    // Looking for the node at a specific index
    if(index >= (nodeCount) || index < 0){
        throw out_of_range("Out of range.");
    }
    unsigned int count = 0;
    Node* current = head;
    while(count != index){
        current = current -> next;
        count++;
    }
    return current;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
    // const version
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
    // const version
    return head;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

template<typename T>
void LinkedList<T>::Clear() {
    // clear all data from linked list / deallocate memory
    Node* current = head;
    while(current != nullptr){
        head = head -> next;
        delete current;
        current = head;
    }
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    //Gived an array of values, insert a node for each of those at the end of the list, maintaining the original order.
    for(int i = (int)(count - 1); i >= 0; i--){
        AddHead(data[i]);
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    //Given an array of values, insert a node for each of those at the beginning of the list, maintaining original order
    for(int i = 0; i < (int)count; i++){
        this -> AddTail(data[i]);
    }
}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    //Create a new node at the end of the list to store the passed in value
    Node* newNode = new Node;
    newNode -> data = data;
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode -> prev = tail;
        tail -> next = newNode;
        tail = newNode;
    }
    nodeCount++;
}

template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    //Create a new node at the front of the list to store the passed in value
    //Checking if the head of the linked list is null, then create node and assign data
    //Create new node if there is already a list and make the new node point to the current head (becomes second)
    //and make new node the new head, remove the prev nullptr from old head
    Node* newNode = new Node;
    newNode -> data = data;
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
    }
    nodeCount++;
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    //How many nodes in this list (Elements)
    return nodeCount;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    //Delete all nodes created by list
    Clear();
}


template<typename T>
LinkedList<T>::LinkedList() {
    //Default constructor: empty list, head points to nullptr, tail points to nullptr
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}


template<typename T>
void LinkedList<T>::PrintReverse() const {
    //Same as printforward but opposite direction
    Node* current = tail;
    while(current != nullptr){
        cout << current -> data << endl;
        current = current -> prev;
    }
}

template<typename T>
void LinkedList<T>::PrintForward() const {
    //Iterate through all of the nodes and print out their values one at a time
    Node* current = head;
    while(current != nullptr){
        cout << current -> data << endl;
        current = current -> next;
    }
}
