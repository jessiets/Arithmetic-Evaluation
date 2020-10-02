#include "token_list.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    TokenList test;

    test.push_back(Token(TokenKind::NUMBER, 1));
    test.push_back(Token(TokenKind::NUMBER, 2));
    test.push_back(Token(TokenKind::NUMBER, 3));
    /* SELF-ADDED TESTS
    test.push_back(Token(TokenKind::NUMBER, 4));
    test.push_back(Token(TokenKind::NUMBER, 5));
    test.push_back(Token(TokenKind::NUMBER, 6));
    test.push_back(Token(TokenKind::NUMBER, 7));*/
    cout << "After push back: " << test << endl;

    test.reverse();
    cout << "After reverse: " << test << endl;

    TokenList test2 = test;
    cout << "Original after copy: " << test << endl;
    cout << "Copy after copy: " << test2 << endl;

    test.remove(0);
    cout << "Original after removing 1: " << test << endl;
    cout << "Copy after removing 1 from original: " << test2 << endl;

    /*
    // SELF-ADDED TESTS
    //testing insert():
    // expected output with push_back n insert for test: 9 1 2 8 3 10
    test.insert(2, Token(TokenKind::NUMBER, 8));
    test.insert(0, Token(TokenKind::NUMBER, 9));
    test.insert(5, Token(TokenKind::NUMBER, 10));
    cout << "After insert: " << test << endl;
    TokenList test3;
    test3.insert(0, Token(TokenKind::NUMBER, 11));
    cout << "Insert to empty list: " << test3 << endl;

    //testing remove(): expected output with push_back, insert, and remove
        //
    test.remove(3);
    // remove beginning of list
    test.remove(0);
    // remove last item
    test.remove(3);
    cout << "After remove: " << test << endl;

    //testing =operator
    cout << "Original test: " << test << endl;
    cout << "test2: " << test2 << endl;
    test = test2;
    cout << "After getting assigned to test2: " << test << endl;

    //testing at(0)
    cout << "Item at index 0: " << test.at(0) << endl;*/

    test.at(1) = Token(TokenKind::NUMBER, 2);
    cout << "After replace 3 with 3: " << test << endl;

    return 0;
}
