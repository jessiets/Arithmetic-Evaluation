# Arithmetic-Evaluation
This program evaluates an arithmetic expression. 
<br>
<br>
<br>
## About
<li>This program takes in an arithmetic expression as input. For example, "(3+4 + (8*20))". <br>
<li>Then, the program tokoenizes the numeric values and operators.<br> From the previous example, the expression will now be: 
{ "(", "3", "+", "4", "+", "(", "8", "+", "20", ")", ")" }. <br>
<li>Lastly, the program will return the evaluated value. 

## Rules
<li> Simple Arithmetic: <br> 
                Input must follow the rules of simple arithmetic. That is, an operation must be enclosed in a set of parenthesis ().
                For example, (3 +(4*5)) is a valid input, whereas (3+ 4*5) is not. 
<li> Chaining:<br> 
                Chaining is implemented in this program. That is, multiple numeric values can be contained within the same set of parenthesis if the 
                operation between these values are consistent. For example, (3+4+5) and (3*4*5) are both valid inputs, whereas (3*4+5) is not.
<li> Negative Values:<br>
                Negative values are accepted in the input expression, however, please make sure that the negative sign is contained in a set of 
                parenthesis. For example, ((-5)-2) is a valid input, whereas (-5 -2) is not.
<li> White Spaces: <br>
                White spaces in the input expression will be ignored during the tokenize process. That is, the expression (  3 +4 +   5 ) will be treated
                the same way as (3+4+5).
               
<li> Errors: <br>
If the input doesn't follow simple arithmetic, the program will quit immediately. <br>
If the input expression attempts a division by 0, the program will throw an exception. <br>


## Implementation
<li> circular list implementation
<li> stack implementation with list composition
<li> the majority of functions have O(1) runtime complexity
