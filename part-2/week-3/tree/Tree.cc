#include <cstdio>
#include <cstdlib>
#include <stack>

#include "Tree.hh"

using namespace std;

void Tree::insert(int data)
{
    // Create a new tree node.
    TreeNode *tree_node = create_new_tree_node(data);

    // If the tree is empty.
    if (!this->root) {
        this->root = tree_node;
        return;
    }

    // Else, traverse down the tree.
    TreeNode *curr_node = this->root;

    while (curr_node->left || curr_node->right) {
        // Traverse left if the data in the node to be inserted is less than or
        // equal to the data at the current node.
        if (tree_node->data <= curr_node->data) {
            if (curr_node->left)
                curr_node = curr_node->left;
            else
                break;
        } else { /* Traverse right otherwise */
            if (curr_node->right)
                curr_node = curr_node->right;
            else
                break;
        }
    }

    // Make the parent of the new node to be the current node.
    tree_node->parent = curr_node;

    // Attach the new node to the appropriate branch of the current node.
    if (tree_node->data <= curr_node->data)
        curr_node->left = tree_node;
    else
        curr_node->right = tree_node;
}

list<int> Tree::traverse(void)
{
    // Create a stack to hold all nodes.
    stack<TreeNode *> nodes;

    // Create a list to hold traversed nodes.
    list<int> traversed_nodes;

    // Start from the root node.
    TreeNode *curr_node = this->root;

    // Traversal will stop only when stack is empty and curr_node is NULL.
    while (!nodes.empty() || curr_node) {
        // Traverse the left branch of the current sub-tree.
        while (curr_node) {
            nodes.push(curr_node);
            curr_node = curr_node->left;
        }

        // Treat this node as the middle node.
        curr_node = nodes.top();
        nodes.pop();
        traversed_nodes.push_back(curr_node->data);

        // Try traversing the right branch of the current sub-tree.
        curr_node = curr_node->right;
    }

    return traversed_nodes;
}

TreeNode *Tree::create_new_tree_node(int data)
{
    // Allocate memory to the new tree node.
    TreeNode *tree_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!tree_node) {
        fprintf(stderr, "Error allocating memory to tree node\n");
        exit(1);
    }

    // Update the values and pointers of the new tree node.
    tree_node->data   = data;
    tree_node->left   = NULL;
    tree_node->right  = NULL;
    tree_node->parent = NULL;

    return tree_node;
}
