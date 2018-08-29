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
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
};

#endif
