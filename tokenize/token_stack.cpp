#include "token_stack.h"

#include <stdexcept>

using namespace std;

// NOTE: all operations other than reverse and destructor
// should have O(1)

// TODO: return the top value on the stack.
const Token& TokenStack::top() const {
    if (this->empty()) {
        throw std::out_of_range("empty stack");
    }

    // TODO: complete function here
    return list.at(0);
}

// TODO: implement the TokenStack methods.
// TODO: return how many tokens are in the stack
size_t TokenStack::size() const { return list.size(); }

// TODO: check whether the stack is empty
bool TokenStack::empty() const {
    if (this->size())
        return false;
    else
        return true;
}

// TODO: push a new token on top of the stack.
void TokenStack::push(const Token& t) {
    // the top of the stack is at index 0
    list.insert(0, t);
}

// TODO: remove the top element on the stack.
// If the stack is empty, this function should do nothing
void TokenStack::pop() { list.remove(0); }

// TODO: reverse the contents of the stack.
void TokenStack::reverse() { list.reverse(); }

// Help debugging
std::ostream& operator<<(std::ostream& out, const TokenStack& stack) {
    // if the list is empty
    /*if(stack.size() == 0)
        out << "Empty List." << endl;
    else{
        out << stack.list;
        return out;
    }*/
    out << stack.list;
    return out;
}
