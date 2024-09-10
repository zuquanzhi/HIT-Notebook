## C++ 堆栈笔记

### 1. 什么是堆栈？

堆栈（Stack）是一种基础的数据结构，遵循**后进先出**（LIFO, Last In First Out）原则，意味着最后插入堆栈的元素最先被弹出。堆栈的使用场景非常广泛，如处理递归、括号匹配、表达式求值、回溯算法等。它通常用于管理程序的运行状态。

### 2. 堆栈的特点与应用场景

#### 2.1 特点
- **线性数据结构**：堆栈通过一个线性方式组织元素，只有栈顶（顶部）元素可以被访问。
- **操作受限**：仅允许在栈的顶部进行插入（push）和删除（pop）操作，无法直接访问或修改栈中的其他元素。
- **动态增长**：堆栈可以动态调整大小，尤其是在使用标准库的实现时（如 C++ 中的 `std::stack`）。

#### 2.2 典型应用场景
- **递归调用管理**：函数递归时，每次函数调用都会在堆栈中保存局部变量和返回地址，直到递归结束，再从堆栈中逐步恢复状态。
- **表达式求值**：在表达式求值过程中，特别是中缀转后缀表达式和逆波兰表达式的计算，堆栈是核心工具。
- **括号匹配**：用于检查表达式中括号是否配对，堆栈可以方便地追踪最近遇到的左括号，并在遇到右括号时进行匹配。
- **浏览器前进/后退操作**：用户在浏览网页时，前进和后退操作是典型的堆栈应用。前进操作和后退操作分别模拟两种不同的堆栈。

### 3. 堆栈的操作

#### 3.1 基本操作
堆栈的主要操作包括：
- **push**：将元素插入堆栈的顶部。
- **pop**：移除堆栈顶部的元素。
- **top（peek）**：返回栈顶元素但不移除它。
- **isEmpty**：检查堆栈是否为空。
- **size**：返回堆栈中元素的数量。

#### 3.2 C++ 标准库实现

C++ 提供了标准的 `std::stack` 容器来实现堆栈。以下是一个简单的例子，演示如何使用 C++ 实现堆栈的基本操作：

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> s;

    // 压栈操作
    s.push(10);
    s.push(20);
    s.push(30);

    // 显示栈顶元素
    std::cout << "Top element: " << s.top() << std::endl;

    // 出栈操作
    s.pop();

    std::cout << "Top element after pop: " << s.top() << std::endl;

    // 判断堆栈是否为空
    if (s.empty()) {
        std::cout << "Stack is empty." << std::endl;
    } else {
        std::cout << "Stack is not empty." << std::endl;
    }

    // 输出堆栈大小
    std::cout << "Stack size: " << s.size() << std::endl;

    return 0;
}
```

### 4. C++ 手动实现堆栈

除了使用标准库的堆栈，我们也可以通过数组或者链表手动实现堆栈。以下是基于数组的实现：

#### 4.1 使用数组实现堆栈

```cpp
#include <iostream>

#define MAX 1000

class Stack {
    int top;
public:
    int arr[MAX]; // 堆栈数组

    Stack() { top = -1; } // 初始化栈顶
    bool push(int x);
    int pop();
    int peek();
    bool isEmpty();
};

// push 操作
bool Stack::push(int x) {
    if (top >= MAX - 1) {
        std::cout << "Stack Overflow" << std::endl;
        return false;
    } else {
        arr[++top] = x;
        std::cout << x << " pushed into stack" << std::endl;
        return true;
    }
}

// pop 操作
int Stack::pop() {
    if (top < 0) {
        std::cout << "Stack Underflow" << std::endl;
        return 0;
    } else {
        int x = arr[top--];
        return x;
    }
}

// peek 操作
int Stack::peek() {
    if (top < 0) {
        std::cout << "Stack is Empty" << std::endl;
        return 0;
    } else {
        return arr[top];
    }
}

// 判断是否为空
bool Stack::isEmpty() {
    return (top < 0);
}

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << s.pop() << " Popped from stack" << std::endl;
    std::cout << "Top element is " << s.peek() << std::endl;
    std::cout << "Stack empty: " << s.isEmpty() << std::endl;
    return 0;
}
```

#### 4.2 链表实现堆栈

链表实现堆栈可以避免数组的固定大小限制，它具有动态扩展的能力。

```cpp
#include <iostream>

class StackNode {
public:
    int data;
    StackNode* next;
};

StackNode* newNode(int data) {
    StackNode* stackNode = new StackNode();
    stackNode->data = data;
    stackNode->next = nullptr;
    return stackNode;
}

bool isEmpty(StackNode* root) {
    return !root;
}

void push(StackNode** root, int data) {
    StackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    std::cout << data << " pushed to stack\n";
}

int pop(StackNode** root) {
    if (isEmpty(*root))
        return -1;
    StackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    delete temp;

    return popped;
}

int peek(StackNode* root) {
    if (isEmpty(root))
        return -1;
    return root->data;
}

int main() {
    StackNode* root = nullptr;

    push(&root, 10);
    push(&root, 20);
    push(&root, 30);

    std::cout << pop(&root) << " popped from stack\n";
    std::cout << "Top element is " << peek(root) << std::endl;

    return 0;
}
```

### 5. 常见堆栈应用

#### 5.1 括号匹配问题
堆栈可以用于括号匹配的检测，以下是一个简单的实现，用于检查括号是否匹配：

```cpp
#include <iostream>
#include <stack>
#include <string>

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

int main() {
    std::string expr = "{[()]}";
    if (areBracketsBalanced(expr))
        std::cout << "Balanced\n";
    else
        std::cout << "Not Balanced\n";
    return 0;
}
```

#### 5.2 表达式求值
堆栈在后缀表达式（逆波兰表达式）计算中非常有用。以下是基于堆栈的后缀表达式求值实现：

```cpp
#include <iostream>
#include <stack>
#include <string>

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
    std::string expr = "231*+9-";
    std::cout << "Result: " << evaluatePostfix(expr) << std::endl;
    return 0;
}
```

### 6. 堆栈的时间与空间复杂度

- **时间复杂度**：
  - `push` 操作：O(1)
  - `pop` 操作：O(1)
  - `peek` 操作：O(1)
  
- **空间复杂度**：O(n)，其中 n 是堆栈中的元素个数。对于链表实现，额外的空间复杂度还包括链表节点的指针存储。

### 7. 堆栈的局限性

虽然堆栈是一种非常高效的结构，但它的局限性包括：
- **只能访问栈顶元素**：堆栈限制了只能访问最顶部的元素，无法直接随机访问任何位置的元素。
- **溢出风险**：对于基于数组的实现，如果栈超过预设大小，会产生溢出问题。
- **应用受限**：对于需要随机访问或双向遍历的应用场景，堆栈并不适用。

### 8. 总结

堆栈是一种重要的数据结构，广泛应用于程序运行管理和算法设计中。C++ 提供了 `std::stack` 方便我们使用堆栈，同时我们也可以基于数组或链表手动实现堆栈，来适应不同的应用场景。理解和掌握堆栈的实现和应用，有助于编写高效的算法和程序。