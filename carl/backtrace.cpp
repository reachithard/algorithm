#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Backtrace
{
private:
    /* data */
public:
    Backtrace(/* args */) {

    }
    ~Backtrace() {

    }


    bool IsPrime(std::vector<char> &ret) {
        int left = 0;
        int right = ret.size() - 1;
        for (; left <= right; left++, right--) {
            if (ret[left] != ret[right]) {
                return false;
            }
        }

        return true;
    }

    bool IsPalindrome(std::string &s, int start, int end) {
      int left = start;
      int right = end;
      for (; left < right; left++, right--) {
        if (s[left] != s[right]) {
          return false;
        }
      }

      return true;
    }

    void backtrace_131(std::string &s, std::vector<std::vector<std::string>> &rets, std::vector<string> &ret, int start) {
        if (start >= s.size()) {
            rets.push_back(ret);
            return;
        }

        for (int idx = start; idx < s.size(); idx++) {
            if (IsPalindrome(s, start, idx)) {
                std::string tmp = s.substr(start, idx - start + 1);
                ret.push_back(tmp);
            } else {
                continue;
            }

            backtrace_131(s, rets, ret, idx + 1);
            ret.pop_back();
        }
    }

    bool IsValidIp(std::string &s, int start, int end) {
        if (s.size() > 1 && s[0] == 0) {
            return false;
        } 
        std::string tmp = s.substr(start, end - start + 1);
        long long ip = std::stoll(tmp);
        return ip >= 0 && ip <= 255;
    }

    void backtrace_93(std::string &s,
                       std::vector<std::vector<std::string>> &rets,
                       std::vector<string> &ret, int start) {
      if (ret.size() == 4 && start >= s.size()) {
        rets.push_back(ret);
        return;
      }

      for (int idx = start; idx < s.size(); idx++) {
        if (IsValidIp(s, start, idx)) {
          std::string tmp = s.substr(start, idx - start + 1);
          ret.push_back(tmp);
        } else {
          continue;
        }

        backtrace_93(s, rets, ret, idx + 1);
        ret.pop_back();
      }
    }
};


TEST(backtrace, leetcode131) {
    std::string s = "aab";
    std::vector<std::string> ret;
    std::unique_ptr<Backtrace> ptr = std::make_unique<Backtrace>();

    std::vector<std::vector<std::string>> rets;
    ptr->backtrace_131(s, rets, ret, 0);

    for (int i = 0; i < rets.size(); i++) {
        for (int j = 0; j < rets[i].size(); j++) {
            cout << rets[i][j] << endl;
        }
    }

    // vector<char> m{'a', 'b', 'b'};
    // bool ispri = ptr->IsPrime(m);
    // ASSERT_TRUE(ispri);
}

/*
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导
0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是
"0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP
地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s
中的任何数字。你可以按 任何 顺序返回答案。

 

示例 1：

输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
示例 2：

输入：s = "0000"
输出：["0.0.0.0"]
示例 3：

输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 

提示：

1 <= s.length <= 20
s 仅由数字组成

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/restore-ip-addresses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(backtrace, leetcode93) {
  std::string s = "25525511135";
  std::vector<std::string> ret;
  std::unique_ptr<Backtrace> ptr = std::make_unique<Backtrace>();

  std::vector<std::vector<std::string>> rets;
  ptr->backtrace_93(s, rets, ret, 0);

  for (int i = 0; i < rets.size(); i++) {
    for (int j = 0; j < rets[i].size(); j++) {
      cout << rets[i][j] << ".";
    }
    cout << endl;
  }
}