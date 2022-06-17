// =======================================================
// Exerc1
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, liU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iomanip>

/********************************
 * Class List definition         *
 *********************************/

class List {
public:
    //constructors
    List(int amount = 0, int start = 0, int step = 0);
    
    // Destructor
    ~List();

    // Copy constructor
    List(const List& source);

    // Assignment operator disabled
    List& operator=(const List& source) = delete;

    //symmetric
    List symmetric_difference(const List& L2) const; //Vi vill returnera en helt ny lista så ingen &.

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

    void insert(Node* p, int v){ //insert node after node pointed by p
        Node* newNode = new Node(v, p->next);
        p->next = newNode;
    }
};

/*****************************************************
 * Class List member functions implementation         *
 ******************************************************/
//Default constructor
List::List(int amount, int start, int step) : head{new Node} { //Skapar en dummy node
    Node* ptr = head;

    if (amount == 0) {
        return;
    }
    else if (step == 0) {
        for (int i = 0; i < amount; i++) {
            insert(ptr, start + i);
            ptr = ptr->next;
        }
    }
    else {
        insert(ptr, start); //insert init value
        ptr = ptr->next;

        int stepAdd = start + step;
        for (int i = 1; i < amount; i++) {
            insert(ptr, stepAdd);
            ptr = ptr->next;
            stepAdd += step;
        }
    }
}

List List::symmetric_difference(const List& L2) const {
    Node* ptr1 = head;
    Node* ptr2 = L2.head;
    List store; //New list
    Node* ptrStore = store.head;

    while (ptr1->next != nullptr && ptr2->next != nullptr) {
        if (ptr1->next->value < ptr2->next->value) {
            store.insert(ptrStore, ptr1->next->value);
            ptrStore = ptrStore->next;
            ptr1 = ptr1->next;
        }
        else if (ptr1->next->value > ptr2->next->value) {
            store.insert(ptrStore, ptr2->next->value);
            ptrStore = ptrStore->next;
            ptr2 = ptr2->next;
        }
        else {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    while (ptr1->next != nullptr) {
        store.insert(ptrStore, ptr1->next->value);
        ptrStore = ptrStore->next;
        ptr1 = ptr1->next;
    }

    while (ptr2->next != nullptr) {
        store.insert(ptrStore, ptr2->next->value);
        ptrStore = ptrStore->next;
        ptr2 = ptr2->next;
    }
    return store;



}
// Copy constructor
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

    const List L3(10, 3);                    // create a list with ten ints starting from three
    std::cout << "List L3: " << L3 << '\n';  // List L3: 3 4 5 6 7 8 9 10 11 12

    List L4(10, 2, 2);  // create a list with four ints starting from two and step increment of two
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
