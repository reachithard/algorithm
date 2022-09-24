#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Greedy {
public:
  Greedy() {}
  ~Greedy() {}

  int greedy_452(std::vector<std::vector<int>> &points) {
    if (points.empty()) {
      return 0;
    }
    std::sort(points.begin(), points.end(),
              [](std::vector<int> &item1, std::vector<int> &item2) -> bool {
                return item1[0] < item2[0];
              });

    for (int i = 0; i < points.size(); i++) {
      cout << points[i][0] << points[i][1] << endl;
    }
    int start = INT32_MIN;
    int end = INT32_MAX;
    int ret = 1;
    for (int idx = 0; idx < points.size(); idx++) {
      if (end < points[idx][0] || start > points[idx][1]) {
        ret++;
        start = points[idx][0];
        end = points[idx][1];
      } else {
        start = std::max(points[idx][0], start);
        end = std::min(points[idx][1], end);
        std::cout << "start" << start << "end" << end << endl;
      }
    }
    return ret;
  }

  int greedy_56(std::vector<std::vector<int>> &points,
                std::vector<std::vector<int>> &rets) {
    if (points.empty()) {
      return 0;
    }
    std::sort(points.begin(), points.end(),
              [](std::vector<int> &item1, std::vector<int> &item2) -> bool {
                return item1[0] < item2[0];
              });

    for (int i = 0; i < points.size(); i++) {
      cout << points[i][0] << points[i][1] << endl;
    }

    int start = points[0][0];
    int end = points[0][1];

    for (int idx = 0; idx < points.size(); idx++) {
      if (points[idx][0] > end || points[idx][1] < start) {
        rets.emplace_back(std::vector<int>{start, end});
        start = points[idx][0];
        end = points[idx][1];
      } else {
        start = std::min(start, points[idx][0]);
        end = std::max(end, points[idx][1]);
        std::cout << "start" << start << "end" << end << endl;
      }
    }
    rets.emplace_back(std::vector<int>{start, end});

    return 0;
  }
};

TEST(greedy, hello) { std::cout << "hello1" << std::endl; }

/**
有一些球形气球贴在一堵用 XY
平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart,
xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x
处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足
 xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。
弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。

 
示例 1：

输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。
示例 2：

输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。
示例 3：

输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 */
TEST(greedy, leetcode452) {
  std::unique_ptr<Greedy> ptr = std::make_unique<Greedy>();
  std::vector<std::vector<int>> point1 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
  std::cout << ptr->greedy_452(point1) << std::endl;

  std::vector<std::vector<int>> point2 = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  std::cout << ptr->greedy_452(point2) << std::endl;

  std::vector<std::vector<int>> point3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::cout << ptr->greedy_452(point3) << std::endl;
}

/**
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti,
endi]
。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

 

示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 

提示：

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
通过次数530,400提交次数1,079,785

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/merge-intervals
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 */
TEST(greedy, leetcode56) {
  std::unique_ptr<Greedy> ptr = std::make_unique<Greedy>();
  std::vector<std::vector<int>> point1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  std::vector<std::vector<int>> rets1;
  ptr->greedy_56(point1, rets1);

  for (int i = 0; i < rets1.size(); i++) {
    cout << "rets1 " << rets1[i][0] << rets1[i][1] << endl;
  }

  std::vector<std::vector<int>> point2 = {{1, 4}, {4, 5}};
  std::vector<std::vector<int>> rets2;
  ptr->greedy_56(point2, rets2);

  for (int i = 0; i < rets2.size(); i++) {
    cout << "rets2 " << rets2[i][0] << rets2[i][1] << endl;
  }

  std::vector<std::vector<int>> point3 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
  std::vector<std::vector<int>> rets3;
  ptr->greedy_56(point3, rets3);

  for (int i = 0; i < rets3.size(); i++) {
    cout << "rets3 " << rets3[i][0] << rets3[i][1] << endl;
  }
}