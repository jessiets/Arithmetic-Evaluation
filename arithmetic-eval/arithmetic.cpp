#include "token.h"
#include "token_stack.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

// THROW ALL EXCEPTIONS EXACTLY AS GIVEN IN THE COMMENTS
// You need only uncomment them to throw the exceptions
// under the correct conditons
// You can check the conditions using an if statement or
// switch statement
// For any problems with the expression format as well as attempting
// division by zero, throw the exception invalid_argument("Malformed");

TokenStack tokenize(std::string expression) {
    TokenStack stack;
    stringstream stream(expression);

    int value;
    char temp;
    // Loop while there are still characters in the stream.
    while (stream.rdbuf()->in_avail()) {
        // TODO: push your tokens to the stack.
        temp = stream.peek();
        // check for whitespaces
        while (temp == ' ') {
            temp = stream.get();
            temp = stream.peek();
        }

        if (temp == '+') {
            temp = stream.get();
            stack.push(Token(TokenKind::PLUS));
        } else {
            if (temp == '-') {
                temp = stream.get();
                stack.push(Token(TokenKind::MINUS));
            } else {
                if (temp == '*') {
                    temp = stream.get();
                    stack.push(Token(TokenKind::TIMES));
                } else {
                    if (temp == '/') {
                        temp = stream.get();
                        stack.push(Token(TokenKind::DIVIDE));
                    } else {
                        if (temp == '(') {
                            temp = stream.get();
                            stack.push(Token(TokenKind::LP));
                        } else {
                            if (temp == ')') {
                                temp = stream.get();
                                stack.push(Token(TokenKind::RP));
                            } else {
                                // if token is an integer
                                if (stream >> value) {
                                    stack.push(Token(TokenKind::NUMBER, value));
                                } else
                                    throw invalid_argument("Malformed");
                            }
                        }
                    }
                }
            }
        }
        // If we find an invalid token, we can simply:
        // throw invalid_argument("Malformed");
    }

    // We pushed the tokens into the stack from left to right, which means
    // we'll pop them back out backwards. For convenience, we'll return the
    // reverse of our current stack so that we can pop the tokens out from
    // left to right, as you'd read the expression.
    stack.reverse();
    return stack;
}

// Reduce is called when we encounter closing parentheses. If the expression
// is validly formed, we can expect there to be either a binary operation on
// the work stack. This method should pop the tokens in that operation,
// compute the result, and push it back onto the work stack as a new token.
void reduce(TokenStack& work) {
    TokenStack immediate;
    Token temp(TokenKind::INVALID);

    // TODO: pop tokens off of work into immediate until we hit TokenKind::LP.
    while (work.top().kind != TokenKind::LP) {
        // TODO: if there's no TokenKind::LP, throw:
        if (work.size() == 0)
            throw invalid_argument("Malformed");
        temp = work.top();
        work.pop();
        immediate.push(temp);
    }
    // clear the LP on work stack
    work.pop();

    // TODO: if you are expecting a token but immediate is empty, throw:
    if (immediate.size() == 0)
        throw invalid_argument("Malformed");

    // if input is only 1 character
    if (immediate.size() == 1) {
        Token val(TokenKind::NUMBER);
        val = immediate.top();
        immediate.pop();
        work.push(val);
    } else {
        // TODO: check whether we have "-p" or "p @ q @ ..." and handle accordingly
        // for -p, reverse sign and push to work stack
        if (immediate.size() == 2) {
            // TODO: if you are expecting a token of a different kind, throw:
            if (immediate.top().kind != TokenKind::MINUS)
                throw invalid_argument("Malformed");
            // popping the - sign
            immediate.pop();
            Token val(TokenKind::NUMBER);
            val = immediate.top();
            immediate.pop();
            val.value *= (-1);
            work.push(val);
        } else {
            // store lhs token in lhs
            Token lhs(TokenKind::NUMBER);
            lhs = immediate.top();
            immediate.pop();
            // store operator in op
            Token op(TokenKind::INVALID);
            op = immediate.top();
            immediate.pop();

            Token rhs(TokenKind::NUMBER);

            // normal case: will have size of 1 at this point
            while (immediate.size()) {
                rhs = immediate.top();
                immediate.pop();
                if (op.kind == TokenKind::PLUS)
                    lhs.value = lhs.value + rhs.value;
                else if (op.kind == TokenKind::MINUS)
                    lhs.value = lhs.value - rhs.value;
                else if (op.kind == TokenKind::TIMES)
                    lhs.value = lhs.value * rhs.value;
                else if (op.kind == TokenKind::DIVIDE) {
                    // TODO: if dividing by zero, throw:
                    if (rhs.value == 0)
                        throw invalid_argument("Malformed");
                    lhs.value = lhs.value / rhs.value;
                }
                // if the operator is not of kind +, -, *, or /, throw:
                else
                    throw invalid_argument("Malformed");
                // for p @ q @ ...
                if (immediate.size()) {
                    // TODO: if you encounter a differing chained binary operation, throw:
                    if (immediate.top().kind != op.kind)
                        throw invalid_argument("Malformed");
                    else
                        immediate.pop();
                }
            }

            // TODO: push the result of either branch back onto work
            work.push(lhs);
        }
    }
}

int evaluate(std::string expression) {
    TokenStack tokens = tokenize(expression);
    TokenStack work;
    // testing tokenize
    // cout << "After tokenize: " << tokens << endl;

    // evaluating process
    Token temp(TokenKind::INVALID);
    while (tokens.size()) {
        // TODO: while the stack is not empty, pop the top token.
        temp = tokens.top();
        tokens.pop();
        // TODO: if the top token is of TokenKind::RP, reduce(work).
        if (temp.kind == TokenKind::RP)
            reduce(work);
        // TODO: otherwise, push the top token onto work.
        else
            work.push(temp);
    }

    // done evaluating
    // TODO: once done, check there is exactly one TokenKind::NUMBER token.
    if (work.size() == 1 && work.top().kind == TokenKind::NUMBER)
        // TODO: if so, return its value, otherwise throw:
        return work.top().value;
    else
        throw invalid_argument("Malformed");
}

// Please DO NOT CHANGE MAIN
int main(int argc, char** argv) {
    if (argc <= 1) {
        cerr << "Expect an expression..." << endl;
        return -1;
    }

    try {
        cout << evaluate(argv[1]) << endl;
    } catch (invalid_argument& e) {
        cerr << "error: " << e.what() << endl;
    }
    return 0;
}

// If you're interested in extending your parser to support things like order
// of operations, unary operators, and single values, feel free to ping me
// on Discord (noahbkim) once you've finished the assignment as is. This will
// not give you any extra credit or improve your score in any way; it's just
// something fun and cool.
