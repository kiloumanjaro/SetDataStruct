
# Set Data Structure Implementation (C++)

This project implements the "set" data structure, which is a container that stores unique elements without any particular order while allowing for fast access. The implementation provides operations for inserting, removing, and performing various set operations such as subset verification, union, intersection, difference, and power set computation.

### Overview
This project implements the "set" data structure, which is a container that stores unique elements without any particular order while allowing for fast access. The implementation provides operations for inserting, removing, and performing various set operations such as subset verification, union, intersection, difference, and power set computation.
### Features

Implements a set as a template class, allowing different types of sets:
- `set<int>`
- `set<double>`
- `set<char>`
- `set<string>`
- `set<set<int>>` (nested sets)

Supports the following operations:
- **Insert**: Add an element to the set.
- **Remove**: Delete an element from the set.
- **Subset**: Check if one set is a subset of another.
- **Union**: Compute the union of two sets.
- **Intersection**: Compute the intersection of two sets.
- **Difference**: Compute the difference between two sets.
- **Power Set**: Generate the power set of a given set.


### Constraints
The implementation is in C++.

The built-in set data structure from the C++ Standard Library may be used, but only for insert, remove, and getter/setter methods.

The set operations (subset, union, intersection, difference, power set) must be manually implemented.

The program reads input from a file (mpa1.in) and processes multiple test cases or directly from a user input.

The program outputs results directly to the console.
### Input Format
- The first line of the input file specifies the number of test cases.
- Each test case consists of:

    1. A number indicating the type of sets to be created:

            1: Integer set

            2: Double set (values rounded to 2 decimal places)

            3: Character set

            4: String set

            5: Set of sets (an additional number specifies the type of elements inside the nested set)

    2. Two lines specifying the default elements of the two sets.

    3. A number indicating how many operations will be performed.

    4. A sequence of operations, each specified by an operation code followed by required parameters.

        #### Example Input File (mpa1.in)
    ```
    cpp
    4
    1
    1 5 7 8
    10 -2 4 5
    3
    1 1 8
    1 2 7
    3
    4
    hello abcd wxyz
    world wxyz abcd lmno
    4
    1 1 world
    2 2 world
    5
    7 2
    5 1
    {1,2,3} {1,2} {7,8,9}
    {1,2} {1,2,5} {7,8,9,10}
    2
    2 2 {7,8,9,10}
    7 2
    ```
### Operations and Expected Output

Insert (1): Insert an element into a specified set.
```
Example: 1 1 8 → {1,5,7,8}
```

Remove (2): Remove an element from a specified set.
```
Example: 2 2 world → {hello,abcd,wxyz}
```

Subset (3): Check if the first set is a subset of the second.
```
Example: 3 → false

```

Union (4): Compute the union of two sets.
```
Example: 4 → {hello,abcd,wxyz,world}
```

Intersection (5): Compute the intersection of two sets.
```
Example: 5 → {wxyz,abcd,lmno}
```

Difference (6): Compute Set1 - Set2.
```
Example: 6 → {abcd,wxyz}
```

Power Set (7): Generate the power set of a specified set.
```
Example: 7 2 → {empty,{wxyz},{abcd},{lmno},{wxyz,abcd},{wxyz,lmno},{abcd,lmno},{wxyz,abcd,lmno}}
```



#### Sample Output
```
{1,5,7,8}
{10,-2,4,5,7}
false
{hello,abcd,wxyz,world}
{wxyz,abcd,lmno}
{abcd,wxyz}
{empty,{wxyz},{abcd},{lmno},{wxyz,abcd},{wxyz,lmno},{abcd,lmno},{wxyz,abcd,lmno}}
{{1,2},{1,2,5}}
{empty,{{1,2}},{{1,2,5}},{{1,2},{1,2,5}}}
{empty,{{a}},{{x,y}},{{0,1,2}},{{a},{x,y}},{{a},{0,1}},{{x,y},{0,1,2}},{{a},{x,y},{0,1,2}}}
{empty,{{a}},{{a,b}},{{a,b,c}},{{0}},{{1}},{{a},{a,b}},{{a},{a,b,c}},{{a},{0}},{{a},{1}},{{a,b},{a,b,c}},{{a,b},{0}},{{a,b},{1}},{{a,b,c},{0}},{{a,b,c},{1}},{{0},{1}},{{a},{a,b},{a,b,c}},{{a},{a,b},{0}},{{a},{a,b},{1}},{{a},{a,b,c},{0}},{{a},{a,b,c},{1}},{{0},{1}},{{a},{a,b},{a,b,c},{0},{1}}}
```
### Compilation and Execution
#### Compilation
To compile the program, use the following command:
```
g++ -std=c++17 set_implementation.cpp -o set_program
```

To run the input file version of the program, use:
```
./set_program < mpa1.in
```

### Future Improvements
- Extend support for additional types such as float.

- Implement an optimized hashing strategy for faster set operations.

- Provide an interactive mode for manual testing.


#### Sample Output
```
{1,5,7,8}
{10,-2,4,5,7}
false
{hello,abcd,wxyz,world}
{wxyz,abcd,lmno}
{abcd,wxyz}
{empty,{wxyz},{abcd},{lmno},{wxyz,abcd},{wxyz,lmno},{abcd,lmno},{wxyz,abcd,lmno}}
{{1,2},{1,2,5}}
{empty,{{1,2}},{{1,2,5}},{{1,2},{1,2,5}}}
{empty,{{a}},{{x,y}},{{0,1,2}},{{a},{x,y}},{{a},{0,1}},{{x,y},{0,1,2}},{{a},{x,y},{0,1,2}}}
{empty,{{a}},{{a,b}},{{a,b,c}},{{0}},{{1}},{{a},{a,b}},{{a},{a,b,c}},{{a},{0}},{{a},{1}},{{a,b},{a,b,c}},{{a,b},{0}},{{a,b},{1}},{{a,b,c},{0}},{{a,b,c},{1}},{{0},{1}},{{a},{a,b},{a,b,c}},{{a},{a,b},{0}},{{a},{a,b},{1}},{{a},{a,b,c},{0}},{{a},{a,b,c},{1}},{{0},{1}},{{a},{a,b},{a,b,c},{0},{1}}}
```

## Authors

- [@kiloumanjaro](https://github.com/kiloumanjaro)


