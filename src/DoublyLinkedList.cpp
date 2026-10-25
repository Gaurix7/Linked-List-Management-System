// DoublyLinkedList.cpp
// Doubly Linked List: every node stores data + pointers to the PREVIOUS and NEXT node.
// We keep both a head AND a tail pointer, so insert/delete at the end is O(1).
#pragma once
#include <iostream>
#include "Utils.h"
using namespace std;

// ---------------------------------------------------------------
// Node structure
// ---------------------------------------------------------------
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int v) : data(v), prev(nullptr), next(nullptr) {}
};

// ---------------------------------------------------------------
// Doubly Linked List class
// ---------------------------------------------------------------
class DoublyLinkedList {
private:
    DNode* head;   // first node
    DNode* tail;   // last node

    // Private helper: safely unlink and delete ANY node (fixes prev, next, head, tail).
    // Used by delete-by-position, delete-by-value and remove-duplicates.
    void removeNode(DNode* node) {
        if (node->prev != nullptr) node->prev->next = node->next;
        else                       head = node->next;          // node was head
        if (node->next != nullptr) node->next->prev = node->prev;
        else                       tail = node->prev;          // node was tail
        delete node;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    int length() const {
        int n = 0;
        for (DNode* t = head; t != nullptr; t = t->next) n++;
        return n;
    }

    // ---------------- INSERTION ----------------

    // 1. Insert at Beginning - O(1)
    void insertAtBeginning(int val) {
        DNode* newNode = new DNode(val);
        newNode->next = head;
        if (head != nullptr) head->prev = newNode;
        else                 tail = newNode;       // list was empty
        head = newNode;
        cout << val << " inserted at beginning.\n";
    }

    // 2. Insert at End - O(1) thanks to tail
    void insertAtEnd(int val) {
        DNode* newNode = new DNode(val);
        if (tail == nullptr) {                     // list was empty
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        cout << val << " inserted at end.\n";
    }

    // 3. Insert at Position (1-based)
    void insertAtPosition(int val, int pos) {
        int n = length();
        if (pos < 1 || pos > n + 1) {
            cout << "Invalid position! Valid range is 1 to " << n + 1 << ".\n";
            return;
        }
        if (pos == 1)     { insertAtBeginning(val); return; }
        if (pos == n + 1) { insertAtEnd(val);       return; }

        DNode* temp = head;
        for (int i = 1; i < pos - 1; i++) temp = temp->next;   // node at (pos-1)
        DNode* newNode = new DNode(val);
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        cout << val << " inserted at position " << pos << ".\n";
    }

    // 4. Insert After a Node (first matching value)
    void insertAfter(int target, int val) {
        DNode* temp = head;
        while (temp != nullptr && temp->data != target) temp = temp->next;
        if (temp == nullptr) {
            cout << "Value " << target << " not found. Nothing inserted.\n";
            return;
        }
        DNode* newNode = new DNode(val);
        newNode->prev = temp;
        newNode->next = temp->next;
        if (temp->next != nullptr) temp->next->prev = newNode;
        else                       tail = newNode;   // inserted after the old tail
        temp->next = newNode;
        cout << val << " inserted after " << target << ".\n";
    }

    // 5. Insert Before a Node (first matching value)
    void insertBefore(int target, int val) {
        DNode* temp = head;
        while (temp != nullptr && temp->data != target) temp = temp->next;
        if (temp == nullptr) {
            cout << "Value " << target << " not found. Nothing inserted.\n";
            return;
        }
        if (temp == head) {                    // target is the head
            DNode* first = new DNode(val);
            first->next = head;
            head->prev = first;
            head = first;
            cout << val << " inserted before " << target << ".\n";
            return;
        }

        DNode* newNode = new DNode(val);
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        cout << val << " inserted before " << target << ".\n";
    }

    // ---------------- DELETION ----------------

    // 6. Delete from Beginning - O(1)
    void deleteFromBeginning() {
        if (head == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        cout << head->data << " deleted from beginning.\n";
        removeNode(head);
    }

    // 7. Delete from End - O(1)
    void deleteFromEnd() {
        if (tail == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        cout << tail->data << " deleted from end.\n";
        removeNode(tail);
    }

    // 8. Delete from Position (1-based)
    void deleteFromPosition(int pos) {
        int n = length();
        if (n == 0) { cout << "List is empty! Nothing to delete.\n"; return; }
        if (pos < 1 || pos > n) {
            cout << "Invalid position! Valid range is 1 to " << n << ".\n";
            return;
        }
        DNode* temp = head;
        for (int i = 1; i < pos; i++) temp = temp->next;
        cout << temp->data << " deleted from position " << pos << ".\n";
        removeNode(temp);
    }

    // 9. Delete by Value (first match)
    void deleteByValue(int val) {
        if (head == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        DNode* temp = head;
        while (temp != nullptr && temp->data != val) temp = temp->next;
        if (temp == nullptr) { cout << "Value " << val << " not found.\n"; return; }
        removeNode(temp);
        cout << val << " deleted.\n";
    }

    // ---------------- SEARCH / UPDATE / DISPLAY ----------------

    // 10. Search
    void search(int val) const {
        int pos = 1;
        for (DNode* t = head; t != nullptr; t = t->next, pos++) {
            if (t->data == val) {
                cout << val << " found at position " << pos << ".\n";
                return;
            }
        }
        cout << val << " not found in the list.\n";
    }

    // 11. Update
    void update(int oldVal, int newVal) {
        for (DNode* t = head; t != nullptr; t = t->next) {
            if (t->data == oldVal) {
                t->data = newVal;
                cout << oldVal << " updated to " << newVal << ".\n";
                return;
            }
        }
        cout << "Value " << oldVal << " not found. Nothing updated.\n";
    }

    // 12. Display Forward  (uses next links)
    void displayForward() const {
        if (head == nullptr) { cout << "List is empty! (NULL)\n"; return; }
        cout << "NULL <- ";
        for (DNode* t = head; t != nullptr; t = t->next) {
            cout << t->data;
            if (t->next != nullptr) cout << " <-> ";
        }
        cout << " -> NULL\n";
    }

    // 13. Display Backward (starts at tail, uses prev links)
    void displayBackward() const {
        if (tail == nullptr) { cout << "List is empty! (NULL)\n"; return; }
        cout << "NULL <- ";
        for (DNode* t = tail; t != nullptr; t = t->prev) {
            cout << t->data;
            if (t->prev != nullptr) cout << " <-> ";
        }
        cout << " -> NULL\n";
    }

    // ---------------- ANALYSIS ----------------

    // 14. Count Nodes
    void countNodes() const {
        cout << "Total nodes: " << length() << "\n";
    }

    // 15. Find Maximum
    void findMax() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        int mx = head->data;
        for (DNode* t = head->next; t != nullptr; t = t->next)
            if (t->data > mx) mx = t->data;
        cout << "Maximum value: " << mx << "\n";
    }

    // 16. Find Minimum
    void findMin() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        int mn = head->data;
        for (DNode* t = head->next; t != nullptr; t = t->next)
            if (t->data < mn) mn = t->data;
        cout << "Minimum value: " << mn << "\n";
    }

    // 17. Find Middle - slow/fast. Even length -> SECOND middle node (same rule as singly list).
    void findMiddle() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        DNode* slow = head;
        DNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Middle element: " << slow->data << "\n";
    }

    // ---------------- REARRANGING ----------------

    // 18. Reverse - swap prev and next of EVERY node, then swap head and tail
    void reverse() {
        DNode* curr = head;
        while (curr != nullptr) {
            DNode* temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;          // old next is now stored in prev
        }
        DNode* t = head;                // swap head and tail
        head = tail;
        tail = t;
        cout << "List reversed.\n";
    }

    // 19. Sort ascending - Bubble Sort by swapping data, O(n^2)
    void sort() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Nothing to sort (list has fewer than 2 nodes).\n";
            return;
        }
        bool swapped;
        DNode* lastSorted = nullptr;
        do {
            swapped = false;
            DNode* curr = head;
            while (curr->next != lastSorted) {
                if (curr->data > curr->next->data) {
                    int t = curr->data;
                    curr->data = curr->next->data;
                    curr->next->data = t;
                    swapped = true;
                }
                curr = curr->next;
            }
            lastSorted = curr;
        } while (swapped);
        cout << "List sorted in ascending order.\n";
    }

    // 20. Remove Duplicates - keeps first occurrence, O(n^2)
    void removeDuplicates() {
        int removed = 0;
        for (DNode* curr = head; curr != nullptr; curr = curr->next) {
            DNode* runner = curr->next;
            while (runner != nullptr) {
                DNode* nextNode = runner->next;      // save before possible delete
                if (runner->data == curr->data) {
                    removeNode(runner);
                    removed++;
                }
                runner = nextNode;
            }
        }
        cout << removed << " duplicate node(s) removed.\n";
    }
};

// ---------------------------------------------------------------
// Menu for the Doubly Linked List
// ---------------------------------------------------------------
void doublyMenu(DoublyLinkedList& list) {
    int choice;
    do {
        cout << "\n********** Operation on Doubly Linked List **********\n"
             << " 1. Insert at Beginning\n"
             << " 2. Insert at End\n"
             << " 3. Insert at Position\n"
             << " 4. Insert After a Node\n"
             << " 5. Insert Before a Node\n"
             << " 6. Delete from Beginning\n"
             << " 7. Delete from End\n"
             << " 8. Delete from Position\n"
             << " 9. Delete by Value\n"
             << "10. Search\n"
             << "11. Update\n"
             << "12. Display Forward\n"
             << "13. Display Backward\n"
             << "14. Count Nodes\n"
             << "15. Find Maximum\n"
             << "16. Find Minimum\n"
             << "17. Find Middle Element\n"
             << "18. Reverse\n"
             << "19. Sort\n"
             << "20. Remove Duplicates\n"
             << "21. Exit\n";
        choice = readInt("Enter the choice:- ");

        switch (choice) {
            case 1:  list.insertAtBeginning(readInt("Enter value: ")); break;
            case 2:  list.insertAtEnd(readInt("Enter value: ")); break;
            case 3: {
                int v = readInt("Enter value: ");
                int p = readInt("Enter position (1-based): ");
                list.insertAtPosition(v, p);
                break;
            }
            case 4: {
                int t = readInt("Insert AFTER which value? ");
                int v = readInt("Enter new value: ");
                list.insertAfter(t, v);
                break;
            }
            case 5: {
                int t = readInt("Insert BEFORE which value? ");
                int v = readInt("Enter new value: ");
                list.insertBefore(t, v);
                break;
            }
            case 6:  list.deleteFromBeginning(); break;
            case 7:  list.deleteFromEnd(); break;
            case 8:  list.deleteFromPosition(readInt("Enter position (1-based): ")); break;
            case 9:  list.deleteByValue(readInt("Enter value to delete: ")); break;
            case 10: list.search(readInt("Enter value to search: ")); break;
            case 11: {
                int o = readInt("Enter old value: ");
                int n = readInt("Enter new value: ");
                list.update(o, n);
                break;
            }
            case 12: list.displayForward(); break;
            case 13: list.displayBackward(); break;
            case 14: list.countNodes(); break;
            case 15: list.findMax(); break;
            case 16: list.findMin(); break;
            case 17: list.findMiddle(); break;
            case 18: list.reverse(); break;
            case 19: list.sort(); break;
            case 20: list.removeDuplicates(); break;
            case 21: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice! Please enter 1-21.\n";
        }
    } while (choice != 21);
}
