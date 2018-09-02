/**
 * Author: Mohit Sakhuja
 * Dated: 29/08/2018
 *
 * Represents a Tree data structure.
 */

#ifndef TREE_HH
#define TREE_HH

#include <list>

#include "TreeNode.hh"

using namespace std;

class Tree {
private:
    // The root node of the tree.
    TreeNode *root;

    // Find in tree.
    TreeNode *find(int key);

    // Finds the predecessor in the left subtree along with its parent.
    // First vector element points to the parent.
    // Second points to the predecessor itself.
    vector<TreeNode *> find_pred_parent(TreeNode *root);

    // Swaps the data of two nodes.
    static void swap(TreeNode *node1, TreeNode *node2);

    // Utility function to delete a node.
    void delete_node(TreeNode *parent, TreeNode *curr_node);

public:
    // Memory management.
    Tree(void);
    ~Tree(void);

    // Insert a node.
    void push(int data);

    // In-order traversal.
    list<int> traverse(void);

    // Search for an element.
    bool search(int element);

    // Get the minimum and maximum elements respectively.
    TreeNode *min(void);
    TreeNode *max(void);

    // Select the ith order element.
    TreeNode *select(int order);

    // Select the predecessor and successor for a given element.
    TreeNode *pred(int element);
    TreeNode *succ(int element);

    // Returns the number of keys less than or equal to a given value.
    int rank(int element);

    // Remove a node with a given key.
    void pop(int key);

    // Returns the number of nodes currently in the tree.
    int size(void);

    // Returns true/false is tree is empty.
    bool empty(void);

    // Removes all elements from the tree.
    void clear(void);
};

#endif
