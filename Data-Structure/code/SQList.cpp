#include <iostream>
#include <vector>

class SQList {
private:
    std::vector<int> data;
    int length;

public:
    SQList() : length(0) {} // 构造函数

    bool IsEmpty() const { return length == 0; } // 判断是否为空

    int GetLength() const { return length; } // 获取长度

    bool Insert(int index, int elem) {
        if (index < 0 || index > length) return false;
        data.insert(data.begin() + index, elem); // 在指定位置插入元素
        ++length;
        return true;
    }

    bool Remove(int index) {
        if (index < 0 || index >= length) return false;
        data.erase(data.begin() + index); // 删除指定位置的元素
        --length;
        return true;
    }

    int GetElement(int index) const {
        if (index < 0 || index >= length) return -1;
        return data[index]; // 返回指定位置的元素
    }
};

// 检查函数
void check() {
    SQList list;
    list.Insert(0, 1);
    list.Insert(1, 3);
    list.Insert(1, 2);

    std::cout << "After insertions: ";
    for (int i = 0; i < list.GetLength(); ++i) {
        std::cout << list.GetElement(i) << " ";
    }
    std::cout << std::endl;

    list.Remove(1);

    std::cout << "After removal: ";
    for (int i = 0; i < list.GetLength(); ++i) {
        std::cout << list.GetElement(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    check();
    return 0;
}