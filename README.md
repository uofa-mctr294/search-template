# searching

## Introduction

In another lab you will learn about sorting. Sorting data can make finding relevant data trivial, and it is for this reason databases often include pre-sorted arrays of indices called indexes that allow for easy searching. Your computer's filesystem is one such example of an indexed database. However, creating these indexes can be expensive and time consuming if a database is big enough, especially if items are constantly being added and removed.

When full sorting is prohibitively expensive, we need to reconsider the data structures we use to store data. ['Big O' Notation](https://www.bigocheatsheet.com/) describes the asymptotic computational time of algorithms as the size of data increases. Most sorting algorithms have worst case time complexities of `O(n log(n))` or worse. If we are sorting just for the sake of searching, then it might be better to choose a more searchable data structure to begin with.

Linked Lists, Hash Tables, and Binary Search Trees are a few of the data structures that are commonly used to improve data manipulation times. Whether to use any of these structures or just regular arrays will be informed by the requirements of your situation.

Linked Lists organize data into nodes, where each node contains a reference (pointer) to the next node in the sequence. Unlike arrays which store data in contiguous memory, linked lists allow data to be scattered in memory. This makes accessing an arbitrary element slower (O(n)) since you must traverse from the beginning, but inserting and removing elements can be much faster (O(1)) once you have a reference to the target location, as you only need to update pointers rather than shifting array elements.

Hash Tables use a hashing function (an easily computable function that outputs a deterministic, preferably irregular integer) to map keys to indices in an array, allowing for on average, easy lookup, insertion, and deletion times (O(1)). When multiple keys hash to the same index (a collision), they are typically stored in a linked list at that index. This makes hash tables very efficient for scenarios where you need fast lookups with minimal overhead.

Binary Search Trees organize data in a tree structure where each node has at most two children, with the left subtree containing smaller values and the right subtree containing larger values. This organization enables moderately fast search, insertion, and deletion in balanced trees (O(log n)), making them efficient for maintaining sorted data while allowing dynamic updates.

## Requirements

Implement the following data structures. Class signatures are provided in `src/search/search.hpp`. A sample driver is provided in `src/main.cpp`.

- Create a Singly Linked List
- Create a Hash Map
  - You can use `y = x mod 'mapsize'` as your hashing function
  - Use your Singly Linked List as the storage for each bucket in the map
- Create a Binary Search Tree
  - All values on the left side of a subtree should be less than the root node, and all values on the right side should be greater

You are also expected to add a series of unit tests to `tests/test_search.cpp`. Test the functionality of basic operations and data manipulations using your data structures, and consider what edge cases may arise.

## Testing Requirements

- For the sake of testing we require that all your source files are placed in `src`.
- We also require that nothing in `tests/test_search.cpp` and `src/search.hpp` is removed. You may feel free to add to this file or add additional files to this directory, as long as testing continues to build and run. Any additional changes may require you to make changes to `CMakeLists.txt`
- You will need to provide implementations for all the class method declarations without definitions in `src/search.hpp`.
- Your classes will be tested with [valgrind](https://valgrind.org/) to check for invalid memory access, or allocated memory that is not cleaned up on class destruction. If you are on Windows you can enable an address anitizer during building
- Categorize your tests with either 'ListSLTest', 'HashMapTest', 'BinarySearchTreeTest' or 'MiscTest'.
  - Google tests headers are of the form `TEST(TestCategory, TestName)`

## Bonus

- Create a Doubly Linked List
- Create an AVL Tree

### Hints

- `std::optional` allows you to express that a value may not be obtainable, when implementing methods consider under what conditions you may not be able to return a value.

#### For Informational Purposes

- While being aware of asymptotic time complexity ('Big O') is important, it is generally only relevant for large datasets, especially as they don't take into account constant overhead. If you know your dataset will have less than ~100 items, these types of considerations are typically pointless, and it is more important to focus on code clarity and expediency.
- For more performant code, it is typically better to do all your allocations at once. Most Standard Library implementations of these data structures use a simple array with a set 'capacity' as underlying storage, and reallocate if that capacity is exceeded.  
  - For this assignment it is perfectly fine to do your [de]allocations as needed, but this will requires managing the lifetime of each individual object

## Building

```shell
cmake -S . -B build
#add -DENABLE_ASAN=ON to enable address sanitization
cmake --build build --config Debug
build\Debug\search_app.exe
```

## Testing

[Build](#building)

```shell
ctest --test-dir build -C Debug
Add -V for verbose testing
```
