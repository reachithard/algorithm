#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Dp {
public:
  Dp() {}
  ~Dp() {}

  int dp_sample1(int w, std::vector<int> &weights, std::vector<int> &values) {
    /*
     * dp[i][j] 为第i个物品 质量为j的最大重量
     * dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i])
     */
    std::vector<std::vector<int>> dp(weights.size() + 1,
                                     std::vector<int>(w + 1, 0));
    // 初始化 dp[0][j] = values[0]
    if (weights.empty() || values.empty()) {
      return 0;
    }
    for (int i = weights[0]; i <= w; i++) {
      dp[0][i] = values[0];
    }

    for (int i = 1; i < weights.size(); i++) {
      for (int j = 0; j <= w; j++) {
        if (j < weights[i]) {
          dp[i][j] = dp[i - 1][j];
          continue;
        }
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
      }
    }

    for (int i = 0; i <= weights.size(); i++) {
      for (int j = 0; j <= w; j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    return dp.back().back();
  }

  int dp_494(int target, std::vector<int> &nums) {
    /*
    left + right = sum; left - right = target; left = (sum + target) / 2;
    dp[i][j]为第i个数和为j的方法数
    递推式确定:dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]] 即
    */
    int sum = 0;
    for (int &num : nums) {
      sum += num;
    }
    int diff = sum + target;
    if (diff < 0 || diff % 2 != 0) {
      return 0;
    }
    int n = nums.size(), neg = diff / 2;
    vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      int num = nums[i - 1];
      for (int j = 0; j <= neg; j++) {
        dp[i][j] = dp[i - 1][j];
        if (j >= num) {
          dp[i][j] += dp[i - 1][j - num];
        }
      }
    }

    for (int i = 0; i <= nums.size(); i++) {
      for (int j = 0; j <= neg; j++) {
        std::cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    /*
        进行滚动数组优化
        dp[j] 为值为j的方法数
        dp[j] += dp[j - nums[i]]; j为值为j的方法数，i为第几个数
    */
    vector<int> dp2(neg + 1, 0);
    dp2[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
      for (int j = neg; j >= nums[i]; j--) {
        dp2[j] += dp2[j - nums[i]];
      }
    }

    for (int i = 0; i < dp2.size(); i++) {
      cout << dp2[i] << " ";
    }
    cout << endl;

    return dp[n][neg];
  }

  int dp_474(int m, int n, std::vector<std::string> &strs) {
    /*
        dp[i][j][k]为第i个 j个0 k个1组成的最大子集数
        确定递推式 dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i - 1][j -
       strs[i]][k - strs[i]] + 1) 大于情况，否则dp[i][j][k] = dp[i - 1][j][k]
        dp[0][0][0] = 0;
    */
    std::vector<std::vector<std::vector<int>>> dp(
        strs.size() + 1,
        std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, 0)));
    dp[0][0][0] = 0;
    for (int i = 1; i <= strs.size(); i++) {
      int zero = std::count(strs[i - 1].begin(), strs[i - 1].end(), '0');
      int one = std::count(strs[i - 1].begin(), strs[i - 1].end(), '1');
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= n; k++) {
          if (j < zero || k < one) {
            dp[i][j][k] = dp[i - 1][j][k];
            continue;
          }
          dp[i][j][k] =
              std::max(dp[i - 1][j][k], dp[i - 1][j - zero][k - one] + 1);
        }
      }
    }

    for (int i = 0; i < dp.size(); i++) {
      cout << "start" << endl;
      for (int j = 0; j < dp[i].size(); j++) {
        for (int k = 0; k < dp[i][j].size(); k++) {
          cout << dp[i][j][k] << " ";
        }
        cout << endl;
      }
      cout << "end" << endl;
    }

    /*
      dp[j][k]为j个0 k个1的最大子集数
      递推式：dp[j][k] = std::max(dp[j][k], dp[j - strs[i]][k - strs[i]] + 1);
    */

    std::vector<std::vector<int>> dp2(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < strs.size(); i++) {
      int zero = std::count(strs[i].begin(), strs[i].end(), '0');
      int one = std::count(strs[i].begin(), strs[i].end(), '1');
      for (int j = m; j >= zero; j--) {
        for (int k = n; k >= one; k--) {
          dp2[j][k] = std::max(dp2[j][k], dp2[j - zero][k - one] + 1);
        }
      }
    }

    cout << "two begin" << endl;
    for (int i = 0; i < dp2.size(); i++) {
      for (int j = 0; j < dp2[i].size(); j++) {
        cout << dp2[i][j] << " ";
      }
      cout << endl;
    }
    cout << "two end" << endl;

    return dp.back().back().back();
  }

  int dp_sample2(int w, std::vector<int> &weights, std::vector<int> &values) {
    /*
        dp[i][j] 为第i个物品，重量为j的最大容量 但是这个物品能重复选取
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] +
       values[i]);
    */
    std::vector<std::vector<int>> dp(weights.size() + 1,
                                     std::vector<int>(w + 1, 0));

    
    for (int i = weights[0]; i <= (w / weights[0]) * weights[0]; i++) {
        if (i % weights[0] == 0) {
          dp[0][i] = dp[0][i - 1] + values[0];
        } else {
          dp[0][i] = dp[0][i - 1];
        }

    }
    for (int i = 1; i < weights.size(); i++) {
      for (int j = weights[i]; j <= w; j++) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
      }
    }

    for (int i = 0; i < dp.size(); i++) {
      for (int j = 0; j < dp[i].size(); j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    /*
      滚动数组
      dp[j] 为容量为j的最大值
      dp[j] = std::max(dp[j], dp[j - weight[i]]) i可重复
    */
    std::vector<int> dp2(w + 1, 0);
    for (int i = 0; i < weights.size(); i++) {
        for (int j = weights[i]; j <= w; j++) {
          dp2[j] = std::max(dp2[j], dp2[j - weights[i]] + values[i]);
        }
    }

    for (int i = 0; i < dp2.size(); i++) {
      cout << dp2[i] << " ";
    }
    cout << endl;
    return dp2[w];
  }

  int dp_518(int amount, std::vector<int> &coins) {
    /*
        dp[i][j] 为第i个硬币，值为j的方法数
        不选 则为dp[i - 1][j]
        选 则为dp[i][j] = dp[i - 1][j] + dp[i - 1][j - conis[i]]
    */
    std::vector<std::vector<int>> dp(coins.size() + 1,
                                     std::vector<int>(amount + 1, 0));

    dp[0][0] = 1;
    
    for (int i = 1; i <= coins.size(); i++) {
      for (int j = 0; j <= amount; j++) {
        for (int k = 0; k * coins[i - 1] <= j; k++) {
          dp[i][j] += dp[i - 1][j - k * coins[i - 1]];
        }
      }
    }

    for (int i = 0; i < dp.size(); i++) {
      for (int j = 0; j < dp[i].size(); j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    /**
     * @brief dp[j] 为值为j的方法数
     * dp[j] += dp[j - coins[i]]
     * 
     */
    std::vector<int> dp2(amount + 1, 0);
    dp2[0] = 1;
    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
          dp2[j] += dp2[j - coins[i]];
        }
    }

    for (int i = 0; i < dp2.size(); i++) {
      cout << dp2[i] << " ";
    }
    cout << endl;

    return dp[coins.size()][amount];
  }

  int dp_377(int target, std::vector<int> &nums) {
    /*
      dp[i][j] 为第i个数字，和为j的组合个数
      dp[i][j] += ∑(dp[i - 1][j - nums[i]])
      dp[0][0] = 1
    */
    std::vector<std::vector<int>> dp(nums.size() + 1, std::vector<int>(target + 1, 0));
    // std::sort(nums.begin(), nums.end(), std::greater<int>());
    dp[0][0] = 1;

    for (int j = 0; j <= target; j++) {
      for (int i = 1; i <= nums.size(); i++) {
        if (j >= nums[i - 1]) {
          for (int k = 0; k < i; k++) {
            dp[i][j] += dp[i][j - nums[k]];
          }
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
    for (int i = 0; i < dp.size(); i++) {
      for (int j = 0; j < dp[i].size(); j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    // TODO

    return dp.back().back();
  }

  int dp_sample3(int m, int n) {
    /*
      设dp[i][j] 为跨任意m个台阶数，到j的方法数
      dp[i][j] = dp[i - 1][j] + dp[i - 1][j - t]  1 <= t <= m
      dp[0][0] = 1
    */
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    dp[0][0] = 1;

    for (int j = 0; j <= n; j++) {
      for (int i = 1; i <= m; i++) {
        if (j >= i) {
          for (int k = 0; k <= i; k++) {
            dp[i][j] += dp[i][j - k];
          }
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    for (int i = 0; i < dp.size(); i++) {
      for (int j = 0; j < dp[i].size(); j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }
  }

  int dp_322(int amount, std::vector<int> &coins) {
    /*
      dp[i][j] 为前i枚硬币，组成的值为j的最小硬币数
      dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coins[t]] + 1) 0 <= t < i
      dp[0][0] = 0
    */
    std::vector<std::vector<int>> dp(coins.size() + 1, std::vector<int>(amount + 1, 105));
    dp[0][0] = 0;
    
    for (int j = 0; j <= amount; j++) {
      for (int i = 1; i <= coins.size(); i++) {
        int val = coins[i - 1];
        if (j < val) {
          dp[i][j] = dp[i - 1][j];
        } else {
          for (int k = 0; k < i; k++) {
            dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coins[k]] + 1);
          }
        }
      }
    }

    for (int i = 0; i < dp.size(); i++) {
      for (int j = 0; j < dp[i].size(); j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    /*
    一为滚动数组优化
      dp[j]为值为j的最小硬币数
      dp[j] = std::min(dp[j], dp[j - nums[i]] + 1);
    */
    std::vector<int> dp2(amount + 1, 105);   
    dp2[0] = 0;
    for (int i = 0; i < coins.size(); i++) {
      for (int j = coins[i]; j <= amount; j++) {
        dp2[j] = std::min(dp2[j], dp2[j - coins[i]] + 1);
      }
    }

    for (int i = 0; i < dp2.size(); i++) {
      cout << dp2[i] << " ";
    }
    cout << endl;
    return dp.back().back();
  }

  

};

TEST(dp, hello) {
  constexpr int size = 3;
  int a[size] = {0};
  for (int i = 0; i < size; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

/*
有背包容量为w，有一堆物品体积为weight， 价值为value 求最大
*/
TEST(dp, sample1) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> weight = {1, 3, 4};
  std::vector<int> value = {15, 20, 30};
  ptr->dp_sample1(4, weight, value);
}

/*
给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-'
，然后串联起来得到表达式 "+2-1" 。 返回可以通过上述方法构造的、运算结果等于
target 的不同 表达式 的数目。

 

示例 1：

输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
示例 2：

输入：nums = [1], target = 1
输出：1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/target-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_494) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> nums = {1, 1, 1, 1, 1};
  cout << ptr->dp_494(3, nums) << endl;
}

/*
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。

请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。

如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。

 

示例 1：

输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
输出：4
解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4
。 其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"}
不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。 示例 2：

输入：strs = ["10", "0", "1"], m = 1, n = 1
输出：2
解释：最大的子集是 {"0", "1"} ，所以答案是 2 。
 

提示：

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] 仅由 '0' 和 '1' 组成
1 <= m, n <= 100

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/ones-and-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_474) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<std::string> strs = {"10", "0001", "111001", "1", "0"};
  cout << ptr->dp_474(5, 3, strs) << endl;

  std::vector<std::string> strs1 = {"10", "0", "1"};
  cout << ptr->dp_474(1, 1, strs1) << endl;
}

/*
有背包容量为w，有一堆物品体积为weight， 价值为value 求最大 每个物品有无限个
*/
TEST(dp, sample2) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> weight = {1, 3, 4};
  std::vector<int> value = {15, 20, 30};
  ptr->dp_sample2(4, weight, value);
}

/*
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回
0 。

假设每一种面额的硬币有无限个。 

题目数据保证结果符合 32 位带符号整数。

 

示例 1：

输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
示例 2：

输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。
示例 3：

输入：amount = 10, coins = [10]
输出：1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/coin-change-2
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_518) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> coins = {1, 2, 5};
  ptr->dp_518(5, coins);

  std::vector<int> coins1 = {2};
  ptr->dp_518(3, coins1);

  std::vector<int> coins2 = {10};
  ptr->dp_518(10, coins2);
}

/*
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums
中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。

 

示例 1：

输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
示例 2：

输入：nums = [9], target = 3
输出：0
 

提示：

1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums 中的所有元素 互不相同
1 <= target <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/combination-sum-iv
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_377) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> nums = {1, 2, 3};
  ptr->dp_377(4, nums);
}

/*
多步爬楼梯 n个台阶 每一步可以选m台阶爬上去 有多少种方法
*/
TEST(dp, sample3) { 
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>(); 
  ptr->dp_sample3(3, 4);  
}

/*
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数
。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

 

示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1
示例 2：

输入：coins = [2], amount = 3
输出：-1
示例 3：

输入：coins = [1], amount = 0
输出：0
 

提示：

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/coin-change
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_322) {
  std::unique_ptr<Dp> ptr = std::make_unique<Dp>();
  std::vector<int> coins = {1, 2, 5};
  ptr->dp_322(11, coins);
}

/*
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数
是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9
和 16 都是完全平方数，而 3 和 11 不是。

 

示例 1：

输入：n = 12
输出：3
解释：12 = 4 + 4 + 4
示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/perfect-squares
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(dp, leetcode_279) {

}