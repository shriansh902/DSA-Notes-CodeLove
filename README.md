# DSA-Notes-CodeLove

Abstract data types used in DSA and other algorithms, explained in detail with C++ implementations.

Each topic has a short explanation, the core operations with their time complexity, and clean C++ code you can compile and run.

---

## Table of Contents

1. [About](#about)
2. [Topics Covered](#topics-covered)
3. [Repository Structure](#repository-structure)
4. [Getting Started](#getting-started)
5. [Complexity Cheat Sheet](#complexity-cheat-sheet)
6. [How to Study From This Repo](#how-to-study-from-this-repo)
7. [Contributing](#contributing)
8. [Roadmap](#roadmap)

---

## About

This repository is a personal collection of notes on **Data Structures and Algorithms (DSA)**, written in **C++**. The goal is to understand *why* each structure works, not only how to code it.

Every note aims to cover:

- **Concept**: what the structure or algorithm is and where it's used
- **Operations**: insert, delete, search, traverse, and so on
- **Complexity**: time and space, best / average / worst case
- **Code**: a readable C++ implementation with comments
- **Practice**: problems to try after reading

---

## Topics Covered

### Abstract Data Types (ADTs)

| ADT | Key idea | Typical use |
|---|---|---|
| Array / Vector | Contiguous memory, index access | Lookup by position |
| Linked List (singly, doubly, circular) | Nodes joined by pointers | Frequent insert / delete |
| Stack | LIFO (last in, first out) | Undo, recursion, expression parsing |
| Queue | FIFO (first in, first out) | Scheduling, BFS |
| Deque | Insert / remove at both ends | Sliding window problems |
| Priority Queue / Heap | Always gives min or max first | Scheduling, Dijkstra, top-K |
| Hash Table (map / set) | Key to value via hashing | Fast lookup, counting |
| Tree (Binary, BST, AVL) | Hierarchical nodes | Sorted data, hierarchies |
| Trie | Prefix tree for strings | Autocomplete, dictionaries |
| Graph | Vertices and edges | Networks, maps, dependencies |
| Disjoint Set (Union-Find) | Track connected groups | Connectivity, Kruskal's |
| Segment Tree / Fenwick Tree | Range queries and updates | Range sum / min / max |

### Algorithms

- **Searching**: linear search, binary search, search on answer
- **Sorting**: bubble, selection, insertion, merge, quick, heap, counting sort
- **Recursion and Backtracking**: subsets, permutations, N-Queens, Sudoku
- **Divide and Conquer**: merge sort, quick select
- **Greedy**: activity selection, Huffman coding, interval scheduling
- **Dynamic Programming**: memoization, tabulation, knapsack, LIS, LCS, grid DP
- **Graph Algorithms**: BFS, DFS, Dijkstra, Bellman-Ford, Floyd-Warshall, topological sort, Kruskal, Prim
- **Two Pointers and Sliding Window**
- **Bit Manipulation**
- **String Algorithms**: KMP, Rabin-Karp, Z-algorithm

### C++ Essentials Used Throughout

- Pointers, references, and dynamic memory (`new` / `delete`)
- Classes, templates, and operator overloading
- The STL: `vector`, `stack`, `queue`, `deque`, `priority_queue`, `map`, `unordered_map`, `set`, `pair`, `algorithm`
- Iterators and lambda functions

---

## Repository Structure

A suggested layout (adjust to match your folders):

```
DSA-Notes-CodeLove/
├── README.md
├── 01-arrays/
├── 02-linked-list/
├── 03-stack-queue/
├── 04-hashing/
├── 05-trees/
├── 06-heaps/
├── 07-graphs/
├── 08-recursion-backtracking/
├── 09-dynamic-programming/
├── 10-sorting-searching/
├── 11-strings/
└── 12-bit-manipulation/
```

Inside each folder, one `.md` file holds the notes and one or more `.cpp` files hold the code.

---

## Getting Started

### Requirements

- A C++ compiler supporting **C++17** or later (g++, clang++, or MSVC)
- Git

### Clone the repo

```bash
git clone https://github.com/shriansh902/DSA-Notes-CodeLove.git
cd DSA-Notes-CodeLove
```

### Compile and run a file

```bash
g++ -std=c++17 -Wall -o program 02-linked-list/singly_linked_list.cpp
./program
```

On Windows (Git Bash), run `./program.exe` or just `program`.

### Example snippet: Stack using an array

```cpp
#include <iostream>
using namespace std;

class Stack {
    int *arr;
    int top, capacity;

public:
    Stack(int size) : capacity(size), top(-1) { arr = new int[size]; }
    ~Stack() { delete[] arr; }

    void push(int x) {
        if (top == capacity - 1) { cout << "Stack overflow\n"; return; }
        arr[++top] = x;
    }
    void pop() {
        if (top == -1) { cout << "Stack underflow\n"; return; }
        top--;
    }
    int peek() { return top == -1 ? -1 : arr[top]; }
    bool empty() { return top == -1; }
};

int main() {
    Stack s(5);
    s.push(10);
    s.push(20);
    cout << s.peek() << "\n";  // 20
    s.pop();
    cout << s.peek() << "\n";  // 10
}
```

---

## Complexity Cheat Sheet

### Data structures

| Structure | Access | Search | Insert | Delete |
|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1)* | O(1)* |
| Stack / Queue | O(n) | O(n) | O(1) | O(1) |
| Hash Table | n/a | O(1) avg | O(1) avg | O(1) avg |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) |
| BST (skewed) | O(n) | O(n) | O(n) | O(n) |
| Heap | O(1) top | O(n) | O(log n) | O(log n) |

\* once the position is known

### Sorting algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|---|---|---|---|---|---|
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

### Graph algorithms

| Algorithm | Time | Use |
|---|---|---|
| BFS / DFS | O(V + E) | Traversal, connectivity |
| Dijkstra (with heap) | O((V + E) log V) | Shortest path, non-negative weights |
| Bellman-Ford | O(V · E) | Shortest path with negative weights |
| Floyd-Warshall | O(V³) | All-pairs shortest paths |
| Kruskal / Prim | O(E log V) | Minimum spanning tree |

---

## How to Study From This Repo

1. **Read the concept first.** Draw the structure on paper before looking at code.
2. **Dry run the code** with a small input and track the variables by hand.
3. **Type it out yourself** instead of copy-pasting.
4. **Solve 3 to 5 problems** per topic on LeetCode, GeeksforGeeks, Codeforces, or CSES.
5. **Revisit after a week** and re-implement from memory.

---

## Contributing

Suggestions and corrections are welcome.

1. Fork the repo
2. Create a branch: `git switch -c add-topic-name`
3. Commit your changes: `git commit -m "Add notes on topic"`
4. Push: `git push -u origin add-topic-name`
5. Open a pull request

Please keep code commented, name files clearly, and include complexity analysis in new notes.

---

## Roadmap

- [x] Basic ADTs: stack, queue, linked list
- [ ] Trees and BST operations
- [ ] Heaps and priority queues
- [ ] Graph algorithms
- [ ] Dynamic programming patterns
- [ ] Segment tree and Fenwick tree
- [ ] String algorithms
- [ ] Practice problem lists per topic

---

## Author

**Shriansh Shegokar** ([@shriansh902](https://github.com/shriansh902))

If this helped you, consider giving the repo a star.
