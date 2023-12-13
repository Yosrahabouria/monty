#include "monty.h"
//*checks if the content is not NULL and uses handleError if it is*/
void processMontyContent(const char *fileContent) {
    if (!fileContent)
        handleError(2, "NULL");

    int currentLineNumber = 1, currentFormat = 0;
    char *currentLine = strdup(fileContent);

    if (!currentLine)
        handleError(4);

    char *currentTokenPtr;
    char *token = strtok_r(currentLine, "\n", &currentTokenPtr);

    while (token) {
        currentFormat = parseMontyLine(token, currentLineNumber++, currentFormat);
        token = strtok_r(NULL, "\n", &currentTokenPtr);
    }

    free(currentLine);
}
/*checks if the line is not NULL and uses handleError if it is*/
int parseMontyLine(char *line, int lineNumber, int currentFormat) {
    char *currentOpcode, *currentValue;
    const char *delimiter = " ";

    if (!line)
        handleError(4);

    currentOpcode = strtok(line, delimiter);
    if (!currentOpcode)
        return currentFormat;

    currentValue = strtok(NULL, delimiter);

    if (strcmp(currentOpcode, "stack") == 0)
        return 0;
    if (strcmp(currentOpcode, "queue") == 0)
        return 1;

    findMontyInstruction(currentOpcode, currentValue, lineNumber, currentFormat);
    return currentFormat;
}
/*checks if the opcode starts with '#' and returns if true (ignoring comments)*/
void findMontyInstruction(char *currentOpcode, char *currentValue, int lineNumber, int currentFormat) {
    MontyInstruction montyInstructions[] = { ... };

    if (currentOpcode[0] == '#')
        return;

    for (int i = 0; montyInstructions[i].opcode; i++) {
        if (strcmp(currentOpcode, montyInstructions[i].opcode) == 0) {
            executeMontyFunction(montyInstructions[i].function, currentOpcode, currentValue, lineNumber, currentFormat);
            return;
        }
    }

    handleError(3, lineNumber, currentOpcode);
}
/*It specifically handles the "push" instruction, checking for valid values and creating nodes accordingly. 
It then calls the appropriate function with the provided parameters. 
If the opcode is not "push," it calls the function directly with the global head and line number.*/
void executeMontyFunction(MontyFunction function, char *op, char *val, int ln, int currentFormat) {
    if (strcmp(op, "push") == 0) {
        if (!val || (val[0] == '-' && !isdigit(val[1])))
            handleError(5, ln);

        MontyNode *node = createMontyNode(atoi(val));

        if (currentFormat == 0)
            function(&node, ln);

        if (currentFormat == 1)
            addToMontyQueue(&node, ln);
    } else {
        function(&montyHead, ln);
    }
}

