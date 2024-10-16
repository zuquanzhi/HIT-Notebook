# KMP 算法（Knuth-Morris-Pratt）笔记

## 1. 算法简介
KMP 算法用于 **字符串匹配**，通过预处理模式串，避免重复的字符比较，从而实现高效匹配。它的时间复杂度是 **O(n + m)**，其中 n 是主串长度，m 是模式串长度。

## 2. 主要思想
当模式串中的某个字符匹配失败时，利用已知的部分匹配结果，跳过不必要的比较。这是通过 **部分匹配表**（也称为 **前缀表**）实现的。

## 3. 术语解释
- **前缀**：从字符串的第一个字符开始，不包含最后一个字符的子串。
- **后缀**：从字符串的最后一个字符开始，不包含第一个字符的子串。
- **部分匹配表**：记录每个字符位置前的部分字符串的最长相同前缀和后缀的长度。

## 4. 部分匹配表的构建
部分匹配表记录模式串在匹配失败时，可以跳过的字符数量。假设模式串为 `pattern`，前缀表 `prefix[i]` 的值表示在 `pattern[0...i]` 中，最长相同前缀和后缀的长度。

**构建步骤**：
1. 初始时，`prefix[0] = 0`，表示第一个字符没有前缀和后缀。
2. 使用双指针法遍历模式串，一个指针指向当前字符，一个指向最长前缀的下一个字符。
3. 若当前字符匹配，前缀长度加 1；否则，回退到前一个匹配的前缀位置。

## 5. KMP 主算法步骤
1. 预处理模式串，计算其部分匹配表。
2. 在主串中按顺序比较字符，若匹配成功，则继续比较下一个字符；若匹配失败，根据部分匹配表跳过一部分字符，减少不必要的比较。
3. 重复步骤 2 直到找到所有匹配位置或遍历完整个主串。

## 6. KMP 代码实现

```cpp
#include <iostream>
#include <cstring>
using namespace std;

// 计算部分匹配表（前缀表）
void computePrefixFunction(const char* pattern, int m, int* prefix) {
    int k = 0;
    prefix[0] = 0;
    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            ++k;
        }
        prefix[i] = k;
    }
}

// KMP 主算法，返回匹配的起始位置
void kmpSearch(const char* text, const char* pattern, int* matches, int& match_count) {
    int n = strlen(text);
    int m = strlen(pattern);
    int prefix[m];
    computePrefixFunction(pattern, m, prefix);

    int q = 0;
    match_count = 0;
    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }
        if (pattern[q] == text[i]) {
            ++q;
        }
        if (q == m) {
            matches[match_count++] = i - m + 1;
            q = prefix[q - 1];
        }
    }
}

int main() {
    const char* text = "ABABDABACDABABCABAB";
    const char* pattern = "ABABCABAB";
    int matches[100];
    int match_count;
    kmpSearch(text, pattern, matches, match_count);
    
    if (match_count == 0) {
        cout << "未找到匹配" << endl;
    } else {
        cout << "匹配位置：";
        for (int i = 0; i < match_count; ++i) {
            cout << matches[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

## 7. 时间复杂度
- **预处理模式串**：O(m)
- **主串匹配**：O(n)
因此，整个算法的时间复杂度为 **O(n + m)**。

## 8. 应用场景
KMP 算法适用于以下场景：
- 字符串匹配问题，例如在文本中查找某个单词或子字符串。
- DNA 序列匹配等生物信息学领域。

## 9. 优势
- 当模式串包含大量重复部分时，KMP 算法能显著减少比较次数，效率高于朴素的字符串匹配算法。
