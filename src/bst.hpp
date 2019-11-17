#pragma once
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;

    Node<T> *searchHelper(Node<T>*, T);
    void inorder_helper(std::vector<T>*, Node<T>*);
    void postorder_helper(std::vector<T>*, Node<T>*);
    void preorder_helper(std::vector<T>*, Node<T>*);
    Node<T> *insert_helper(Node<T>*, T);
    void remove_helper(Node<T>*, T);
};

template<class T>
BST<T>::BST()
{
    root = nullptr;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = nullptr;
    while(root != nullptr)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
 {
    std::vector<T> *vec = new std::vector<T>;
    inorder_helper(vec, root);
    return vec;
}

template<class T>
void BST<T>::inorder_helper(std::vector<T> *vec, Node<T> *_node) {
    if(_node != nullptr) {    
        inorder_helper(vec, _node->get_left());
        vec->push_back(_node->get_data());
        inorder_helper(vec, _node->get_right());
    }
}

template<class T>
void BST<T>::preorder_helper(std::vector<T> *vec, Node<T> *_node) {
    if(_node != nullptr) {
        vec->push_back(_node->get_data());
        preorder_helper(vec, _node->get_left());
        preorder_helper(vec, _node->get_right());
    }
}

template<class T>
void BST<T>::postorder_helper(std::vector<T> *vec, Node<T> *_node) {
    if(_node != nullptr) {
        postorder_helper(vec, _node->get_left());
        postorder_helper(vec, _node->get_right());
        vec->push_back(_node->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    preorder_helper(vec, root);
    return vec;
}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    postorder_helper(vec, root);
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insert_helper(root, new_data);
}

template<class T>
Node<T>* BST<T>::insert_helper(Node<T> *node, T newNodeData) {
    if(node == nullptr) {
        Node<T> *newNode = new Node<T>(newNodeData);
        newNode->set_right(nullptr);
        newNode->set_left(nullptr);
        node_count++;
        return newNode;
    } else {
        if(newNodeData > node->get_data()) {
            node->set_right(insert_helper(node->get_right(), newNodeData));
        } else {
            node->set_left(insert_helper(node->get_left(), newNodeData));
        }
    }
    return node;
}

template<class T>
Node<T> *BST<T>::search(T val)
{
    Node<T> *result = searchHelper(root, val);
    return result;
}

template<class T>
Node<T> *BST<T>::searchHelper(Node<T> *_root, T val) {
    Node<T> *cur = _root;
    if(cur == nullptr) {
        return nullptr;
    } else {
        if(val == cur->get_data()) {
            return cur;
        } else {
            if(val < cur->get_data()) {
                return searchHelper(cur->get_left(), val);
            } else {
                return searchHelper(cur->get_right(), val);
            }
        }
    }
}

template<class T>
void BST<T>::remove(T val)
{
    remove_helper(root, val);
}

template<class T>
void BST<T>::remove_helper(Node<T> *tree, T key) {
    
}

template<class T>
int BST<T>::get_size()
{
    return node_count;
}