#include <iostream>
#include <exception>

#include "logger.hpp"
#include "parser.hpp"
#include "interpreter.hpp"


int main() {
    std::string input_expression;
    interpreter i;

    std::cout<<">>>";
    while(std::getline(std::cin, input_expression)) {
        if (!input_expression.empty()) {
            Parser p(input_expression);
            try {
                ast_program* program = p.parse();
                i.visit(program);
            }
            catch (std::exception& e) {
                std::cout << e.what() <<std::endl;

                auto log = p.log();
                log->print();
            }
        }
        std::cout<<">>>";        
    }

    return 0;
}
/*
print "hello world!"
x = (9-1)/2.0
print x
y = -5
print x*y

x = 1 +
print z


*/