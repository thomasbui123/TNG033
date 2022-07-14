// =======================================================
// Exerc1
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, liU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

/********************************
 * Class List definition         *
 *********************************/

class List {
public:
    // Default constructor
    List();

    // Exercise a -- same as August exam, 2021
    List(const std::vector<int>& elements, const std::vector<int>& rep);

    // Destructor
    ~List();

    // Exercise b
    void unique();

    // Copy constructor disabled
    List(const List& source) = delete;

    // Assignment operator disabled
    List& operator=(const List& source) = delete;

    friend std::ostream& operator<<(std::ostream& os, const List& L);

private:
    class Node {
    public:
        // Constructor
        Node(int i, Node* ptr = nullptr) : value{i}, next{ptr} {
        }

        int value;
        Node* next;

        friend std::ostream& operator<<(std::ostream& os, const List& L);
    };

    Node* head;
};

/*****************************************************
 * Class List member functions implementation         *
 ******************************************************/

// Default constructor
List::List()
    : head{new Node{0, nullptr}}  // dummy node
{
}

// Destructor
List::~List() {
    Node* temp = head->next;

    while (temp != nullptr) {
        delete head;
        head = temp;
        temp = temp->next;
    }
    delete head;

    // cout << "Destructor called ..." << "\n";
}

// Exercise a
List::List(const std::vector<int>& elements, const std::vector<int>& rep) : List() {
    assert(elements.size() == rep.size());  // not required

    Node* last{head};
    for (std::size_t i = 0; i < elements.size(); ++i) {
        for (int k = 0; k < rep[i]; ++k) {
            last->next = new Node(elements[i]);
            last = last->next;
        }
    }
}

// Exercise b
void List::unique() {
    Node* ptr1{head->next};

    while (ptr1 != nullptr) {
        if (Node * ptr2{ptr1->next}; ptr2 != nullptr && ptr2->value == ptr1->value) {
            ptr1->next = ptr2->next;
            delete ptr2;
        } else {
            ptr1 = ptr1->next;
        }
    }
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

    List L0;

    List L1(std::vector<int>{2, 4, 6, 8}, std::vector<int>{1, 1, 1, 1});
    std::cout << "List L1: " << L1 << '\n';  // List L1: 2 4 6 8

    List L2(std::vector<int>{3, 5, 7}, std::vector<int>{2, 1, 2});
    std::cout << "List L2: " << L2 << '\n';  // List L1: 3 3 5 7 7

    List L3(std::vector<int>{1, 10, 6, 8, 10}, std::vector<int>{3, 1, 2, 2, 3});
    std::cout << "List L3: " << L3 << '\n';  // List L1: 1 1 1 10 6 6 8 8 10 10 10

    /*********************************************
     * Test 2: unique                            *
     **********************************************/
    std::cout << "\n** Test 2: unique\n\n";

    L0.unique();
    std::cout << "List L0: " << L0 << '\n';  // List L0: The list is empty!!

    L1.unique();
    std::cout << "List L1: " << L1 << '\n';  // List L1: 2 4 6 8

    L2.unique();
    std::cout << "List L2: " << L2 << '\n';  // List L2: 3 5 7

    L3.unique();
    std::cout << "List L3: " << L3 << '\n';  // List L3: 1 10 6 8 10
}
