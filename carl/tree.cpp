#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

/*
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}

  TreeNode *Find(TreeNode *cur, int val) {
    if (cur == nullptr) {
      return nullptr;
    }

    TreeNode *node = cur;
    if (val < cur->val) {
      if (cur->left) {
        node = Find(cur->left, val);
      }
    } else {
      if (cur->right) {
        node = Find(cur->right, val);
      }
    }
    if (node && (node->left == nullptr || node->right == nullptr)) {
      return node;
    }
  }

  void Push(TreeNode *other) {
    if (other == nullptr) {
      return;
    }

    TreeNode *node = Find(this, other->val);
    if (other->val < node->val) {
      node->left = other;
    } else {
      node->right = other;
    }

    // 进行reblance操作
  }

  void Print() {
    queue<TreeNode *> layer;
    layer.push(this);
    while (!layer.empty()) {
      queue<TreeNode *> tmp;
      while (!layer.empty()) {
        TreeNode *cur = layer.front();
        layer.pop();
        tmp.push(cur);
        cout << " " << cur->val;
      }
      cout << endl;

      while (!tmp.empty()) {
        /* code */
        TreeNode *cur = tmp.front();
        tmp.pop();
        if (cur->left) {
          layer.push(cur->left);
        }

        if (cur->right) {
          layer.push(cur->right);
        }
      }
    }
  }

  void PreOrder() {
    PreOrder(this);
    cout << endl;
  }

  void PreOrder(TreeNode *root) {
    // 根左右
    if (root == nullptr) {
      return;
    }

    cout << root->val << " ";
    if (root->left) {
      PreOrder(root->left);
    }

    if (root->right) {
      PreOrder(root->right);
    }
  }

  void MidOrder() {
    MidOrder(this);
    cout << endl;
  }

  void MidOrder(TreeNode *root) {
    // 左根右
    if (root == nullptr) {
      return;
    }

    if (root->left) {
      MidOrder(root->left);
    }

    cout << root->val << " ";

    if (root->right) {
      MidOrder(root->right);
    }
  }

  void PostOrder() {
    PostOrder(this);
    cout << endl;
  }

  void PostOrder(TreeNode *root) {
    // 左右根
    if (root == nullptr) {
      return;
    }

    if (root->left) {
      PostOrder(root->left);
    }

    if (root->right) {
      PostOrder(root->right);
    }

    cout << root->val << " ";
  }

  void Reverse() { Reverse(this); }

  void Reverse(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    if (root->left) {
      Reverse(root->left);
    }

    if (root->right) {
      Reverse(root->right);
    }

    swap(root->left, root->right);
  }

  bool Symmetric() { return Symmetric(this); }

  bool Symmetric(TreeNode *root) {
    if ((root->left == nullptr && root->right == nullptr) ||
        (root->left->val == root->right->val)) {
      return true;
    } else {
      return false;
    }

    bool left = false;
    bool right = false;

    if (root->left) {
      left = Symmetric(root->left);
    }

    if (root->right) {
      right = Symmetric(root->right);
    }

    return left && right;
  }

  int MaxDepth() { MaxDepth(this); }

  int MaxDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }
    return max(MaxDepth(root->left), MaxDepth(root->right)) + 1;
  }

  int MinDepth() { MinDepth(this); }

  int MinDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }

    int left = MinDepth(root->left);
    int right = MinDepth(root->right);

    if (root->left == nullptr && root->right) {
      return left + 1;
    }

    if (root->left && root->right == nullptr) {
      return right + 1;
    }

    return min(left, right) + 1;
  }

  bool IsBalance() { return IsBalance(this); }

  bool IsBalance(TreeNode *root) {
    if (root == nullptr) {
      return true;
    }
    int left = 0;
    if (root->left) {
      left = MaxDepth(root->left);
    }

    int right = 0;
    if (root->right) {
      right = MaxDepth(root->right);
    }

    return abs(left - right) <= 1 && IsBalance(root->left) &&
           IsBalance(root->right);
  }

  void AllPaths(std::vector<vector<int>> &paths) {
    vector<int> tmp;

    AllPaths(this, tmp, paths);
  }

  void AllPaths(TreeNode *root, std::vector<int> &tmp,
                std::vector<vector<int>> &paths) {
    // 如果是叶子节点则进行输出
    tmp.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr) {
      // 如果这里对paths进行pop_back 则会出现pop不干净
      std::vector<int> tt = tmp;
      paths.push_back(tt);
    }

    if (root->left) {
      AllPaths(root->left, tmp, paths);
      // 还是需要在这pop
      tmp.pop_back();
    }

    if (root->right) {
      AllPaths(root->right, tmp, paths);
      tmp.pop_back();
    }
  }

  void LayerdPush(const vector<int> &tmp) {
    queue<TreeNode *> que;
    que.push(this);
    int idx = 0;
    while (!que.empty() && idx < tmp.size()) {
      TreeNode *top = que.front();
      if (top->left == nullptr) {
        TreeNode *tt = new TreeNode(tmp[idx++]);
        top->left = tt;
        que.push(tt);
      } else if (top->right == nullptr) {
        TreeNode *tt = new TreeNode(tmp[idx++]);
        top->right = tt;
        que.push(tt);
      } else {
        que.pop();
      }
    }
  }

  bool TargetPath(int target) {
    vector<int> paths;
    return TargetPath(this, paths, target);
  }

  bool TargetPath(TreeNode *root, vector<int> &paths, int target) {
    paths.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr) {
      int sum = 0;
      for (int i = 0; i < paths.size(); i++) {
        sum += paths[i];
      }

      if (sum == target) {
        return true;
      }
    }

    bool left = false;
    if (root->left) {
      left = TargetPath(root->left, paths, target);
      paths.pop_back();
    }

    bool right = false;
    if (root->right) {
      right = TargetPath(root->right, paths, target);
      paths.pop_back();
    }

    return left || right;
  }
};

/*
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
*/
TEST(tree, leetcode144) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();

  root->PreOrder();
}

/*
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
*/
TEST(tree, leetcode94) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();

  root->MidOrder();
}

/*
给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
*/
TEST(tree, leetcode145) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();

  root->PostOrder();
}

/*
给你一棵二叉树的根节点 root ，返回其节点值的 层序遍历 。
*/
TEST(tree, leetcode102) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();
}

/*
给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
*/
TEST(tree, leetcode226) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();

  root->Reverse();

  root->Print();
}

/*
给你一个二叉树的根节点 root ， 检查它是否轴对称。
*/
TEST(tree, leetcode101) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }
  ASSERT_FALSE(root->Symmetric());

  TreeNode *tt = new TreeNode(-1);
  ASSERT_TRUE(tt->Symmetric());
}

/*
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。
*/
TEST(tree, leetcode104) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }
  cout << root->MaxDepth() << endl;
}

/*
给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。

 

示例 1：


输入：root = [3,9,20,null,null,15,7]
输出：2
示例 2：

输入：root = [2,null,3,null,4,null,5,null,6]
输出：5
 

提示：

树中节点数的范围在 [0, 105] 内
-1000 <= Node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-depth-of-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode111) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }
  cout << root->MinDepth() << endl;
}

// TEST(cout, threadSafe) {
//   volatile int sum = 0;
//   std::function<void()> th1 = [&sum]() {
//     /* code */
//     for (int i = 0; i < 1000; i++) {
//       for (int x = 0; x < 1000; x++) {
//         sum += x;
//       }
//       cout << "thread1"
//            << "11111111111111"
//            << "         1111111111111111111111111111111111111111" << sum <<
//            endl;
//       ;
//     }
//   };

//   std::function<void()> th2 = [&sum]() {
//     /* code */
//     for (int i = 0; i < 1000; i++) {
//       string str = std::string("thread") + std::string("2") +
//       std::string("\n"); for (int x = 0; x < 1000; x++) {
//         sum += x;
//       }
//       cout << "thread"
//            << "222222222222222222222222222222"
//            << "           22222222222222222222222222222222222"
//            << "2" << sum << endl;
//       ;
//       ;
//     }
//   };

//   std::function<void()> th3 = [&sum]() {
//     /* code */
//     for (int i = 0; i < 1000; i++) {
//       string str = std::string("thread") + std::string("2") +
//       std::string("\n"); for (int x = 0; x < 1000; x++) {
//         sum += x;
//       }
//       cout << "thread"
//            << "3333333333333333"
//            << "           333333"
//            << "3" << sum << endl;;
//       ;
//     }
//   };

//   thread t(th1);
//   thread t2(th2);
//   thread t3(th3);
//   t.join();
//   t2.join();
//   t3.join();
// }

/*
给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
*/
TEST(tree, leetcode110) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }
  cout << root->IsBalance() << endl;
}

/*
给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。

叶子节点 是指没有子节点的节点。
*/
TEST(tree, leetcode257) {
  TreeNode *root = new TreeNode(-1);
  vector<int> nums{2, -3, 1, 3, 8, 5, 9};
  for (int i = 0; i < nums.size(); i++) {
    TreeNode *node = new TreeNode(nums[i]);
    root->Push(node);
  }

  root->Print();

  vector<vector<int>> paths;
  root->AllPaths(paths);
  for (int i = 0; i < paths.size(); i++) {
    for (int j = 0; j < paths[i].size(); j++) {
      cout << paths[i][j] << ",";
    }
    cout << endl;
  }
}

/*
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在
根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum
。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点。

 

示例 1：


输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。
示例 2：


输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为 3
(1 --> 3): 和为 4
不存在 sum = 5 的根节点到叶子节点的路径。
示例 3：

输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。
 

提示：

树中节点的数目在范围 [0, 5000] 内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/path-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode112) {
  TreeNode *root = new TreeNode(5);
  vector<int> arr = {4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
  root->LayerdPush(arr);
  root->Print();
  ASSERT_TRUE(root->TargetPath(22));
}