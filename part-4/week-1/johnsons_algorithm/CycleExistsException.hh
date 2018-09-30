/**
 * Author: Mohit Sakhuja
 * Dated: 30/09/2018
 *
 * An exception that is thrown whenever a cycle exists in a graph.
 */

#ifndef CYCLE_EXISTS_EXCEPTION_HH
#define CYCLE_EXISTS_EXCEPTION_HH

#include <exception>

using namespace std;

struct CycleExistsException : public exception {
    const char *what(void) const throw();
};

#endif