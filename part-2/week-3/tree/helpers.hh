/**
 * Author: Mohit Sakhuja
 * Dated: 02/09/2018
 *
 * Contains declarations for utility/helper functions required for testing.
 */

#ifndef HELPERS_HH
#define HELPERS_HH

#include <vector>

using namespace std;

// Returns the index starting from which all elements are greater than or equal
// to the given element.
int lower_bound(vector<int> &array, int element);

// Returns the index start from which all elements are stricly greater than the
// given element.
int upper_bound(vector<int> &array, int element);

#endif
