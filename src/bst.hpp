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
    void remove_helper(Node<T>*, T, Node<T>*);
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
    remove_helper(root, val, nullptr);
}

template<class T>
void BST<T>::remove_helper(Node<T> *node, T key, Node<T> *parent_node) {
    if(root == nullptr) {
        cout << "The tree is empty. Cannot remove >" << key << ">" << endl;
    } else {
        if(node->get_data() == key) {
            //Determine the type of node we're trying to remove
            if(node->get_left() == nullptr && node->get_right() == nullptr) { //    **** LEAF NODE ****
                if(node->get_data() == root->get_data()) { //IF the node is the tree's root node.
                    root = nullptr; //This tree is now empty.
                } else {
                    //Simply set the parent's node that points to the node we have found to null to remove the node.
                    if(parent_node->get_left()->get_data() == node->get_data()) { //Parent's left node is the node we are removing
                        parent_node->set_left(nullptr); //Adios amigo
                    } else { //Parent's right node is the node we are removing
                        parent_node->set_right(nullptr); //Adios amigo
                    }
                    delete(node); //release the memory held by the deleted node
                    return; //We are done.
                }
            //Single child (Left node is null and right node is not and Vice versa, to ensure the node has only one child)
            } else if( (node->get_left() == nullptr && node->get_right() != nullptr) || (node->get_left != nullptr && node->get_right() == nullptr)   ) { 
                if(node->get_data() == root->get_data()) { //IF the node is the tree's root node
                    if(node->get_left() == nullptr && node->get_right() != nullptr) { //THE CHILD IS TO NODE'S RIGHT
                        //Here we have concluded the following:
                        //
                        // [1]: The node we are removing has 1 and only 1 child
                        // [2]: The node we are removing is the root node
                        //
                        // Therefore, in this edge case, it does not matter if the child node is to the left or right of it's parent a.k.a the node we are removing.
                        // It only matters when deciding what root should be set to.
                        // This node regardless of side, will become the tree's root.
                        //
                        root = node->get_right();

                    } else { //THE CHILD IS TO NODE'S LEFT
                        //Here we have concluded the following:
                        //
                        // [1]: The node we are removing has 1 and only 1 child
                        // [2]: The node we are removing is the root node
                        //
                        // Therefore, in this edge case, it does not matter if the child node is to the left or right of it's parent a.k.a the node we are removing.
                        // It only matters when deciding what root should be set to.
                        // This node regardless of side, will become the tree's root.
                        //
                        root = node->get_left();
                    }
                    delete(node); //release the memory held by the deleted node
                    return; //We are done.

                } else { //The node is not the tree's root node

                }
            } else if() { //The node has two children (fml)

            }
        } else {
            //We have not yet found the node, try again using a search recursion
            if(key < node->get_data()) {
                remove_helper(node->get_left(), key, node);
            } else {
                remove_helper(node->get_right(), key, node);
            }
        }
    }
}

template<class T>
int BST<T>::get_size()
{
    return node_count;
}