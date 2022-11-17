#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set()

    : head(new Node{ 0, nullptr }), counter(0) { // deklarerar Set()

}

// Constructor for creating a set from an int
Set::Set(int v) : Set{} { 

    insert(v);       // använder insert för att sätta in önskat värde i ett skapat set

}


// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) : Set{} {

    for (int i : V) {      //skapar en lista med unika värden och i storleksordning

        Node* ptr = head;

        while (ptr) {
            if (!ptr->next || ptr->next->value > i) {   //
                insert(i);
                break;
            }
            else if (ptr->next->value < i) {   // tar de
                ptr = ptr->next;
            }
            else {
                break;
            }
        }

    }

    
}

// copy constructor
Set::Set(const Set& source) : Set(){
    Node* ptr1 = source.head->next;
    Node* ptr2 = head;

    while (ptr1 != nullptr) {        //skapar ett nytt identiskt set

        insert(ptr2, ptr1->value);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {
    std::swap(head, s.head); //byter plats på första noden
    std::swap(counter, s.counter); //byter plats på antalet element

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head;
    while (ptr != nullptr) {
        head = ptr->next;
        remove(ptr);
        ptr = head;
    }

    counter = 0;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    Set temp;
    

    return counter;
}

// Test if set is empty
bool Set::empty() const {

    return (counter == 0);//sant om countern är 0
    //if (counter == 0)
    //{
    //    return true;
    //}       
    //else return false;
}

// Test if x is an element of the set
bool Set::member(int x) const {
    
    Node* temp = head->next;

    while (temp != nullptr && x != temp->value) {
        temp = temp->next;
    }

    if (temp == nullptr) {

        return false;
    }
    else {

        return true;
    }
    
}

bool Set::operator<=(const Set& b) const { //att seten har antingen minst ett gemensamt värde eller är identiska
    
    Node* ptr = head->next;

    while (ptr != nullptr) {
        if (!b.member(ptr->value)) { // om nått av värdena i this-setet inte tillhör b returnas false, 
            return false;            // om alla värden tar sig igenom hiunner while-loopen avslutas och istället returnas true
        }
        ptr = ptr->next;
    }

    return true;  // delete if needed
}

bool Set::operator==(const Set& b) const { //om this är en delmängd av b och vice verse så är de samma set, samma elemnt.
                                            // testar om de är identiska
    if (operator<=(b)) {
        if (b.operator<=(*this)) {
            return true;
        }
    }
    return false; // delete if needed
}

bool Set::operator!=(const Set& b) const { // kollar om de är identiska, om inte returnar vi true
    if (operator==(b)) {
        return false;
    }

    return true;  // delete if needed
}

bool Set::operator<(const Set& b) const { //seten har minst ett gemensamt värde, men de är inte identiska
    if (operator<=(b)) {
        if (b.counter < counter) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;  // delete if needed
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    Set temp{};
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;

    while (ptr1 != nullptr && ptr2 != nullptr) { //sorterar bort dubbletter
        if (ptr1->value < ptr2->value) {
            temp.insert(ptr1->value);
            ptr1 = ptr1->next;
        }
        else if (ptr2->value < ptr1->value) {
            temp.insert(ptr2->value);
            ptr2 = ptr2->next;
        }
        else {
            temp.insert(ptr2->value); //om båda värdena är samma, tas ett av värdena och båda går vidare till nästa element
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    while (ptr1 != nullptr) {  // stoppar in reseterande element från varje set, ifall de har olika storlekar
        temp.insert(ptr1->value);
        ptr1 = ptr1->next;
    }
    while (ptr2 != nullptr) {
        temp.insert(ptr2->value);
        ptr2 = ptr2->next;
    }

    return temp;  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    Set temp{};

    Node* ptr = head->next;

    while (ptr != nullptr) //så länge ptr inte är null, kollar vi om ptr value finns i set b
    {
        if (b.member(ptr->value) == true) { //finns värdet ptr->value i set b stoppar vi in det i temp
            temp.insert(ptr->value);
        }
        
        ptr = ptr->next;
    }

    return temp; // returnar det vi hann samla ihop i temp
}

// Set difference
Set Set::operator-(const Set& b) const { // samma som ovan, samlar ihop de värden som inte finns i bägge set 
    Set temp{};                          // i ett nytt sett temp

    Node* ptr = head->next;
    
    while (ptr != nullptr)
    {
        if (b.member(ptr->value) == false) {
            temp.insert(ptr->value);
        }

        ptr = ptr->next;
    }

    return temp;  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
   
    Set temp{x};

    /*temp.insert(x);*/

    Set final = operator-(temp); //kallar på funktionen ovan som kollar skillnaden mellan  s1 och set temp

    return final;  // delete if needed
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* ptr, int value) {

    Node* newNode = new Node(value, ptr->next);
    ptr->next = newNode;
    ++counter;
}

void Set::insert(int value) {

    Node* ptr = head;

    while ((ptr->next != nullptr) && (ptr->next->value < value)) {
        ptr = ptr->next;
    }
    if (ptr->next == nullptr || ptr->next->value != value) {
        insert(ptr, value);
    }
}

void Set::remove(Node* ptr) {

    delete(ptr);
}
