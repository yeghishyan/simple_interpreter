# Simple Interpreter

## Table of contents

<!--- [Usage](#usage) --->
- [Example](#example)
- [Interpreter structure](#interpreter-structure)
- [Dependencies](#dependencies)

<!---
## Usage

```sh
cmake --build build/
```
-->


## Example

```python
print "hello world!"  #"hello world!"
x = (9-1)/2.0         # 4.0
print x               # 4.0
y = -5
print x*y             # -20.0

#x = 1 +               
#print z
```


## Interpreter structure

```
<program>               = <statement>

<block>                 = "{" <statement> "}"

<statement>             = (<variable_decl> | <assignment_statement>) ";"
                        | <print_statement> ";"
                        | <block> ";"

<variable_decl>         = "var" <identifier> "=" <expression>

<print_statement>       = "print" <expression> 

<assignment_statement>  = <identifier> "=" <expression>

‹expression›            = ‹term› ‹additive-op› ‹term›

‹term›                  = ‹factor› ‹multiplicative-op› ‹factor›

‹factor›                = ‹literal›     
                        | ‹identifier›
                        | ‹sub-expression›
                        | ‹unary›
    
‹literal›               = ‹int-literal›
                        | ‹real-literal›
                        | <string-literal>
    
‹sub-expression›        = "(" ‹expression› ")"

‹unary›                 = ( "+" | "-" ) { ‹expression› }

‹additive-op›           = "+" | "-"

‹multiplicative-op›     = "*" | "/" | "^"

‹identifier›            = (‹letter›) { ‹letter› | ‹digit› }

‹int-literal›           = ‹digit› { ‹digit› }

‹real-literal›          = ‹digit› { ‹digit› } "." { ‹digit› }
                        | "." ‹digit› { ‹digit› }

‹printable›             = ‹digit› | ‹letter› | " " | "!" | """ | "#" | "$" | "%" | "&"
                        | "'" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";"
                        | "<" | "=" | ">" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`"
                        | "{" | "|" | "}" | "~"

‹letter›                = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K"
                        | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V"
                        | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g"
                        | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r"
                        | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"

‹digit›                 = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```


## Dependencies

* [CMake](https://github.com/Kitware/CMake)

[(Back to top)](#table-of-contents)
