#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Structure to represent a stack of operators
typedef struct {
    char data[MAX_SIZE];
    int top;
} stackOpt;

// Structure to represent a stack of numbers
typedef struct {
    float data[MAX_SIZE];
    int top;
} stackNum;

// Function to push an operator onto the operator stack
void pushOpt(stackOpt *stack, char op) {
    stack->data[++stack->top] = op;
}

// Function to pop an operator from the operator stack
char popOpt(stackOpt *stack) {
    return stack->data[stack->top--];
}

// Function to push an operand onto the operand stack
void pushNum(stackNum *stack, float operand) {
    stack->data[++stack->top] = operand;
}

// Function to pop an operand from the operand stack
float popOperand(stackNum *stack) {
    return stack->data[stack->top--];
}

int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Function to check if a character is an operator (+, -, *, /)
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

float calculate(char *str) {
    stackOpt operatorStack;
    stackNum numStack;
    operatorStack.top = -1;
    numStack.top = -1;

    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == ' ')
            continue;

        if (isDigit(str[i])){
            //atof: (float) all now and following number including '.'
            float num = atof(str+i);

            while (i < len && (isDigit(str[i]) || str[i] == '.')) {
                i++;
            }
            i--; // Move back one character to account for the extra increment
            pushNum(&numStack, num);
        } else if (str[i] == '(') {
            pushOpt(&operatorStack, '(');
        } else if (str[i] == ')') {
            while (operatorStack.top >= 0 && operatorStack.data[operatorStack.top] != '(') {
                char opt = popOpt(&operatorStack);
                float b = popOperand(&numStack);
                float a = popOperand(&numStack);
                switch (opt) {
                    case '+':
                        pushNum(&numStack, a + b);
                        break;
                    case '-':
                        pushNum(&numStack, a - b);
                        break;
                    case '*':
                        pushNum(&numStack, a * b);
                        break;
                    case '/':
                        pushNum(&numStack, a / b);
                        break;
                }
            }
            if (operatorStack.top >= 0 && operatorStack.data[operatorStack.top] == '(') {
                popOpt(&operatorStack); // Pop '(' from the stack
            } else {
                printf("Error: Mismatched parentheses!\n");
                exit(1);
            }
        } else if (isOperator(str[i])) {
            while (operatorStack.top >= 0 &&
                   precedence(operatorStack.data[operatorStack.top]) >= precedence(str[i])) {
                char opt = popOpt(&operatorStack);
                float b = popOperand(&numStack);
                float a = popOperand(&numStack);
                switch (opt) {
                    case '+':
                        pushNum(&numStack, a + b);
                        break;
                    case '-':
                        pushNum(&numStack, a - b);
                        break;
                    case '*':
                        pushNum(&numStack, a * b);
                        break;
                    case '/':
                        pushNum(&numStack, a / b);
                        break;
                }
            }
            pushOpt(&operatorStack, str[i]);
        }
    }

    while (operatorStack.top >= 0) {
        char opt = popOpt(&operatorStack);
        float b = popOperand(&numStack);
        float a = popOperand(&numStack);
        switch (opt) {
            case '+':
                pushNum(&numStack, a + b);
                break;
            case '-':
                pushNum(&numStack, a - b);
                break;
            case '*':
                pushNum(&numStack, a * b);
                break;
            case '/':
                pushNum(&numStack, a / b);
                break;
        }
    }

    return numStack.data[numStack.top];
}

int main() {
    char str[MAX_SIZE];

    // Read the str from a file
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    while (fscanf(inputFile, "%s", str) != EOF) {
        float result = calculate(str);
        fprintf(outputFile, "%.2f\n", result);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
