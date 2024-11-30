#include <iostream>
#include <stack>
using namespace std;

int applyOp(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    return a / b;
}

int precedence(char op) { return (op == '+' || op == '-') ? 1 : 2; }

int evaluate(string exp) {
    stack<int> values; 
    stack<char> ops; 

    for (int i = 0; i < exp.length(); i++) {
        if (isspace(exp[i])) continue;

        if (isdigit(exp[i])) {
            int val = 0;
            while (i < exp.length() && isdigit(exp[i])) 
                val = val * 10 + (exp[i++] - '0');
            values.push(val);
            i--;
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(exp[i])) {
                int b = values.top(); values.pop();
                int a = values.top(); values.pop();
                values.push(applyOp(a, b, ops.top())); ops.pop();
            }
            ops.push(exp[i]);
        }
    }

    while (!ops.empty()) {
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        values.push(applyOp(a, b, ops.top())); ops.pop();
    }

    return values.top();
}

int main() {
    string expression = "3 + 5 - 2 * 3 / 2";
    cout << "Expression: " << expression << endl;
    cout << "Result: " << evaluate(expression) << endl;
    return 0;
}