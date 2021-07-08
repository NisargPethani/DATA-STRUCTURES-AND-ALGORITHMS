# EXTERNAL SORTING

External Sorting is a class of algorithms used to deal with massive amounts of data that do not fit in memory.

This repository aims at implementing one such type: 
- K-Way merge sort algorithm to sort a very large array. This algorithm is a perfect example of the use of divide and conquer where with limited resources large problems are tackled by breaking the problem space into small computable subspaces and then operations are done on
them.

**Not used any in-built data structures**

## IMPLEMENTATION
1. Input Constraints:
    1. A file containing a large unsorted list of integers (Will not fit in your usual Laptop
    RAM).

2. Output: 
    1. A file containing non-Descending sorted list of the given integers

3. Input Format: 
    - Code should take two arguments.
    - First is the name of input file.
    - Second is name of output file.
    - Example Format: 
    ```
    gcc code.cpp
    ./a.out input.txt output.txt
    ```

4. Generation of unsorted file:
    - To generate the unsorted file, python script [generate_input.py](./generate_input.py) is uploaded. It contains all the instructions required to run it.