#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>

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
            if (curr_node->left) {
                curr_node->nodes++;
                curr_node = curr_node->left;
            } else
                break;
        } else { /* Traverse right otherwise */
            if (curr_node->right) {
                curr_node->nodes++;
                curr_node = curr_node->right;
            } else
                break;
        }
    }

    // Make the parent of the new node to be the current node.
    tree_node->parent = curr_node;
    curr_node->nodes++;

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

bool Tree::search(int element)
{
    return this->find(element) ? true : false;
}

TreeNode *Tree::min(void)
{
    // Return NULL when the tree is empty.
    if (!this->root)
        return NULL;

    return this->select(1);
}

TreeNode *Tree::max(void)
{
    // Return NULL when the tree is empty.
    if (!this->root)
        return NULL;

    return this->select(this->root->nodes);
}

TreeNode *Tree::select(int order)
{
    // Return NULL when the tree is empty.
    if (!this->root)
        return NULL;

    // Return NULL when the order is either less than 1 or higher than the
    // number of elements.
    if (order < 1 || order > this->root->nodes)
        return NULL;

    TreeNode *curr_node = this->root;

    while (curr_node->left || curr_node->right) {
        int curr_order = (curr_node->left ? curr_node->left->nodes : 0) + 1;

        if (order == curr_order)
            return curr_node;
        else if (order < curr_order)
            curr_node = curr_node->left;
        else {
            order -= curr_order;
            curr_node = curr_node->right;
        }
    }

    if (order == curr_node->nodes)
        return curr_node;

    return NULL;
}

TreeNode *Tree::pred(int element)
{
    // Return NULL if the tree is empty.
    if (!this->root)
        return NULL;

    // Start from the root node.
    TreeNode *curr_node = this->root;

    // Create a stack to hold all possible predecessors (i.e. nodes < element).
    stack<TreeNode *> possible_predecessors;

    while (curr_node && (curr_node->left || curr_node->right)) {
        // If the value at current node is greater than or equal to the
        // element, then the predecessor lies to the left of the current node.
        if (element <= curr_node->data)
            curr_node = curr_node->left;
        else { /* Else it lies to the right */
            possible_predecessors.push(curr_node);
            curr_node = curr_node->right;
        }
    }

    // curr_node might be pointing to a leaf node.
    if (curr_node && curr_node->data < element)
        possible_predecessors.push(curr_node);

    // If we did not find any possible predecessors, then there are none.
    if (possible_predecessors.empty())
        return NULL;

    // Otherwise, topmost node of the stack is the predecessor.
    curr_node = possible_predecessors.top();
    while (!possible_predecessors.empty())
        possible_predecessors.pop();

    return curr_node;
}

TreeNode *Tree::succ(int element)
{
    // Return NULL if the tree is empty.
    if (!this->root)
        return NULL;

    // Start from the root node.
    TreeNode *curr_node = this->root;

    // Create a stack to hold all possible successors (i.e. nodes > element).
    stack<TreeNode *> possible_successors;

    while (curr_node && (curr_node->left || curr_node->right)) {
        if (element >= curr_node->data)
            curr_node = curr_node->right;
        else {
            possible_successors.push(curr_node);
            curr_node = curr_node->left;
        }
    }

    // curr_node might be pointing to a leaf node.
    if (curr_node && curr_node->data > element)
        possible_successors.push(curr_node);

    // If we did not find any possible successors, then there are none.
    if (possible_successors.empty())
        return NULL;

    // Otherwise, topmost node of the stack is the successor.
    curr_node = possible_successors.top();
    while (!possible_successors.empty())
        possible_successors.pop();

    return curr_node;
}

int Tree::rank(int element)
{
    // Rank is 0 if the tree is empty.
    if (!this->root)
        return 0;

    // Start from the root node.
    TreeNode *curr_node = this->root;

    int rank = 0;
    while (curr_node && (curr_node->left || curr_node->right)) {
        // Rank stays the same when looking to the left.
        if (element < curr_node->data)
            curr_node = curr_node->left;
        else {
            // Rank increases when looking to the right.
            int curr_rank = (curr_node->left ? curr_node->left->nodes : 0) + 1;
            rank += curr_rank;
            curr_node = curr_node->right;
        }
    }

    // When curr_node points to a leaf node.
    if (curr_node && curr_node->data <= element)
        rank += 1;

    return rank;
}

void Tree::remove(int key)
{
    // TODO: Handle deletion of root node.

    // Find the node with the same key, and also its parent.
    TreeNode *curr_node = this->root;
    TreeNode *parent    = NULL;

    while (curr_node) {
        if (key == curr_node->data)
            break;

        parent = curr_node;
        if (key < curr_node->data)
            curr_node = curr_node->left;
        else
            curr_node = curr_node->right;
    }

    // No node to delete if there is no node with the given key.
    if (!curr_node)
        return;

    // Now delete the node.
    this->delete_node(parent, curr_node);
}

void Tree::delete_node(TreeNode *parent, TreeNode *curr_node)
{
    // Check the number of children that this node has.
    // Nodes = 1 means that it has no children.
    if (curr_node->nodes == 1) {
        if (!parent)
            this->root = NULL;
        else {
            if (curr_node->data <= parent->data)
                parent->left = NULL;
            else
                parent->right = NULL;
            parent->nodes--;
        }

        free(curr_node);
        return;
    }

    // Check if the current node has only the left branch.
    else if (curr_node->left && !curr_node->right) {
        if (!parent) {
            this->root = curr_node->left;
        } else {
            if (curr_node->data <= parent->data)
                parent->left = curr_node->left;
            else
                parent->right = curr_node->left;
            parent->nodes--;
        }

        free(curr_node);
        return;
    }

    // Check if the current node has only the right branch.
    else if (!curr_node->left && curr_node->right) {
        if (!parent) {
            this->root = curr_node->right;
        } else {
            if (curr_node->data <= parent->data)
                parent->left = curr_node->right;
            else
                parent->right = curr_node->right;
            parent->nodes--;
        }

        free(curr_node);
        return;
    }

    // Else, when the current node has both branches, find its predecessor
    // (which is guaranteed to exist in the left subtree).
    else {
        vector<TreeNode *> nodes = this->find_pred_parent(curr_node);

        TreeNode *pred_parent = nodes[0];
        TreeNode *pred        = nodes[1];

        // Update the number of nodes in current node.
        curr_node->nodes--;

        // Swap the predecessor's data with the current node's data.
        swap(pred, curr_node);

        // Delete the node at the position of the predecessor.
        this->delete_node(pred_parent, pred);
    }
}

void Tree::swap(TreeNode *node1, TreeNode *node2)
{
    int data    = node1->data;
    node1->data = node2->data;
    node2->data = data;
}

vector<TreeNode *> Tree::find_pred_parent(TreeNode *root)
{
    // Vector to hold pointers to the parent of the predecessor and the
    // predecessor itself.
    vector<TreeNode *> nodes(2);

    // Start from the node that is left child for the root node.
    TreeNode *pred        = root->left;
    TreeNode *pred_parent = root;

    // Since the predecessor is guaranteed to be found in the left subtree,
    // it is assured that the predecessor for the given root is the rightmost
    // node of the left subtree.
    while (pred && pred->right) {
        pred_parent = pred;
        pred        = pred->right;
    }

    nodes[0] = pred_parent;
    nodes[1] = pred;

    return nodes;
}

TreeNode *Tree::find(int key)
{
    // Start searching from the root node.
    TreeNode *curr_node = this->root;

    while (curr_node) {
        // If the current node's data is equal to the element, then return that
        // element.
        if (key == curr_node->data)
            return curr_node;

        // If element is less than the current node's data, then search the
        // left branch.
        if (key < curr_node->data)
            curr_node = curr_node->left;
        // Else search the right branch.
        else
            curr_node = curr_node->right;
    }

    return NULL;
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
    tree_node->nodes  = 1;
    tree_node->left   = NULL;
    tree_node->right  = NULL;
    tree_node->parent = NULL;

    return tree_node;
}
