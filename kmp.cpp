#include <iostream>
#include <vector>
using namespace std;

// 构建前缀表
vector<int> compute_prefix_table(const string& pattern) {
    vector<int> prefix_table(pattern.length(), 0);  // 创建前缀表，初始值都是0
    int length = 0;
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;  // 前缀和后缀相等的长度增加
            prefix_table[i] = length;  // 记录当前位置的前缀和后缀相等的长度
            i++;
        } else {
            if (length != 0) {
                length = prefix_table[length - 1];  // 如果不相等，回退到上一个匹配的位置
            } else {
                prefix_table[i] = 0;  // 没有匹配，将当前位置的前缀和后缀相等的长度设为0
                i++;
            }
        }
    }

    return prefix_table;
}

// 使用KMP算法计算子字符串在主字符串中出现的次数
int count_substring_occurrences(const string& s1, const string& s2) {
    vector<int> prefix_table = compute_prefix_table(s1);  // 构建前缀表
    int count = 0;  // 记录出现次数
    int i = 0;  // 主字符串的位置
    int j = 0;  // 模式字符串的位置

    while (i < s2.length()) {
        if (s1[j] == s2[i]) {
            i++;
            j++;

            if (j == s1.length()) {
                count++;  // 模式字符串完全匹配，出现次数加一
                j = prefix_table[j - 1];  // 根据前缀表回退到上一个匹配的位置
            }
        } else {
            if (j != 0) {
                j = prefix_table[j - 1];  // 如果不匹配，根据前缀表回退到上一个匹配的位置
            } else {
                i++;
            }
        }
    }

    return count;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    int result = count_substring_occurrences(s1, s2);  // 使用KMP算法计算子字符串出现次数
    cout << result << endl;

    return 0;
}
