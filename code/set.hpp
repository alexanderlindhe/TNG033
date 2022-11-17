#pragma once

#include <iostream>
#include <vector>
#include <cassert>  //assert

// Class Set represents a set of integers using an increasingly sorted singly-linked list
class Set {
public:
    // Default constructor
    Set();

    // Constructor: create a singleton {v}
    explicit Set(int v);

    // Constructor: create a set with the elements in V
    // V is not sorted and may contain repeated elements
    explicit Set(const std::vector<int>& V);

    // Copy constructor
    Set(const Set& b);

    // Assignment operator
    Set& operator=(Set b);

    // Destructor
    ~Set();

    bool member(int x) const;         // Test if x is an element of the set
    bool empty() const;               // Test if set is empty
    std::size_t cardinality() const;  // Return number of elements in the set

    // Overloaded comparison operators
    bool operator<=(const Set& b) const;
    bool operator==(const Set& b) const;
    bool operator!=(const Set& b) const;
    bool operator<(const Set& b) const;

    // Overloaded operators
    // A new set is returned
    Set operator+(const Set& b) const;  // Set union
    Set operator*(const Set& b) const;  // Set intersection
    Set operator-(const Set& b) const;  // Set difference
    Set operator-(int x) const;         // Set difference with set {x}

    // Return number of existing nodes
    // Used only for debug purposes
    static std::size_t get_count_nodes();

private:
    /* ***************************************************
     * Class Node is private to class Set
     * All class Node members are public to class Set
     * *************************************************** */
    class Node {
    public:
        // Constructor
        Node(int nodeVal = 0, Node* nextPtr = nullptr) : value{ nodeVal }, next{ nextPtr } {
            ++count_nodes;
        }

        // Destructor
        ~Node() {
            --count_nodes;
            assert(count_nodes >= 0);  // number of existing nodes can never be negative
        }

        int value;
        Node* next;

        // Total number of existing nodes -- use only to help to detect bugs in the code
        // Cannot be used in the implementation of the member functions
        static std::size_t count_nodes;

        friend std::ostream& operator<<(std::ostream& os, const Set& b);
    };
    /* *************************************************** */

    Node* head;  // points to the first node
                 // Note: first node is a dummy node of the list

    std::size_t counter;  // number of elements in the Set



    friend std::ostream& operator<<(std::ostream& os, const Set& b);

    /* Add Auxiliarly functions below */

    void insert(Node* ptr, int value);

    void insert(int value);

    void remove(Node* ptr);


};
