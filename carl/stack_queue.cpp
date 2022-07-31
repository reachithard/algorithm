#include <gtest/gtest.h>

#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

namespace leetcode232 {
class Queue {
public:
  void push(int x) { st1.push(x); }

  int pop() {
    if (st2.empty()) {
      while (!st1.empty()) {
        /* code */
        st2.push(st1.top());
        st1.pop();
      }
    }

    int x = st2.top();
    st2.pop();
    return x;
  }

  int peek() {
    if (st2.empty()) {
      while (!st1.empty()) {
        /* code */
        st2.push(st1.top());
        st1.pop();
      }
    }

    int x = st2.top();
    return x;
  }

  bool empty() { return st1.empty() && st2.empty(); }

private:
  stack<int> st1;
  stack<int> st2;
};
} // namespace leetcode232

/*
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：

你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size,
和 is empty 操作是合法的。 你所使用的语言也许不支持栈。你可以使用 list 或者
deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-queue-using-stacks
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(stack_queue, leetcode232) {
  using namespace leetcode232;

  Queue s;
  s.push(1);
  s.push(2);
  s.push(3);

  cout << s.peek() << endl;

  while (!s.empty()) {
    cout << s.pop() << endl;
  }
}

namespace leetcode225 {
class Stack {
public:
  void push(int x) {
    que1.push(x);
    while (!que2.empty()) {
      /* code */
      que1.push(que2.front());
      que2.pop();
    }

    while (!que1.empty()) {
      que2.push(que1.front());
      que1.pop();
    }
  }

  int pop() {
    int x = que2.front();
    que2.pop();
    return x;
  }

  int top() { return que2.front(); }

  bool empty() { return que2.empty(); }

private:
  queue<int> que1;
  queue<int> que2;
};
} // namespace leetcode225

/*
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop
和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 

注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is
empty 这些操作。 你所使用的语言也许不支持队列。 你可以使用 list （列表）或者
deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-stack-using-queues
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(stack_queue, leetcode225) {
  using namespace leetcode225;
  Stack s;
  s.push(1);
  s.push(2);
  s.push(3);

  cout << s.top() << endl;

  while (!s.empty()) {
    cout << s.pop() << endl;
  }
}

/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(stack_queue, leetcode20) {
  string s = "()[]{}}";
  stack<char> st;
  bool err = false;
  // 利用隐式转换
  for (char c : s) {
    switch (c) {
    case '{':
    case '(':
    case '[':
      /* code */
      st.push(c);
      break;
    case ']': {
      if (st.empty()) {
        err = true;
        goto error;
      }
      if (st.top() == '[') {
        st.pop();
      } else {
        err = true;
        goto error;
      }
    } break;
    case ')': {
      if (st.empty()) {
        err = true;
        goto error;
      }
      if (st.top() == '(') {
        st.pop();
      } else {
        err = true;
        goto error;
      }
    } break;
    case '}': {
      if (st.empty()) {
        err = true;
        goto error;
      }
      if (st.top() == '{') {
        st.pop();
      } else {
        err = true;
        goto error;
      }
    } break;
    }
  }

error:
  if (err) {
    cout << "get error" << endl;
  }
}

/*
根据 逆波兰表示法，求表达式的值。

有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

注意 两个整数之间的除法只保留整数部分。

可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为
0 的情况。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：

输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：

输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 

提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200]
内的一个整数  

逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + *
也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(stack_queue, leetcode150) {
  stack<string> st;
  vector<string> pp = {"2", "1", "+", "3", "*"};

  for (string &t : pp) {
    if (t == "+") {
      // 拿两个数做运算
      string a = st.top();
      st.pop();
      string b = st.top();
      st.pop();

      int tmp = std::stoi(a) + std::stoi(b);
      st.push(to_string(tmp));
    } else if (t == "-") {
      // 拿两个数做运算
      string a = st.top();
      st.pop();
      string b = st.top();
      st.pop();

      int tmp = std::stoi(a) - std::stoi(b);
      st.push(to_string(tmp));
    } else if (t == "*") {
      // 拿两个数做运算
      string a = st.top();
      st.pop();
      string b = st.top();
      st.pop();

      int tmp = std::stoi(a) * std::stoi(b);
      st.push(to_string(tmp));
    } else if (t == "/") {
      // 拿两个数做运算
      string a = st.top();
      st.pop();
      string b = st.top();
      st.pop();

      int tmp = std::stoi(a) / std::stoi(b);
      st.push(to_string(tmp));
    } else {
      st.push(t);
    }
  }

  cout << "result:" << st.top() << endl;
}

/*
给你一个整数数组
nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的
k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sliding-window-maximum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]
 

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sliding-window-maximum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
namespace leetcode239 {
class Queue {
public:
  void pop(int val) {
    if (!buffer.empty() && val == buffer.front()) {
      buffer.pop_front();
    }
  }

  void push(int val) {
    while (!buffer.empty() && val > buffer.back()) {
      cout << "val" << val << " back" << buffer.back() << endl;
      buffer.pop_back();
    }
    buffer.push_back(val);
  }

  int front() { return buffer.front(); }

private:
  deque<int> buffer;
};
} // namespace leetcode239

TEST(stack_queue, leetcode239) {
  vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
  int k = 3;

  using namespace leetcode239;
  Queue queue;
  vector<int> result;
  for (int i = 0; i < k; i++) {
    queue.push(nums[i]);
  }

  result.push_back(queue.front());
  for (int i = k; i < nums.size(); i++) {
    cout << "i-k:" << nums[i - k] << " k:" << nums[k] << endl;
    queue.pop(nums[i - k]);
    queue.push(nums[i]);
    result.push_back(queue.front());
  }

  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  cout << endl;
}

/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按
任意顺序 返回答案。

 

示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:

输入: nums = [1], k = 1
输出: [1]
 

提示：

1 <= nums.length <= 105
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/top-k-frequent-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class comLess {
public:
  bool operator()(const pair<int, int> &lh, const pair<int, int> &rh) {
    return lh.second > rh.second;
  }
};

TEST(stack_queue, leetcode347) {
  map<int, int> freqs;
  vector<int> nums{1, 1, 1, 2, 2, 3};
  int k = 2;

  priority_queue<pair<int, int>, vector<pair<int, int>>, comLess> pp;
  for (int i = 0; i < nums.size(); i++) {
    freqs[nums[i]]++;
  }
  for (auto it = freqs.begin(); it != freqs.end(); it++) {
    pp.push(*it);
    if (pp.size() > k) {
      pp.pop();
    }
  }

  while (!pp.empty()) {
    cout << " " << pp.top().first;
    pp.pop();
  }
  cout << endl;
  //
}

/*
给定 n 个非负整数表示每个宽度为 1
的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

 

示例 1：



输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接
6 个单位的雨水（蓝色部分表示雨水）。 示例 2：

输入：height = [4,2,0,3,2,5]
输出：9

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/trapping-rain-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(stack_queue, leetcode42) {
  // 使用双指针解题
  // vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  vector<int> height{4, 2, 0, 3, 2, 5};

  int sum = 0;
  for (int i = 0; i < height.size(); i++) {
    if (i == 0 || i == height.size() - 1) {
      continue;
    }

    int maxLeft = 0;
    int maxRight = 0;
    for (int l = i - 1; l >= 0; l--) {
        maxLeft = max(maxLeft, height[l]);
    }

    for (int r = i + 1; r < height.size(); r++) {
      maxRight = max(maxRight, height[r]);
    }

    int h = min(maxLeft, maxRight) - height[i];
    if (h > 0) {
      sum += h;
    }
  }

  cout << "sum " << sum << endl;
}