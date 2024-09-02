

### 链表基础知识

**定义：**
链表是一种线性数据结构，其中元素不是在内存中连续存放的，而是通过指针链接在一起。每个元素称为一个节点，每个节点包含数据域和指向下一个节点的指针。

**链表节点结构：**
```cpp
struct ListNode {
    int val;       // 节点存储的数据
    ListNode *next; // 指向下一个节点的指针
    ListNode(int x) : val(x), next(nullptr) {} // 构造函数
};
```

### 链表的基本操作

#### 创建链表
```cpp
ListNode* createLinkedList(const std::vector<int>& elements) {
    if (elements.empty()) return nullptr;
    ListNode *head = new ListNode(elements[0]), *current = head;
    for (size_t i = 1; i < elements.size(); ++i) {
        current->next = new ListNode(elements[i]);
        current = current->next;
    }
    return head;
}
```

#### 插入节点
```cpp
void insertNode(ListNode*& head, int pos, int val) {
    ListNode *newNode = new ListNode(val);
    if (pos == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        ListNode *temp = head;
        for (int i = 0; temp != nullptr && i < pos - 1; i++) {
            temp = temp->next;
        }
        if (temp != nullptr) {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}
```

#### 删除节点
```cpp
void deleteNode(ListNode*& head, int pos) {
    if (head == nullptr || pos < 0) return;
    if (pos == 0) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    } else {
        ListNode *temp = head;
        for (int i = 0; temp != nullptr && i < pos - 1; i++) {
            temp = temp->next;
        }
        if (temp != nullptr && temp->next != nullptr) {
            ListNode *toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
    }
}
```

#### 打印链表
```cpp
void printList(ListNode *head) {
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}
```

### 高级操作

#### 反转链表
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head, *next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

#### 查找中间节点
```cpp
ListNode* findMiddleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

#### 合并两个有序链表
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummyHead(0);
    ListNode *current = &dummyHead;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    current->next = (l1 != nullptr ? l1 : l2);
    return dummyHead.next;
}
```

#### 删除链表中的重复节点
```cpp
ListNode* removeDuplicates(ListNode* head) {
    ListNode *current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->val == current->next->val) {
            ListNode *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
    return head;
}
```

#### 检查链表是否有环
```cpp
bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
```

#### 使用递归处理链表
```cpp
ListNode* reverseListRecursively(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* rest = reverseListRecursively(head->next);
    head->next->next = head;
    head->next = nullptr;
    return rest;
}
```

### 应用场景
链表在实际应用中有很多用途，例如：
- 在浏览器的历史记录中，可以使用链表来保存用户访问过的页面。
- 在音乐播放器中，可以使用链表来保存播放列表。
- 在实现LRU缓存算法时，可以结合链表和哈希表来快速地添加和删除元素。

### 总结
链表是一种灵活的数据结构，它允许动态地改变其大小。虽然链表的访问速度不如数组快，但在插入和删除操作上具有优势。掌握链表的基本操作和一些高级技巧对于解决复杂的数据结构问题非常有用。