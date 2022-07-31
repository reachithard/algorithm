#include <gtest/gtest.h>

#include <iostream>
#include <string>

using namespace std;

/*
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s
的形式给出。

不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1)
的额外空间解决这一问题。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(str, leetcode344) {
    std::string b = "hello";
    for (int i = 0, j = b.size() - 1; i < j; i++, j--) {
        swap(b[i], b[j]);
    }

    cout << b << endl;
}

/*
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k
字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-string-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(str, leetcode541) {
    std::string b = "111112jk3jlk1jljljsljs";
    int k = 3;
    int start = 0;
    for (; start + 2 * k < b.size(); start += 2 * k) {
        std::reverse(b.begin() + start, b.begin() + start + k);
    }

    std::reverse(b.begin() + start, b.end());

    cout << b << endl;
}