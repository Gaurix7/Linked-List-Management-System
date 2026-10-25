// Main.cpp - entry point of the Linked List Management System.
// Compile ONLY this file; it pulls in the other two with #include.
//   g++ src/Main.cpp -o linkedlist
#include <iostream>
#include "SinglyLinkedList.cpp"
#include "DoublyLinkedList.cpp"
using namespace std;

// Option 3: compare Singly vs Doubly (table + live demo on the same data)
void compareLists() {
    cout << "\n==================================================\n"
         << " SINGLY vs DOUBLY LINKED LIST\n"
         << "==================================================\n"
         << "Feature                 Singly            Doubly\n"
         << "--------------------------------------------------\n"
         << "Pointers per node       1 (next)          2 (prev, next)\n"
         << "Memory per node         Less              More\n"
         << "Traversal direction     Forward only      Forward + Backward\n"
         << "Insert at beginning     O(1)              O(1)\n"
         << "Insert at end           O(n) (no tail)    O(1) (with tail)\n"
         << "Delete from end         O(n)              O(1) (with tail)\n"
         << "Delete a given node     Needs prev node   Direct (has prev)\n"
         << "Reverse                 O(n), O(1) space  O(n), O(1) space\n"
         << "Implementation          Simpler           More pointer updates\n"
         << "--------------------------------------------------\n"
         << "Sizes on this machine: SNode = " << sizeof(SNode)
         << " bytes, DNode = " << sizeof(DNode) << " bytes\n";

    cout << "\n--- Live demo: same data 40, 10, 30, 20, 50 in both lists ---\n";
    SinglyLinkedList s;
    DoublyLinkedList d;
    int vals[] = {40, 10, 30, 20, 50};
    cout.setstate(ios::failbit);                       // hide "inserted" messages
    for (int v : vals) { s.insertAtEnd(v); d.insertAtEnd(v); }
    cout.clear();                                      // turn output back on

    cout << "\nSingly (can go forward only):\n  ";
    s.display();
    cout << "Doubly forward:\n  ";
    d.displayForward();
    cout << "Doubly backward:\n  ";
    d.displayBackward();

    cout.setstate(ios::failbit);
    s.sort(); d.sort();
    s.reverse(); d.reverse();
    cout.clear();
    cout << "\nAfter sort + reverse:\n  Singly: ";
    s.display();
    cout << "  Doubly forward : ";
    d.displayForward();
    cout << "  Doubly backward: ";
    d.displayBackward();
}

int main() {
    SinglyLinkedList singly;   // lists live here so data is kept when you
    DoublyLinkedList doubly;   // return to the main menu
    int choice;

    do {
        cout << "\n==================================================\n"
             << " LINKED LIST MANAGEMENT SYSTEM\n"
             << "==================================================\n"
             << "1. Singly Linked List\n"
             << "2. Doubly Linked List\n"
             << "3. Compare Singly vs Doubly Linked List\n"
             << "4. Exit\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: singlyMenu(singly); break;
            case 2: doublyMenu(doubly); break;
            case 3: compareLists();     break;
            case 4: cout << "Thank you! Exiting...\n"; break;
            default: cout << "Invalid choice! Please enter 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}
