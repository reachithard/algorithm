#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

/*
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target
 ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-search
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
namespace leetcode704 {
uint32_t TwoDivideSearch(const vector<int> &nums, int target) {
  // 定义的是[left, right]
  uint32_t left = 0;
  uint32_t right = nums.size() - 1;
  uint32_t find = -1;
  while (left <= right) { // 注意这里是<= 例如[0, 999] 当找501时
    /*
     * mid left right
     * 499 0 999
     * 749 500 999
     * 624 500 748
     * 561 500 623
     * 530 500 560
     * 514 500 529
     * 506 500 513
     * 502 500 505
     * 500 500 501
     * 501 501 501 // 如果小于等于则还有这一次查找 因为单数与双数会变小
     */
    uint32_t mid = (right - left) / 2 + left;
    cout << mid << " " << left << " " << right << endl;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else {
      return mid;
    }
  }
  return -1;

//   // [left, right)
//   uint32_t left = 0;
//   uint32_t right = nums.size();
//   while (left < right)
//   {
//     /* code */
//     uint32_t mid = (right - left) / 2 + left;
//     if (nums[mid] < target) {
//       left = mid + 1;
//     } else if (nums[mid] > target) {
//       right = mid;
//     } else {
//       return mid;
//     }
//   }
//   return -1;
  
}
} // namespace leetcode704

TEST(array, leetcode704) {
  using namespace std;
  using namespace leetcode704;
  vector<int> nums;
  for (int i = 0; i < 1000; i++) {
    nums.push_back(i);
  }

  std::sort(nums.begin(), nums.end());

  int target = 501;
  for (uint32_t i = 0; i < nums.size(); i++) {
    cout << nums[i] << endl;
  }

  int idx = TwoDivideSearch(nums, target);
  cout << idx << endl;
}

/*
给你一个数组 nums 和一个值 val，你需要 原地
移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

 

说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(array, leetcode27) {
  using namespace std;
  vector<int> nums{0, 1, 2, 3, 3, 0, 4};

  uint32_t left = 0;
  uint32_t right = nums.size() - 1;
  int target = 2;
  // 双指针解法， 比carl更优？ 减少了很多拷贝? nums[slow++] = nums[fast]; 
  for (int i = 0; i < right;) {
    if (nums[i] != target) {

      i++;
      left++;
    } else {
        swap(nums[i], nums[right]);
        right--;
    }
  }

//   uint32_t slow = 0;
//   for (uint32_t fast = 0; fast < nums.size(); fast++) {
//     if (nums[fast] != target) {
//         nums[slow++] = nums[fast];
//     }
//   }
  
  for (int i = 0; i < nums.size(); i++) {
    cout << nums[i] << endl;
  }
}

/*
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ...,
numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-size-subarray-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(array, leetcode209) {
  using namespace std;
  vector<int> nums{0, 1, 2, 3, 3, 0, 4};
  int target = 3;
  int min = 0;
  int sum = 0;
  for (int i = 0, j = 0; j < nums.size(); j++) {
    sum += nums[j];
    while (sum >= target) { // 这里需要一直变换i的位置 而不是只变换一次
        min = std::min(min, j - i + 1);
        sum -= nums[i];
        i++;
    }
  }
  cout << min << endl;
}

/*
给你一个正整数 n ，生成一个包含 1 到 n平方 所有元素，且元素按顺时针顺序螺旋排列的 n
x n 正方形矩阵 matrix 。
*/
TEST(array, leetcode59) {
    int n = 3;
    vector<vector<int>> result(n, vector<int>(n, 0));

    int loop = n / 2;

    int xoff = 0;
    int yoff = 0;
    int off = 1;
    int count = 1;
    while (loop--) {
        int i = xoff;
        int j = yoff;
        for (; i < xoff + n - off; i++) {
            result[i][j] = count++;
        }

        for (; j < yoff + n - off; j++) {
          result[i][j] = count++;
        }

        for (; i >= xoff; i--) {
          result[i][j] = count++;
        }

        for (; j >= yoff; j--) {
          result[i][j] = count++;
        }

        xoff++;
        yoff++;
        off += 2;
    } 

    if (n % 2) {
        result[n / 2] [n / 2] = count;
    }

    for (int i = 0; i < result[0].size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}