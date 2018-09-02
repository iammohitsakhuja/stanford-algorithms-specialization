/**
 * Author: Mohit Sakhuja
 * Dated: 02/09/2018
 *
 * Contains test declarations for testing the operations of a binary search
 * tree.
 */

#ifndef TESTS_HH
#define TESTS_HH

#include <vector>

#include "Tree.hh"

void test_insertion(vector<int> &array, Tree &tree);
void test_traversal(vector<int> &array, Tree &tree);
void test_searching(vector<int> &array, Tree &tree);
void test_selection(vector<int> &array, Tree &tree);
void test_min_max(vector<int> &array, Tree &tree);
void test_predecessor(vector<int> &array, Tree &tree);
void test_successor(vector<int> &array, Tree &tree);
void test_rank(vector<int> &array, Tree &tree);
void test_deletion(vector<int> &array, Tree &tree);
void test_clear_empty_size(vector<int> &array, Tree &tree);

#endif
