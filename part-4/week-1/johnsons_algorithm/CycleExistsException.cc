#include "CycleExistsException.hh"

const char *CycleExistsException::what(void) const throw()
{
    return "Cycle exists!";
}