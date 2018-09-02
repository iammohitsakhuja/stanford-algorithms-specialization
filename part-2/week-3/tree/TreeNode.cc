#include <cstddef>

#include "TreeNode.hh"

TreeNode::TreeNode(int data)
{
    this->data  = data;
    this->nodes = 1;
    this->left  = NULL;
    this->right = NULL;
}

TreeNode::~TreeNode(void)
{
    this->left  = NULL;
    this->right = NULL;
}
