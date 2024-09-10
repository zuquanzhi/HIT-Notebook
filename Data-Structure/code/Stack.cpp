#include <iostream>
#include <stack>
#include <string>
#include <cctype> // for isdigit()

// 手动实现的堆栈类
class Stack {
    int top;
    int maxSize;
    int* stackArray;
public:
    Stack(int size) {
        maxSize = size;
        stackArray = new int[maxSize];
        top = -1;
    }

    ~Stack() {
        delete[] stackArray;
    }

    bool push(int x) {
        if (top >= maxSize - 1) {
            std::cout << "Stack Overflow" << std::endl;
            return false;
        }
        stackArray[++top] = x;
        std::cout << x << " pushed into stack" << std::endl;
        return true;
    }

    int pop() {
        if (top < 0) {
            std::cout << "Stack Underflow" << std::endl;
            return -1;
        }
        return stackArray[top--];
    }

    int peek() {
        if (top < 0) {
            std::cout << "Stack is Empty" << std::endl;
            return -1;
        }
        return stackArray[top];
    }

    bool isEmpty() {
        return (top < 0);
    }
};

// 使用标准库实现堆栈的括号匹配功能
bool areBracketsBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        } else {
            if (s.empty()) return false;
            char top = s.top();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

// 使用标准库实现的后缀表达式（逆波兰表达式）求值
int evaluatePostfix(const std::string& expr) {
    std::stack<int> s;
    for (char ch : expr) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        } else {
            int val1 = s.top(); s.pop();
            int val2 = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(val2 + val1); break;
                case '-': s.push(val2 - val1); break;
                case '*': s.push(val2 * val1); break;
                case '/': s.push(val2 / val1); break;
            }
        }
    }
    return s.top();
}

int main() {
    // 使用手动实现的堆栈类
    Stack s(5);  // 创建大小为5的堆栈
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "Top element: " << s.peek() << std::endl;
    std::cout << s.pop() << " popped from stack" << std::endl;

    // 使用标准库实现的堆栈来进行括号匹配
    std::string expr = "{[()]}";
    if (areBracketsBalanced(expr)) {
        std::cout << "Brackets are balanced" << std::endl;
    } else {
        std::cout << "Brackets are not balanced" << std::endl;
    }

    // 使用标准库实现的堆栈来求解后缀表达式
    std::string postfixExpr = "231*+9-";
    std::cout << "Postfix evaluation result: " << evaluatePostfix(postfixExpr) << std::endl;

    return 0;
}