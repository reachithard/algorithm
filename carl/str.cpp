#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

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

/*
给你一个字符串 s ，颠倒字符串中 单词 的顺序。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。

注意：输入字符串
s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-words-in-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

输入：s = "the sky is blue"
输出："blue is sky the"
*/
TEST(str, leetcode151) {
  string s = " the sky  is blue ";
  reverse(s.begin(), s.end());

  int lastpos = 0;
  int pos = 0;

  // 考虑前导 后导 以及中间空格
  for (; pos < s.size(); pos++) {
    if (s[pos] == ' ') {
      reverse(s.begin() + lastpos, s.begin() + pos);
      lastpos = pos + 1;
    }
  }
  reverse(s.begin() + lastpos, s.begin() + pos);

  cout << s << endl;
  // 去除多余空格 用双指针去除 一个实际的 一个遍历的
  int sIdx = 0;
  int cur = 0;
  for (; cur < s.size(); cur++) {
    if (s[sIdx] == ' ' && s[cur] == ' ') {
      continue;
    } else {
      s[sIdx++] = s[cur];
    }
  }

  cout << "s trim:" << string(s.data(), sIdx) << endl;
}

/*
实现 strStr() 函数。

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle
字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

说明：

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及
Java 的 indexOf() 定义相符。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(str, leetcode28) {
  std::string haystack = "hello";
  std::string needle = "abca";

  vector<int> next(needle.size(), -1);
  // 构建next数组
  int j = -1;
  for (int i = 1; i < needle.size(); i++) {
    while (j >= 0 && needle[i] != needle[j + 1]) {
      j = next[j];
    }

    if (needle[i] == needle[j + 1]) {
      j++;
    }

    next[i] = j;
  }

  cout << "next ";
  for (int t = 0; t < next.size(); t++) {
    cout << next[t] << " ";
  }
  cout << endl;

  int t = -1;
  for (int i = 0; i < haystack.size(); i++) {
    while (t >= 0 && haystack[i] != needle[t + 1]) {
      t = next[t]; // 回退了 1 1 2 1 1 回退到 2
    }

    if (haystack[i] == needle[t + 1]) {
      t++;
    }

    if (t == (needle.size() - 1)) {
      cout << "find" << i - needle.size() + 1 << endl;
      break;
    }
  }
}

/*
给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。
*/
// TODO
TEST(str, leetcode459) {
  // 1. 暴力解 枚举所有
  // 2. s + s .find(s , 1);
  // 3. kmp
  std::string s = "abcabc";

  vector<int> next(s.size(), -1);

  int p = -1;
  for (int t = 1; t < s.size(); t++) {
    while (p >= 0 && s[t] != s[p + 1]) {
      p = next[p];
    }

    if (s[t] == s[p + 1]) {
      p++;
    }
    next[t] = p;
  }

  if (next[s.size() - 1] != 0 && s.size() % (next[s.size() - 1]) == 0) {
    cout << " true " << endl;
  } else {
    cout << " false " << endl;
  }
}