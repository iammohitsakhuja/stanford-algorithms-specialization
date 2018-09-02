#include "helpers.hh"

int lower_bound(vector<int> &array, int element)
{
    int left  = 0;
    int right = array.size();

    while (left < right) {
        int middle = left + (right - left) / 2;
        if (element <= array[middle])
            right = middle;
        else
            left = middle + 1;
    }

    return left;
}

int upper_bound(vector<int> &array, int element)
{
    int left  = 0;
    int right = array.size();

    while (left < right) {
        int middle = left + (right - left) / 2;
        if (element < array[middle])
            right = middle;
        else
            left = middle + 1;
    }

    return left;
}
