// =======================================================
// Exerc1
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, liU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iomanip>
#include <cassert>

/********************************
 * Class List definition         *
 *********************************/

class List {
public:
    // Exercise a
    List(int n = 0, int start_from = 0, int step = 1);

    // Copy constructor
    List(const List& source);

    // Destructor
    ~List();

    // Exercise b
    List symmetric_difference(const List& source) const;

    // Assignment operator disabled
    List& operator=(const List& source) = delete;

    friend std::ostream& operator<<(std::ostream& os, const List& L);

private:
    class Node {
    public:
        // Constructor
        Node(int i = 0, Node* ptr = nullptr) : value{i}, next{ptr} {
        }

        int value;
        Node* next;
    };

    Node* head;
};

/*****************************************************
 * Class List member functions implementation         *
 ******************************************************/

// Exercise a
List::List(int n, int start_from, int step) : head{new Node} {  // dummy node
    assert(n >= 0);                                             // not required

    Node* ptr = head;
    for (int value = start_from, i = 0; i < n; value += step, ptr = ptr->next, ++i) {
        ptr->next = new Node{value};
    }
}

List::List(const List& source) : head{new Node} {
    Node* ptr1 = source.head->next;
    Node* ptr2 = head;

    while (ptr1 != nullptr) {
        ptr2->next = new Node{ptr1->value};
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
}

// Destructor
List::~List() {
    Node* ptr = head->next;

    while (ptr != nullptr) {
        delete head;
        head = ptr;
        ptr = ptr->next;
    }
    delete head;
    // cout << "Destructor called ..." << "\n";
}

// Exercise b
// Sets *this and source are sorted increasingly
List List::symmetric_difference(const List& source) const {
    List res;
    Node* ptr1 = head;
    Node* ptr2 = source.head;
    Node* ptr3 = res.head;

    while (ptr1->next != nullptr && ptr2->next != nullptr) {
        if (ptr1->next->value < ptr2->next->value) {
            ptr3->next = new Node(ptr1->next->value);
            ptr3 = ptr3->next;
            ptr1 = ptr1->next;
        } else if (ptr2->next->value < ptr1->next->value) {
            ptr3->next = new Node(ptr2->next->value);
            ptr3 = ptr3->next;
            ptr2 = ptr2->next;
        } else {  // ptr1->next->value == ptr2->next->value
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;

            // If list values are not unique
            /*int v = ptr1->next->value;
            while (ptr1->next != nullptr && ptr1->next->value == v) {
                ptr1 = ptr1->next;
            }
            while (ptr2->next != nullptr && ptr2->next->value == v) {
                ptr2 = ptr2->next;
            }*/
            
        }
    }

    while (ptr1->next != nullptr) {
        ptr3->next = new Node(ptr1->next->value);
        ptr3 = ptr3->next;
        ptr1 = ptr1->next;
    }

    while (ptr2->next != nullptr) {
        ptr3->next = new Node(ptr2->next->value);
        ptr3 = ptr3->next;
        ptr2 = ptr2->next;
    }

    return res;
}

std::ostream& operator<<(std::ostream& os, const List& L) {
    List::Node* ptr{L.head->next};

    if (ptr == nullptr) {
        os << "The list is empty!!";
        return os;
    }
    while (ptr != nullptr) {
        os << ptr->value << " ";
        ptr = ptr->next;
    }
    return os;
}

/**************************************
 * Main function  -- test              *
 * DELIVER UNMODIFIED                  *
 ***************************************/

int main() {
    /*********************************************
     * Test 1: Constructor                       *
     **********************************************/
    std::cout << "\n** Test 1: Create some lists\n\n";

    List L0;                                 // The list is empty!
    std::cout << "List L0: " << L0 << '\n';  // List L0: The list is empty!

    List L1(4);                              // create a list with four ints starting from zero
    std::cout << "List L1: " << L1 << '\n';  // List L1: 0 1 2 3

    List L2(4, 2);                           // create a list with four ints starting from two
    std::cout << "List L2: " << L2 << '\n';  // List L2: 2 3 4 5

    const List L3(10, 3);                          // create a list with ten ints starting from three
    std::cout << "List L3: " << L3 << '\n';  // List L3: 3 4 5 6 7 8 9 10 11 12

    List L4(4, 2, 2);  // create a list with four ints starting from two and step increment of two
    std::cout << "List L4: " << L4 << '\n';  // List L4: 2 4 6 8

    List L5(4, 2, -2);  // create a list with four ints starting from two and step decrement of two
    std::cout << "List L5: " << L5 << '\n';  // List L5: 2 0 -2 -4

    /*********************************************
     * Test 2: symmetric_difference               *
     **********************************************/
    std::cout << "\n** Test 2: symmetric_difference\n\n";

    std::cout << L0.symmetric_difference(L4) << '\n';  // 2 4 6 8
    std::cout << L4.symmetric_difference(L0) << '\n';  // 2 4 6 8

    std::cout << L2.symmetric_difference(L3) << '\n';  // 2 6 7 8 9 10 11 12
    std::cout << L3.symmetric_difference(L2) << '\n';  // 2 6 7 8 9 10 11 12

    std::cout << L2.symmetric_difference(L4) << '\n';  // 3 5 6 8
    std::cout << L4.symmetric_difference(L2) << '\n';  // 3 5 6 8
}
