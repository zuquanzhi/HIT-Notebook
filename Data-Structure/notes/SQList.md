
---

# 学习笔记：顺序表（SQList）的理解与实现

## 1. 什么是顺序表（SQList） ß
顺序表是一种常见的线性数据结构，其特点是通过一组连续的内存空间来存储数据元素。在顺序表中，每个元素都有一个直接的前驱和后继（除了第一个元素没有前驱，最后一个元素没有后继）。顺序表的操作主要包括插入、删除、查找等。

## 2. 顺序表的特点
### 优点

- **访问速度快**：由于元素在内存中是连续存储的，因此可以通过索引直接访问，时间复杂度为 O(1)。
- **易于实现**：使用数组或容器如 `std::vector` 可以轻松实现顺序表。

### 缺点

- **插入和删除效率低**：当在表中间插入或删除元素时，需要移动后续的所有元素，最坏情况下的时间复杂度为 O(n)。
- **空间预分配**：需要提前知道表的最大容量，否则可能会导致内存不足。

## 3. 顺序表的实现

```cpp
#include <iostream>
#include <vector>

class SQList {
private:
    std::vector<int> elements;
    int size; // 当前顺序表的实际大小

public:
    SQList() : size(0) {}

    // 向顺序表中添加元素
    void add(int elem) {
        elements.push_back(elem);
        ++size;
    }

    // 根据索引获取元素
    int get(int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds." << std::endl;
            return -1; // 或者抛出异常
        }
        return elements[index];
    }

    // 删除指定索引处的元素
    bool remove(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds." << std::endl;
            return false;
        }
        elements.erase(elements.begin() + index);
        --size;
        return true;
    }

    // 打印顺序表的内容
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << get(i) << " ";
        }
        std::cout << std::endl;
    }

    // 获取顺序表的大小
    int getSize() const {
        return size;
    }
};

int main() {
    SQList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.print(); // 输出: 1 2 3

    list.remove(1);
    list.print(); // 输出: 1 3

    return 0;
}
```
## 4. 时间复杂度分析

- **访问**: O(1)，直接通过索引访问。
- **插入**: 最坏情况下为 O(n)，当插入位置位于表的开头或中间时。
- **删除**: 最坏情况下为 O(n)，当删除位置位于表的开头或中间时。
- **查找**: O(n)，需要遍历整个表。

## 5. 应用场景

顺序表适合用于需要频繁访问但插入和删除较少的情况，例如缓存数据、静态数据集合等。