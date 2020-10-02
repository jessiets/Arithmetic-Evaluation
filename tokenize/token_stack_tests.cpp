#include "token_stack.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // cerr << "No TokenStack tests have been implemented yet!" << endl;
    TokenStack test;

    test.push(Token(TokenKind::NUMBER, 1));
    test.push(Token(TokenKind::NUMBER, 2));
    test.push(Token(TokenKind::NUMBER, 3));
    // expected output: 3 2 1
    cout << "After push: " << test << endl;

    cout << "Top: " << test.top() << endl;

    test.pop();
    cout << "Top element popped, remaining: " << test << endl;
    cout << "Top: " << test.top() << endl;
    ;
    test.pop();
    cout << "Another top element popped, remaining: " << test << endl;
    cout << "Top: " << test.top() << endl;
    test.pop();
    cout << "All elements popped: " << test << endl;

    test.push(Token(TokenKind::NUMBER, 4));
    test.push(Token(TokenKind::NUMBER, 5));
    test.push(Token(TokenKind::NUMBER, 6));
    test.push(Token(TokenKind::NUMBER, 7));
    test.push(Token(TokenKind::NUMBER, 8));
    cout << "Original test: " << test << endl;
    test.reverse();
    cout << "After reverse: " << test << endl;

    return 0;
}
