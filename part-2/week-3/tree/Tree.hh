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

    // Creates a TreeNode.
    static TreeNode *create_new_tree_node(int data);

public:
    // Insert a node.
    void insert(int data);

    // In-order traversal.
    list<int> traverse(void);
};

#endif
