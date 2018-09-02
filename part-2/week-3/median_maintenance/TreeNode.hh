/**
 * Author: Mohit Sakhuja
 * Dated: 29/08/2018
 *
 * Represents a single node of a tree.
 */

#ifndef TREENODE_HH
#define TREENODE_HH

struct TreeNode {
    int data;
    int nodes; /* Represents the number of nodes in the subtree for which this
                  node is the root node */
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data);
    ~TreeNode(void);
};

#endif
