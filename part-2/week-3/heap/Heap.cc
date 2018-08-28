#include "Heap.hh"

void Heap::push(int element)
{
    this->array.push_back(element);
    this->bubble_up();
}

void Heap::pop(void)
{
    if (!this->empty()) {
        this->swap(0, this->array.size() - 1);
        this->array.pop_back();
        this->bubble_down(0);
    }
}

int Heap::top(void)
{
    if (this->empty())
        return INT_MIN;

    return this->array.front();
}

bool Heap::empty(void)
{
    return this->array.empty();
}

int Heap::size(void)
{
    return this->array.size();
}

// Private helper functions.
int Heap::get_left_child_index(int index)
{
    return 2 * index + 1;
}

int Heap::get_right_child_index(int index)
{
    return 2 * (index + 1);
}

int Heap::get_parent_index(int index)
{
    return (index - 1) / 2;
}

bool Heap::has_left_child(int index)
{
    return get_left_child_index(index) < this->size();
}

bool Heap::has_right_child(int index)
{
    return get_right_child_index(index) < this->size();
}

bool Heap::has_parent(int index)
{
    return get_parent_index(index) >= 0;
}

int Heap::left_child(int index)
{
    if (!this->has_left_child(index))
        return INT_MAX;

    return this->array[get_left_child_index(index)];
}

int Heap::right_child(int index)
{
    if (!this->has_right_child(index))
        return INT_MAX;

    return this->array[get_right_child_index(index)];
}

int Heap::parent(int index)
{
    if (!this->has_parent(index))
        return INT_MIN;

    return this->array[get_parent_index(index)];
}

void Heap::swap(int first_index, int second_index)
{
    int temp                  = this->array[first_index];
    this->array[first_index]  = this->array[second_index];
    this->array[second_index] = temp;
}

void Heap::bubble_up(void)
{
    // Get the current index of the last element.
    int curr_index = this->size() - 1;

    // While the current element has a parent, and the value at the current
    // element is less than the value of the parent.
    while (this->has_parent(curr_index)
        && this->array[curr_index] < this->parent(curr_index)) {
        // Get parent index.
        int parent_index = get_parent_index(curr_index);

        // Swap the current element with its parent element.
        this->swap(curr_index, parent_index);

        curr_index = parent_index;
    }
}

void Heap::bubble_down(int curr_index)
{
    while (this->has_left_child(curr_index)) {
        // Get the index of the smaller child.
        int smaller_child_index = get_left_child_index(curr_index);

        if (this->has_right_child(curr_index)
            && this->right_child(curr_index) < this->left_child(curr_index))
            smaller_child_index = get_right_child_index(curr_index);

        if (this->array[smaller_child_index] < this->array[curr_index]) {
            this->swap(curr_index, smaller_child_index);
            curr_index = smaller_child_index;
        } else {
            break;
        }
    }
}

void Heap::heapify(vector<int> array)
{
    this->array.resize(array.size());

    // First copy all elements.
    for (int i = 0, size = array.size(); i <= size; i++)
        this->array[i] = array[i];

    for (int i = this->array.size() - 1; i >= 0; i--)
        this->bubble_down(i);
}
