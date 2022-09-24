#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Backtrace {
private:
  /* data */
public:
  Backtrace(/* args */) {}
  ~Backtrace() {}

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

  void backtrace_131(std::string &s,
                     std::vector<std::vector<std::string>> &rets,
                     std::vector<string> &ret, int start) {
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

  void backtrace_93(std::string &s, std::vector<std::vector<std::string>> &rets,
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

  void backtrace_78(std::vector<int> &nums, std::vector<std::vector<int>> &rets,
                    std::vector<int> &ret, int start) {
    rets.push_back(ret);

    if (start >= nums.size()) {
      return;
    }

    for (int idx = start; idx < nums.size(); idx++) {
      ret.push_back(nums[idx]);
      backtrace_78(nums, rets, ret, idx + 1);
      ret.pop_back();
    }
  }

  void backtrace_47(std::vector<int> &nums, std::vector<std::vector<int>> &rets,
                    std::vector<int> &ret, vector<int> &used) {
    if (ret.size() == nums.size()) {
      rets.push_back(ret);
      return;
    }

    for (int idx = 0; idx < nums.size(); idx++) {
      // 去重 说明同一层已经被选中过了 这个是第二个1 {1， 1， 2， 2}
      if (idx > 0 && nums[idx] == nums[idx - 1] && used[idx - 1] == 0) {
        continue;
      }

      if (used[idx] == 0) {
        used[idx] = 1;
        ret.push_back(nums[idx]);

        backtrace_47(nums, rets, ret, used);
        used[idx] = 0;
        ret.pop_back();
      }
    }
  }

  bool IsValidQueue(std::vector<std::vector<char>> &ret) {
    // 如果矩阵里面的皇后全是正常
    struct pos {
      int x;
      int y;
    };

    std::vector<pos> position;
    for (int i = 0; i < ret.size(); i++) {
      for (int j = 0; j < ret[i].size(); j++) {
        if (ret[i][j] == 'Q') {
          pos tmp;
          tmp.x = i;
          tmp.y = j;
          position.push_back(tmp);
        }
      }
    }

    // 进行斜率判断
    for (int i = 0; i < position.size(); i++) {
      for (int j = 0; j < position.size(); j++) {
        if (i == j) {
          continue;
        }

        if (position[i].x == position[j].x || position[i].y == position[j].y) {
          return false;
        }

        if (abs(position[i].x - position[j].x) ==
            abs(position[i].y - position[j].y)) {
          return false;
        }
      }
    }

    return true;
  }

  void backtrace_51(int n, std::vector<std::vector<std::vector<char>>> &rets,
                    std::vector<std::vector<char>> &ret, int row) {
    if (IsValidQueue(ret) && row == n) {
      rets.push_back(ret);
      return;
    }

    for (int col = 0; col < n; col++) {
      if (IsValidQueue(ret)) {
        ret[row][col] = 'Q';
        backtrace_51(n, rets, ret, row + 1);
        ret[row][col] = '.';
      }
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

/*
给你一个整数数组 nums ，数组中的元素 互不相同
。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

 

示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]
 

提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/subsets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(backtrace, leetcode78) {

  std::unique_ptr<Backtrace> ptr = std::make_unique<Backtrace>();
  vector<int> nums{1, 2, 3};
  std::vector<std::vector<int>> rets;
  vector<int> ret;
  ptr->backtrace_78(nums, rets, ret, 0);

  for (int i = 0; i < rets.size(); i++) {
    for (int j = 0; j < rets[i].size(); j++) {
      cout << rets[i][j] << ".";
    }
    cout << endl;
  }
}

/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

 

示例 1：

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
示例 2：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/permutations-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(backtrace, leetcode47) {
  std::unique_ptr<Backtrace> ptr = std::make_unique<Backtrace>();
  vector<int> nums{1, 1, 2};
  std::vector<std::vector<int>> rets;
  vector<int> ret;
  vector<int> used(nums.size(), 0);
  ptr->backtrace_47(nums, rets, ret, used);

  for (int i = 0; i < rets.size(); i++) {
    for (int j = 0; j < rets[i].size(); j++) {
      cout << rets[i][j] << ".";
    }
    cout << endl;
  }
}

/*
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n
的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.'
分别代表了皇后和空位。

 

示例 1：


输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
示例 2：

输入：n = 1
输出：[["Q"]]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(backtrace, leetcode51) {
  int n = 4;
  std::unique_ptr<Backtrace> ptr = std::make_unique<Backtrace>();
  std::vector<std::vector<std::vector<char>>> rets;

  std::vector<std::vector<char>> ret(n, std::vector<char>(n, '.'));
  for (int i = 0; i < ret.size(); i++) {
    for (int j = 0; j < ret[i].size(); j++) {
      cout << ret[i][j];
    }
    cout << endl;
  }

  std::vector<std::vector<int>> used(n, std::vector<int>(n, 0));
  ptr->backtrace_51(n, rets, ret, 0);

  for (int i = 0; i < rets.size(); i++) {
    cout << "start" << endl;
    for (int j = 0; j < rets[i].size(); j++) {
      for (int k = 0; k < rets[i][j].size(); k++) {
        cout << rets[i][j][k];
      }
      cout << endl;
    }
    cout << "end" << endl;
  }
}