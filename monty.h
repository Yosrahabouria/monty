#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/** Error fucntions **/
void printErrorMessage(int errorCode, const char *messageFormat, ...);
void handleGeneralError(int errorCode, ...);
void handleMoreError(int errorCode, ...);
void handleStringError(int errorCode, ...);
/** Monty functions *//
void processMontyContent(const char *fileContent);
int parseMontyLine(char *line, int lineNumber, int currentFormat);
void findMontyInstruction(char *currentOpcode, char *currentValue, int lineNumber, int currentFormat);
void executeMontyFunction(MontyFunction function, char *op, char *val, int ln, int currentFormat);
#endif /* MONTY_H */
