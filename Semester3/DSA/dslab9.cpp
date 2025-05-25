// Experiment 9
// I.	Write a program to implement STACK using arrays/Linked List that performs following operations
// (a)	PUSH
// (b)	POP
// (c)	PEEP
// (d)	DISPLAY
// II.	Write a program to convert infix algebraic expression to postfix algebraic expression with the help of stack.
// III.	Evaluate a postfix algebraic expression with the help of stack.

#include<iostream>
#include<string>
using namespace std;

void Display(int stack[], int &top) {
    if (top == -1) {
        cout << "Stack is empty" << endl;
        return;
    }
    int temp = top;
    while (temp != -1) {
        cout << stack[temp] << " ";
        temp--;
    }
    cout << endl;
}

void Push(int stack[], int val, int &top, int size) {
    if (top >= size - 1) {
        cout << "Overflow" << endl;
        return;
    }
    top += 1;
    stack[top] = val;
}

int Pop(int stack[], int &top) {
    if (top == -1) {
        cout << "Underflow" << endl;
        return -1;
    }
    int val = stack[top];
    top -= 1;
    return val;
}

int Peep(int stack[], int top) {
    if (top == -1) {
        cout << "Underflow" << endl;
        return -1;
    }
    return stack[top];
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int isOperand(char x) {
    if (x == '+' || x == '-' || x == '*' || x == '/')
        return 0;
    else
        return 1;
}

// Convert infix to postfix
void infix_to_postfix() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix;
    int size = infix.length();
    int stack[size];
    int top = -1;

    for (int i = 0; i < size; i++) {
        char token = infix[i];

        if (token == '(') {
            Push(stack, token, top, size);
        } else if (token == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix += (char)Pop(stack, top);
            }
            Pop(stack, top); // Pop '('
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (top != -1 && precedence(stack[top]) >= precedence(token)) {
                postfix += (char)Pop(stack, top);
            }
            Push(stack, token, top, size);
        } else {
            postfix += token;  
        }
    }

    while (top != -1) {
        postfix += (char)Pop(stack, top);
    }

    cout << "Postfix expression is: " << postfix << endl;
}

// Evaluate postfix expression
void evaluate_postfix() {
    string postfix;
    cout << "Enter postfix expression: ";
    cin >> postfix;

    int size = postfix.length();
    int stack[size];
    int top = -1;

    for (int i = 0; i < size; i++) {
        if (isOperand(postfix[i])) {
            Push(stack, postfix[i] - '0', top, size);
        } else {
            int x2 = Pop(stack, top);
            int x1 = Pop(stack, top);
            int r = 0;
            switch (postfix[i]) {
                case '+': r = x1 + x2; break;
                case '-': r = x1 - x2; break;
                case '*': r = x1 * x2; break;
                case '/': r = x1 / x2; break;
            }
            Push(stack, r, top, size);
        }
    }
    cout << "Result is: " << stack[top] << endl;
}

int main() {
    int size = 5;
    int stack[size];
    int top = -1;

    cout << "1. Display elements of stack" << endl;
    cout << "2. Push" << endl;
    cout << "3. Pop" << endl;
    cout << "4. Peep" << endl;
    cout << "5. Infix to postfix" << endl;
    cout << "6. Evaluate postfix" << endl;
    cout << "7. Exit" << endl;

    int choice, val, lastval;

    while (1) {
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Display(stack, top);
                break;
            case 2:
                cout << "Enter Value to insert: ";
                cin >> val;
                Push(stack, val, top, size);
                break;
            case 3:
                Pop(stack, top);
                break;
            case 4:
                lastval = Peep(stack, top);
                cout << "Last value is: " << lastval << endl;
                break;
            case 5:
                infix_to_postfix();
                break;
            case 6:
                evaluate_postfix();
                break;
            case 7:
                cout << "Exiting";
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}
