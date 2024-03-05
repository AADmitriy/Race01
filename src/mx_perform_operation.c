#include "minilibmx.h"

int mx_perform_operation(enum e_operation operation, int operand1, int operand2) {
    switch (operation) {
        case ADD:
            return operand1 + operand2;
        case SUB:
            return operand1 - operand2;
        case MUL:
            return operand1 * operand2;
        case DIV:
            return operand1 / operand2;
        default:
            return 0;
    }
}

