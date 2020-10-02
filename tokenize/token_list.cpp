#include "token_list.h"

#include <memory>
#include <stdexcept>

using namespace std;

size_t TokenList::size() const { return this->_size; }

// TODO: implement the TokenList methods.

// Rule of Three
// copy constructor
TokenList::TokenList(TokenList const& other) {
    shared_ptr<Item> current(other.head);
    while (_size < other._size) {
        this->push_back(current->value);
        current = current->next;
    }
}

// assignment operator
TokenList& TokenList::operator=(TokenList const& other) {
    // check for self assignment
    if (&other == this)
        return *this;

    // otherwise, copy rhs to lhs
    shared_ptr<Item> current(other.head);
    _size = 0;
    while (_size < other._size) {
        this->push_back(current->value);
        current = current->next;
    }
}
// destructor
TokenList::~TokenList() {
    int i = this->size();
    while (this->size()) {
        this->remove(i - 1);
        i--;
    }
}

// at function get Token at an arbitrary index
// the two implementations could be identical
Token& TokenList::at(size_t index) {
    // if list is empty, throw an exception
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    // return token at index%n, where n is current list size
    size_t n = this->size();
    // temp stores the address of the Item at index
    shared_ptr<Item> temp(head);
    // if the index is 0, just return the topmost index without loop
    if (index == 0) {
        return temp->value;
    }

    for (size_t i = 0; i < index % n; i++)
        temp = temp->next;
    return temp->value;
}

const Token& TokenList::at(size_t index) const {
    // if list is empty, throw an exception
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    // return token at index%n, where n is current list size
    size_t n = this->size();
    // temp stores the address of the Item at index
    shared_ptr<Item> temp(head);
    // if the index is 0, just return the topmost index without loop
    if (index == 0) {
        return temp->value;
    }

    for (size_t i = 0; i < index % n; i++)
        temp = temp->next;
    return temp->value;
}

// insert Token to end of list
void TokenList::push_back(Token value) {
    // create new Item
    shared_ptr<Item> temp = make_shared<Item>(value);
    // if the list is empty, create a new list
    if (this->size() == 0) {
        // update head pointer to point at new Item
        head = temp;
        // circular list, so newItem points to itself
        temp->previous = temp;
        temp->next = temp;
    }
    // otherwise, add the new item to the back of the list
    else {
        // circular list, so head->prev is pointing at the tail
        // add item to back of list
        temp->previous = head->previous;
        head->previous->next = temp;
        temp->next = head;
        // update tail
        head->previous = temp;
    }

    // update list size
    this->_size++;
}

// insert Token at given index
void TokenList::insert(size_t index, Token value) {
    // if list is empty, directly call push_back
    if (this->_size == 0)
        push_back(value);

    else {
        // First, increase list size by 1.
        this->_size++;
        size_t n = this->size();
        // create new item
        shared_ptr<Item> temp = make_shared<Item>(value);

        // if index is at the head of the list, assuming that the list exists
        if (index == 0 && n > 1) {
            // initiate new item prev and next ptr
            temp->previous = head->previous;
            temp->next = head;
            // update old item prev and next ptr
            head->previous->next = temp;
            head->previous = temp;
            // update head
            head = temp;
        } else {
            // if index is at the end of the list, just call push_back
            if (index % n == n - 1) {
                push_back(value);
                this->_size--;
            } else {
                // insert Token at index%n where n is new size, assuming head starts [0]
                // index points at the original item at index
                shared_ptr<Item> i_element(head);
                for (size_t i = 0; i < index % n; i++) {
                    i_element = i_element->next;
                }
                temp->previous = i_element->previous;
                temp->next = i_element;
                i_element->previous->next = temp;
                i_element->previous = temp;
            }
        }
    }
    // cout << "Number of items in list: " << this->size() << endl;
}

// remove item at given index
void TokenList::remove(size_t index) {
    // if list is empty, just return
    if (this->size() == 0)
        return;
    // otherwise, remove item at index%n where n is size, assuming head starts [0]
    shared_ptr<Item> remove_item(head);
    size_t n = this->size();

    // if the item removed is at index 0
    if (index == 0) {
        // if the item to be removed is the last item on the list
        if (this->size() == 1) {
            head = nullptr;
        } else {
            // assign new head
            head = remove_item->next;
            // update prev of new head
            head->previous = remove_item->previous;
            // update tail
            head->previous->next = head;
        }
    } else {
        // otherwise, remove item normally
        // have remove_item point to the item at index
        for (size_t i = 0; i < index % n; i++) {
            remove_item = remove_item->next;
        }
        // update the prev and next ptr of item before and after remove_item
        remove_item->previous->next = remove_item->next;
        remove_item->next->previous = remove_item->previous;
    }
    // decrease size count
    this->_size--;
    // cout << "Remove_item use count: " << remove_item.use_count() << endl;
    // cout << "Number of items in list: " << this->size() << endl;
}

// reverse the list
void TokenList::reverse() {
    // if list is empty, throw an exception
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    shared_ptr<Item> current;
    shared_ptr<Item> temp(head);
    size_t i = 0;
    while (i < _size) {
        current = temp;
        // temp storres the original next element
        temp = current->next;
        // new next will point at original prev
        current->next = current->previous;
        // new prev will point at original next(stored in next)
        current->previous = temp;
        // i keeps track of how many elements we've reversed
        i++;
    }
    // update new head
    head = current;
}

std::ostream& operator<<(std::ostream& out, const TokenList& list) {
    out << "{";
    std::shared_ptr<TokenList::Item> cursor = list.head;
    if (cursor != nullptr) {
        for (size_t i = 0; i < list.size() - 1; i++) {
            out << cursor->value << ", ";
            cursor = cursor->next;
        }
        out << cursor->value;
    }
    return out << "}";
}
