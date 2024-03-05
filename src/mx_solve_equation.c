#include <stdlib.h>
#include <stdbool.h>

#include "minilibmx.h"

enum e_operation get_oposite_operation(enum e_operation operation) {
    switch (operation) {
        case ADD:
            return SUB;
        case SUB:
            return ADD;
        case MUL:
            return DIV;
        case DIV:
            return MUL;
        default:
            return UNKNOWN;
    }
}

// works only for simple equations no multiplication with zeros, no division
int mx_solve_equation(int operand1,
                      int operand2,
                      enum e_operation operation,
                      int equal,
                      enum e_input_type unknown_variable) {
    int result;

    switch (unknown_variable) {
        case OPERAND1:
            result = mx_perform_operation(get_oposite_operation(operation), equal, operand2);

            return result;
        case OPERAND2:
            if (operation == ADD || operation == MUL) {
                result = mx_perform_operation(get_oposite_operation(operation), equal, operand1);
            
                return result;
            }

            result = mx_perform_operation(operation, operand1, equal);
    
            return result;
        case RESULT:
            result = mx_perform_operation(operation, operand1, equal);
            
            return result;
        default:
            return 0;
    }
}

