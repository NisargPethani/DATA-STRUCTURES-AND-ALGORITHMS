# B+ Tree

Implemented the B+ tree, which is used in the SQL range queries.
Programming Language: ​ Python

**Not used any inbuilt data structures to handle these queries**


## Implementation

1. Order of tree can change changing the `order` variable in line no 3 in file [b+_tree](./b+_tree.py).

2. Implemented a B+ tree to handle the following type of queries
    1. INSERT X - insert X into the B+ tree
    2. FIND X - print YES if X is already inserted, else NO
    3. COUNT X - print number of occurrences of X in B+tree
    4. RANGE X Y - print number of elements in range x to y (both x and y included)
    5. DISPLAY - To display tree

3. Constraints:
    1. -10^9 <= X <= 10^9, -10^9 <= Y <= 10^9
    2. The number of queries will be less than 10^6.

4. Input:
    1. The input argument consists of a file name.
    2. Each line in the file consists of one of the above-mentioned queries.

5. Output:
    1. Writen outputs of the corresponding queries in a separate file and command-line.

6. Run command:
    ```
    python3 b+_tree.py input.txt output.txt
    ```

