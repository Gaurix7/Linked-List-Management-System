// SinglyLinkedList.cpp
// Singly Linked List: every node stores data + a pointer to the NEXT node only.
#pragma once
#include <iostream>
#include "Utils.h"
using namespace std;

// ---------------------------------------------------------------
// Node structure
// ---------------------------------------------------------------
struct SNode {
    int data;
    SNode* next;
    SNode(int v) : data(v), next(nullptr) {}
};

// ---------------------------------------------------------------
// Singly Linked List class
// ---------------------------------------------------------------
class SinglyLinkedList {
private:
    SNode* head;   // points to the first node (nullptr when list is empty)

public:
    SinglyLinkedList() : head(nullptr) {}
    ~SinglyLinkedList() { clear(); }

    // Free every node (used by the destructor)
    void clear() {
        while (head != nullptr) {
            SNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Silent helper: number of nodes (no printing)
    int length() const {
        int n = 0;
        for (SNode* t = head; t != nullptr; t = t->next) n++;
        return n;
    }

    // ---------------- INSERTION ----------------

    // 1. Insert at Beginning - O(1)
    void insertAtBeginning(int val) {
        SNode* newNode = new SNode(val);
        newNode->next = head;
        head = newNode;
        cout << val << " inserted at beginning.\n";
    }

    // 2. Insert at End - O(n) (no tail pointer)
    void insertAtEnd(int val) {
        SNode* newNode = new SNode(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            SNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
        cout << val << " inserted at end.\n";
    }

    // 3. Insert at Position (1-based) - O(n)
    void insertAtPosition(int val, int pos) {
        int n = length();
        if (pos < 1 || pos > n + 1) {
            cout << "Invalid position! Valid range is 1 to " << n + 1 << ".\n";
            return;
        }
        if (pos == 1) { insertAtBeginning(val); return; }

        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) temp = temp->next;   // stop at node (pos-1)
        SNode* newNode = new SNode(val);
        newNode->next = temp->next;
        temp->next = newNode;
        cout << val << " inserted at position " << pos << ".\n";
    }

    // 4. Insert After a Node (first matching value)
    void insertAfter(int target, int val) {
        SNode* temp = head;
        while (temp != nullptr && temp->data != target) temp = temp->next;
        if (temp == nullptr) {
            cout << "Value " << target << " not found. Nothing inserted.\n";
            return;
        }
        SNode* newNode = new SNode(val);
        newNode->next = temp->next;
        temp->next = newNode;
        cout << val << " inserted after " << target << ".\n";
    }

    // 5. Insert Before a Node (first matching value)
    void insertBefore(int target, int val) {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        if (head->data == target) {            // target is the head
            SNode* first = new SNode(val);
            first->next = head;
            head = first;
            cout << val << " inserted before " << target << ".\n";
            return;
        }
        SNode* temp = head;                    // find the node just BEFORE target
        while (temp->next != nullptr && temp->next->data != target) temp = temp->next;
        if (temp->next == nullptr) {
            cout << "Value " << target << " not found. Nothing inserted.\n";
            return;
        }
        SNode* newNode = new SNode(val);
        newNode->next = temp->next;
        temp->next = newNode;
        cout << val << " inserted before " << target << ".\n";
    }

    // ---------------- DELETION ----------------

    // 6. Delete from Beginning - O(1)
    void deleteFromBeginning() {
        if (head == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        SNode* temp = head;
        head = head->next;
        cout << temp->data << " deleted from beginning.\n";
        delete temp;
    }

    // 7. Delete from End - O(n)
    void deleteFromEnd() {
        if (head == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        if (head->next == nullptr) {           // only one node
            cout << head->data << " deleted from end.\n";
            delete head;
            head = nullptr;
            return;
        }
        SNode* temp = head;
        while (temp->next->next != nullptr) temp = temp->next;   // second-last node
        cout << temp->next->data << " deleted from end.\n";
        delete temp->next;
        temp->next = nullptr;
    }

    // 8. Delete from Position (1-based)
    void deleteFromPosition(int pos) {
        int n = length();
        if (n == 0) { cout << "List is empty! Nothing to delete.\n"; return; }
        if (pos < 1 || pos > n) {
            cout << "Invalid position! Valid range is 1 to " << n << ".\n";
            return;
        }
        if (pos == 1) { deleteFromBeginning(); return; }

        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) temp = temp->next;     // node before target
        SNode* target = temp->next;
        temp->next = target->next;
        cout << target->data << " deleted from position " << pos << ".\n";
        delete target;
    }

    // 9. Delete by Value (first match)
    void deleteByValue(int val) {
        if (head == nullptr) { cout << "List is empty! Nothing to delete.\n"; return; }
        if (head->data == val) {
            SNode* temp = head;
            head = head->next;
            delete temp;
            cout << val << " deleted.\n";
            return;
        }
        SNode* temp = head;
        while (temp->next != nullptr && temp->next->data != val) temp = temp->next;
        if (temp->next == nullptr) {
            cout << "Value " << val << " not found.\n";
            return;
        }
        SNode* target = temp->next;
        temp->next = target->next;
        delete target;
        cout << val << " deleted.\n";
    }

    // ---------------- SEARCH / UPDATE / DISPLAY ----------------

    // 10. Search - reports 1-based position of first match
    void search(int val) const {
        int pos = 1;
        for (SNode* t = head; t != nullptr; t = t->next, pos++) {
            if (t->data == val) {
                cout << val << " found at position " << pos << ".\n";
                return;
            }
        }
        cout << val << " not found in the list.\n";
    }

    // 11. Update - replace first occurrence of oldVal with newVal
    void update(int oldVal, int newVal) {
        for (SNode* t = head; t != nullptr; t = t->next) {
            if (t->data == oldVal) {
                t->data = newVal;
                cout << oldVal << " updated to " << newVal << ".\n";
                return;
            }
        }
        cout << "Value " << oldVal << " not found. Nothing updated.\n";
    }

    // 12. Display
    void display() const {
        if (head == nullptr) { cout << "List is empty! (NULL)\n"; return; }
        for (SNode* t = head; t != nullptr; t = t->next) cout << t->data << " -> ";
        cout << "NULL\n";
    }

    // ---------------- ANALYSIS ----------------

    // 13. Count Nodes
    void countNodes() const {
        cout << "Total nodes: " << length() << "\n";
    }

    // 14. Find Maximum
    void findMax() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        int mx = head->data;
        for (SNode* t = head->next; t != nullptr; t = t->next)
            if (t->data > mx) mx = t->data;
        cout << "Maximum value: " << mx << "\n";
    }

    // 15. Find Minimum
    void findMin() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        int mn = head->data;
        for (SNode* t = head->next; t != nullptr; t = t->next)
            if (t->data < mn) mn = t->data;
        cout << "Minimum value: " << mn << "\n";
    }

    // 16. Find Middle - slow/fast pointers.
    // RULE: for an even-length list we return the SECOND of the two middle nodes.
    //       (e.g. 10,20,30,40 -> 30)
    void findMiddle() const {
        if (head == nullptr) { cout << "List is empty!\n"; return; }
        SNode* slow = head;
        SNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;           // moves 1 step
            fast = fast->next->next;     // moves 2 steps
        }
        cout << "Middle element: " << slow->data << "\n";
    }

    // ---------------- REARRANGING ----------------

    // 17. Reverse - O(n) time, O(1) extra space
    void reverse() {
        SNode* prev = nullptr;
        SNode* curr = head;
        while (curr != nullptr) {
            SNode* nextNode = curr->next;   // remember next
            curr->next = prev;              // flip the link
            prev = curr;                    // move prev forward
            curr = nextNode;                // move curr forward
        }
        head = prev;
        cout << "List reversed.\n";
    }

    // 18. Sort ascending - Bubble Sort by swapping data, O(n^2)
    void sort() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Nothing to sort (list has fewer than 2 nodes).\n";
            return;
        }
        bool swapped;
        SNode* lastSorted = nullptr;
        do {
            swapped = false;
            SNode* curr = head;
            while (curr->next != lastSorted) {
                if (curr->data > curr->next->data) {
                    int t = curr->data;
                    curr->data = curr->next->data;
                    curr->next->data = t;
                    swapped = true;
                }
                curr = curr->next;
            }
            lastSorted = curr;   // largest element of this pass is now in place
        } while (swapped);
        cout << "List sorted in ascending order.\n";
    }

    // 19. Remove Duplicates - keeps first occurrence, O(n^2)
    void removeDuplicates() {
        int removed = 0;
        for (SNode* curr = head; curr != nullptr; curr = curr->next) {
            SNode* runner = curr;
            while (runner->next != nullptr) {
                if (runner->next->data == curr->data) {
                    SNode* dup = runner->next;
                    runner->next = dup->next;
                    delete dup;
                    removed++;
                } else {
                    runner = runner->next;
                }
            }
        }
        cout << removed << " duplicate node(s) removed.\n";
    }
};

// ---------------------------------------------------------------
// Menu for the Singly Linked List
// ---------------------------------------------------------------
void singlyMenu(SinglyLinkedList& list) {
    int choice;
    do {
        cout << "\n********** Operation on Singly Linked List **********\n"
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
             << "12. Display\n"
             << "13. Count Nodes\n"
             << "14. Find Maximum\n"
             << "15. Find Minimum\n"
             << "16. Find Middle Element\n"
             << "17. Reverse\n"
             << "18. Sort\n"
             << "19. Remove Duplicates\n"
             << "20. Exit\n";
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
            case 12: list.display(); break;
            case 13: list.countNodes(); break;
            case 14: list.findMax(); break;
            case 15: list.findMin(); break;
            case 16: list.findMiddle(); break;
            case 17: list.reverse(); break;
            case 18: list.sort(); break;
            case 19: list.removeDuplicates(); break;
            case 20: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice! Please enter 1-20.\n";
        }
    } while (choice != 20);
}
