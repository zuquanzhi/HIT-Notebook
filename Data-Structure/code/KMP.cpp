#include <iostream>
#include <cstring> // 用于 memset
using namespace std;

// 计算部分匹配表（前缀表）
void computePrefixFunction(const char* pattern, int m, int* prefix) {
    int k = 0; // k是当前匹配的长度
    prefix[0] = 0; // 第一个元素的部分匹配值为0

    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefix[k - 1]; // 回退到前一个最长匹配的位置
        }
        if (pattern[k] == pattern[i]) {
            ++k; // 匹配成功，增加匹配长度
        }
        prefix[i] = k; // 更新部分匹配表
    }
}

// KMP 主算法，返回匹配的起始位置，匹配次数通过 `match_count` 返回
void kmpSearch(const char* text, const char* pattern, int* matches, int& match_count) {
    int n = strlen(text);    // 主串长度
    int m = strlen(pattern); // 模式串长度
    int prefix[m];           // 部分匹配表

    computePrefixFunction(pattern, m, prefix); // 计算部分匹配表

    int q = 0; // 当前匹配的字符个数
    match_count = 0; // 初始化匹配计数

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1]; // 回退到前一个最长匹配的位置
        }
        if (pattern[q] == text[i]) {
            ++q; // 当前字符匹配成功
        }
        if (q == m) { // 完全匹配
            matches[match_count++] = i - m + 1; // 记录匹配的起始位置
            q = prefix[q - 1]; // 继续寻找下一个匹配
        }
    }
}

int main() {
    const char* text = "ABABDABACDABABCABAB"; // 主串
    const char* pattern = "ABABCABAB"; // 模式串
    int matches[100]; // 假设匹配结果不超过100个
    int match_count; // 匹配的次数

    kmpSearch(text, pattern, matches, match_count);

    // 输出匹配结果
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