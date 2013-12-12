#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <vector>

// Assume the elements of the vector are already in order
// Find the position where value could be added to keep
//    everything in order, and insert it there.
// Return the position where it was inserted
template <typename T>
int addInOrder (std::vector<T>& vec, T value)
{
  // Make room for the insertion
  int toBeMoved = vec.size() - 1;
  vec.push_back (value); // add a space at the end of the vector
  while (toBeMoved >= 0 && value < vec[toBeMoved]) {
    vec[toBeMoved+1] = vec[toBeMoved];
    --toBeMoved;
  }
  // Insert the new value
  vec[toBeMoved+1] = value;
  return toBeMoved+1;
}


// Search a vector for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqSearch(const std::vector<T>& list, T searchItem)
{
    int loc;

    for (loc = 0; loc < list.size(); loc++)
        if (list[loc] == searchItem)
            return loc;

    return -1;
}


// Search an ordered vector for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int seqOrderedSearch(const std::vector<T>& list, T searchItem)
{
    int loc = 0;

    while (loc < list.size() && list[loc] < searchItem)
      {
       ++loc;
      }
    if (loc < list.size() && list[loc] == searchItem)
       return loc;
    else
       return -1;
}





// Search an ordered array for a given value, returning the index where 
//    found or -1 if not found.
template <typename T>
int binarySearch(const std::vector<T>& list, T searchItem)
{
    int first = 0;
    int last = list.size() - 1;
    int mid;

    bool found = false;

    while (first <= last && !found)
    {
        mid = (first + last) / 2;

        if (list[mid] == searchItem)
            found = true;
        else 
            if (searchItem < list[mid])
                last = mid - 1;
            else
                first = mid + 1;
    }

    if (found) 
        return mid;
    else
        return -1;
}





#endif
