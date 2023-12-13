#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void handleExitFailure() {
    free_nodes();
    exit(EXIT_FAILURE);
}

void printErrorMessage(int errorCode, const char *messageFormat, ...) {
    va_list args;
    va_start(args, messageFormat);
    
    fprintf(stderr, messageFormat, args);
    
    va_end(args);
    handleExitFailure();
}

void handleGeneralError(int errorCode, ...) {
    va_list args;
    va_start(args, errorCode);

    switch (errorCode) {
        case 1:
            printErrorMessage(errorCode, "USAGE: monty file\n");
            break;
        case 2:
            printErrorMessage(errorCode, "Error: Can't open file %s\n", va_arg(args, char *));
            break;
        case 3: {
            int lineNum = va_arg(args, int);
            char *operation = va_arg(args, char *);
            printErrorMessage(errorCode, "L%d: unknown instruction %s\n", lineNum, operation);
            break;
        }
        case 4:
            printErrorMessage(errorCode, "Error: malloc failed\n");
            break;
        case 5:
            printErrorMessage(errorCode, "L%d: usage: push integer\n", va_arg(args, int));
            break;
        default:
            break;
    }

    va_end(args);
}

void handleMoreError(int errorCode, ...) {
    va_list args;
    va_start(args, errorCode);

    switch (errorCode) {
        case 6:
            printErrorMessage(errorCode, "L%d: can't pint, stack empty\n", va_arg(args, int));
            break;
        case 7:
            printErrorMessage(errorCode, "L%d: can't pop an empty stack\n", va_arg(args, int));
            break;
        case 8: {
            int lineNum = va_arg(args, unsigned int);
            char *operation = va_arg(args, char *);
            printErrorMessage(errorCode, "L%d: can't %s, stack too short\n", lineNum, operation);
            break;
        }
        case 9:
            printErrorMessage(errorCode, "L%d: division by zero\n", va_arg(args, unsigned int));
            break;
        default:
            break;
    }

    va_end(args);
}

void handleStringError(int errorCode, ...) {
    va_list args;
    va_start(args, errorCode);

    int lineNum = va_arg(args, int);
    switch (errorCode) {
        case 10:
            printErrorMessage(errorCode, "L%d: can't pchar, value out of range\n", lineNum);
            break;
        case 11:
            printErrorMessage(errorCode, "L%d: can't pchar, stack empty\n", lineNum);
            break;
        default:
            break;
    }

    va_end(args);
}

