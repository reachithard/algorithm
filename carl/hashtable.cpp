#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

只有小写
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/valid-anagram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(hashtable, leetcode242) {
  string a = "hello";
  string b = "olleh";

  int cnt[26] = {0};
  for (int i = 0; i < a.size(); i++) {
    cnt[a[i] - 'a']++;
  }

  for (int i = 0; i < b.size(); i++) {
    cnt[b[i] - 'a']--;
  }

  ASSERT_TRUE(std::all_of(std::begin(cnt), std::end(cnt),
                          [](int i) { return i == 0; }));
}

/*
给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一
的。我们可以 不考虑输出结果的顺序 。
*/
TEST(hashtable, leetcode349) {
  vector<int> nums1{1, 2, 3};
  vector<int> nums2{3, 4};

  unordered_set<int> snum1(nums1.begin(), nums1.end());
  set<int> result;
  for (int i = 0; i < nums2.size(); i++) {
    if (snum1.find(nums2[i]) != snum1.end()) {
      result.insert(nums2[i]);
    }
  }

  for (auto it = result.begin(); it != result.end(); it++) {
    cout << *it << endl;
  }
}

/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值
target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(hashtable, leetcode1) {
  vector<int> nums{3, 3};
  int target = 6;

  unordered_map<int, int> hash;

  for (int i = 0; i < nums.size(); i++) {
    hash[nums[i]] = i; // 直接覆盖
  }

  int idx = -1;
  int idx1 = -1;
  for (int t = 0; t < nums.size(); t++) {
    if (hash.find(target - nums[t]) != hash.end()) {
      idx = hash[target - nums[t]];
      idx1 = t;
      break;
    }
  }

  cout << idx << " " << idx1 << endl;
}

/*
给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n
，请你计算有多少个元组 (i, j, k, l) 能满足：

0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/4sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(hashtable, leetcode454) {
  vector<int> nums1;
  vector<int> nums2;
  vector<int> nums3;
  vector<int> nums4;

  unordered_map<int, int> tt;
  int cnt = 0;
  for (int i = 0; i < nums1.size(); i++) {
    for (int j = 0; j < nums2.size(); j++) {
      tt[nums1[i] + nums2[j]]++;
    }
  }

  for (int i = 0; i < nums3.size(); i++) {
    for (int j = 0; j < nums4.size(); j++) {
      if (tt.find(-nums3[i] - nums4[j]) != tt.end()) {
        cnt += tt[-nums3[i] - nums4[j]];
      }
    }
  }
}

/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a
+ b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(hashtable, leetcode15) {
  vector<int> nums{-1, 0, 1, 2, -1, -1, -4};

  // a + b = -c
  sort(nums.begin(), nums.end());

  for (int i = 0; i < nums.size(); i++) {
    int last = INT32_MIN;
    for (int j = i + 1, k = nums.size() - 1; j < k;) {
      if (nums[j] + nums[k] == -nums[i]) {
        if (last != nums[j]) {
          // 这里是一个
          cout << "i " << nums[i] << " j" << nums[j] << " k" << nums[k] << endl;
          last = nums[j];
          i++;
          k--;
        }
      } else if (nums[j] + nums[k] < -nums[i]) {
        j++;
      } else {
        k--;
      }
    }
  }
}

/*
给你一个由 n 个整数组成的数组 nums ，和一个目标值 target
。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c],
nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(hashtable, leetcode18) {
  vector<int> nums{2, 2, 2, 2, 2};
  int target = 8;
  sort(nums.begin(), nums.end());

  int left = INT32_MIN;
  int right = INT32_MIN;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      for (int k = j + 1, t = nums.size() - 1; k < t;) {
        if (nums[i] + nums[j] + nums[k] == target - nums[t]) {
          // 进行去重

          if (left != nums[k] || right != nums[t]) {
            left = nums[k];
            right = nums[t];
            cout << "i " << nums[i] << " j" << nums[j] << " k" << nums[k]
                 << " t" << nums[t] << " left" << left << " right" << right
                 << endl;
          }
          t--;
          k++;
        } else if (nums[i] + nums[j] + nums[k] > target - nums[t]) {
          t--;
        } else {
          k++;
        }
      }
    }
  }
}