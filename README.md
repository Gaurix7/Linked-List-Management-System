# Linked List Management System

## Objective
A menu-driven console application that implements a **Singly Linked List** and a **Doubly Linked List** from scratch (no arrays, no `std::list`/`vector`) to practice core Data Structures concepts: pointer manipulation, traversal, insertion, deletion, searching, sorting and reversal. Built as a 2nd-year DSA mini project.

## Language Used: C++
Standard C++11 (tested with g++ 13). No external libraries.

## Features
- Fully menu-driven, with input validation (typing letters instead of numbers will not crash the program)
- 19 operations on the Singly Linked List and 20 on the Doubly Linked List
- Every operation is a separate method
- Edge cases handled: empty list, one-node list, invalid positions, missing values, duplicates, zero and negative values
- Side-by-side **Singly vs Doubly comparison** (table + live demo)
- No memory leaks: nodes are freed by `delete` and by the class destructor

## Singly Linked List
Each node holds `data` and a `next` pointer. Only the `head` is stored, so insertion/deletion at the end needs traversal, which is O(n).

## Doubly Linked List
Each node holds `data`, `prev` and `next`. Both `head` and `tail` are stored, so insertion/deletion at the end is O(1) and the list can be displayed backward.

## Operations
| # | Singly Linked List | Doubly Linked List |
|---|---|---|
| 1-5 | Insert at Beginning / End / Position / After a Node / Before a Node | same |
| 6-9 | Delete from Beginning / End / Position / by Value | same |
| 10-11 | Search, Update | same |
| 12-13 | Display | Display Forward, Display Backward |
| 14-16 | Count, Max, Min | same |
| 17 | Find Middle (slow/fast pointers) | same |
| 18 | Reverse | same (swaps `prev`/`next` and `head`/`tail`) |
| 19 | Sort (Bubble Sort, swaps data) | same |
| 20 | Remove Duplicates (keeps first occurrence) | same |

**Design decisions**
- Positions are **1-based**.
- *Insert After/Before*, *Delete by Value*, *Search* and *Update* act on the **first** matching node.
- *Find Middle*: for an even number of nodes the **second** middle node is returned (e.g. `10,20,30,40` -> `30`).
- Insert Before/After and Delete use a single helper path so `head`/`tail` are always updated correctly.

## How to Run
Requires a C++ compiler (g++ / MinGW / clang).

```bash
git clone <your-repo-url>
cd Linked-List-Management-System
g++ -std=c++11 src/Main.cpp -o linkedlist
./linkedlist          # Windows: linkedlist.exe
```
`Main.cpp` includes `SinglyLinkedList.cpp`, `DoublyLinkedList.cpp` and `Utils.h`, so **only `Main.cpp` has to be compiled**.

## Sample Output
```
Singly Linked List
Before:      40 -> 10 -> 30 -> 20 -> 50 -> NULL
After Sort:  10 -> 20 -> 30 -> 40 -> 50 -> NULL
After Reverse: 50 -> 40 -> 30 -> 20 -> 10 -> NULL

Doubly Linked List
Forward:  NULL <- 40 <-> 10 <-> 30 <-> 20 <-> 10 -> NULL
Backward: NULL <- 10 <-> 20 <-> 30 <-> 10 <-> 40 -> NULL
```
A complete run is saved in [`sample-output/output.txt`](sample-output/output.txt).

## Time Complexity
| Operation | Singly | Doubly |
|---|---|---|
| Insert at Beginning | O(1) | O(1) |
| Insert at End | O(n) (no tail) | O(1) (tail) |
| Insert at Position | O(n) | O(n) |
| Delete from Beginning | O(1) | O(1) |
| Delete from End | O(n) | O(1) |
| Delete by Position / Value | O(n) | O(n) |
| Search / Display / Count / Min / Max / Middle | O(n) | O(n) |
| Reverse | O(n), O(1) extra space | O(n), O(1) extra space |
| Bubble Sort | O(n^2) | O(n^2) |
| Remove Duplicates (simple) | O(n^2) | O(n^2) |

## Author
Gauri Rawat
