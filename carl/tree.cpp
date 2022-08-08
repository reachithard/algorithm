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

  void AllTargetPath(int target, vector<vector<int>> &paths) {
    vector<int> path;
    AllTargetPath(this, path, target, paths);
  }

  void AllTargetPath(TreeNode *root, vector<int> &path, int target,
                     vector<vector<int>> &paths) {
    if (root == nullptr) {
      return;
    }

    path.push_back(root->val);

    if (root->left == nullptr && root->right == nullptr) {
      int sum = 0;
      for (int i = 0; i < path.size(); i++) {
        // cout << path[i] << ",";
        sum += path[i];
      }
      // cout << "root->val" << root->val;
      cout << endl;

      if (target == sum) {
        paths.push_back(path);
      }
    }

    if (root->left) {
      AllTargetPath(root->left, path, target, paths);
      path.pop_back();
    }

    if (root->right) {
      AllTargetPath(root->right, path, target, paths);
      path.pop_back();
    }
  }
};

class Tree {
public:
  Tree() {}

  Tree(int val) { dummy = new TreeNode(val); }

  void InorderAndPostorder(vector<int> &inorder, vector<int> &postorder) {
    dummy = InorderAndPostorder(dummy, inorder, 0, inorder.size(), postorder, 0,
                                postorder.size());
  }

  int times = 0;
  // 中序遍历是左根右 后序遍历是左右根 后序遍历的最后一个节点是根结点
  // vector<int> inorder = {9, 3, 15, 20, 7};
  // vector<int> postorder = {9, 15, 7, 20, 3};
  TreeNode *InorderAndPostorder(TreeNode *root, vector<int> &inorder,
                                int inorderBegin, int inorderEnd,
                                vector<int> &postorder, int postorderBegin,
                                int postorderEnd) {
    if (postorderBegin == postorderEnd) {
      return nullptr;
    }
    root = new TreeNode(postorder[postorderEnd - 1]);
    // cout << "inodebegin:" << inorderBegin << " inorderEnd:" << inorderEnd <<
    // " postbegin:" << postorderBegin << " postEnd:" << postorderEnd << endl;
    if (postorderEnd - postorderBegin == 1) {
      return root;
    }

    int idx = inorderBegin;
    for (; idx < inorderEnd; idx++) {
      if (inorder[idx] == postorder[postorderEnd - 1]) {
        break;
      }
    }

    // idx找到
    int leftInorderBegin = inorderBegin;
    int leftInorderEnd = idx;

    int rightInorderBegin = idx + 1;
    int rightInorderEnd = inorderEnd - 1;

    int leftPostorderBegin = postorderBegin;
    int leftPostorderEnd = postorderBegin + leftInorderEnd - leftInorderBegin;

    int rightPostorderBegin =
        postorderBegin + leftInorderEnd - leftInorderBegin;
    int rightPostorderEnd = postorderEnd - 1;

    // cout << "leftInorderBegin:" << leftInorderBegin
    //      << " leftInorderEnd:" << leftInorderEnd
    //      << " rightInorderBegin:" << rightInorderBegin
    //      << " rightInorderEnd:" << rightInorderEnd
    //      << " leftPostorderBegin:" << leftPostorderBegin
    //      << " leftPostorderEnd:" << leftPostorderEnd
    //      << " rightPostorderBegin:" << rightPostorderBegin
    //      << " rightPostorderEnd:" << rightPostorderEnd << endl;

    //  times++;
    //  if (times > 20) {
    //   return nullptr;
    //  }

    root->left = InorderAndPostorder(root->left, inorder, leftInorderBegin,
                                     leftInorderEnd, postorder,
                                     leftPostorderBegin, leftPostorderEnd);
    root->right = InorderAndPostorder(root->right, inorder, rightInorderBegin,
                                      rightInorderEnd, postorder,
                                      rightPostorderBegin, rightPostorderEnd);

    return root;
  }

  void InorderAndPostorder(TreeNode **root, vector<int> &inorder,
                           vector<int> &postorder, int &index) {
    cout << "index" << index << endl;
    if (index < 0 || inorder.empty()) {
      return;
    }
    *root = new TreeNode(postorder[index--]); // 后序遍历最后一个是根节点

    cout << "begin";
    for (int t = 0; t < inorder.size(); t++) {
      cout << inorder[t] << " ";
    }
    cout << endl;

    // 然后从中序遍历找左节点
    int idx = 0;
    for (; idx < inorder.size(); idx++) {
      if (inorder[idx] == postorder[index + 1]) {
        // 说明找到
        break;
      }
    }

    cout << "idx:" << idx << "ret:" << postorder[index + 1] << endl;
    inorder.erase(inorder.begin() + idx);
    if (idx >= 1 && idx != inorder.size()) {
      TreeNode *tmp = new TreeNode(inorder[idx - 1]);
      (*root)->left = tmp;
      inorder.erase(inorder.begin() + idx - 1);
    }

    InorderAndPostorder(&((*root)->right), inorder, postorder, index);
  }

  void InorderAndPreorder(vector<int> &inorder, vector<int> &preorder) {
    dummy = InorderAndPreorder(dummy, inorder, 0, inorder.size(), preorder, 0,
                               preorder.size());
  }

  // 根左右 和 左根右
  /*
  vector<int> preorder{3, 9, 20, 15, 7};
  vector<int> inorder{9, 3, 15, 20, 7};
  */
  TreeNode *InorderAndPreorder(TreeNode *root, vector<int> &inorder,
                               int inorderBegin, int inorderEnd,
                               vector<int> &preorder, int preorderBegin,
                               int preorderEnd) {
    if (preorderBegin == preorderEnd) {
      return nullptr;
    }
    root = new TreeNode(preorder[preorderBegin]);

    if (preorderEnd - preorderBegin == 1) {
      return root;
    }

    int idx = inorderBegin;
    for (; idx < inorder.size(); idx++) {
      if (preorder[preorderBegin] == inorder[idx]) {
        break;
      }
    }

    int leftInorderBegin = inorderBegin;
    int leftInorderEnd = idx;

    int rightInorderBegin = idx + 1;
    int rightInorderEnd = inorderEnd;

    int leftPreorderBegin = preorderBegin + 1;
    int leftPreorderEnd =
        preorderBegin + (leftInorderEnd - leftInorderBegin) + 1;

    int rightPreorderBegin =
        preorderBegin + (leftInorderEnd - leftInorderBegin) + 1;
    int rightPreorderEnd = preorderEnd;

    root->left = InorderAndPreorder(root->left, inorder, leftInorderBegin,
                                    leftInorderEnd, preorder, leftPreorderBegin,
                                    leftPreorderEnd);
    root->right = InorderAndPreorder(root->right, inorder, rightInorderBegin,
                                     rightInorderEnd, preorder,
                                     rightPreorderBegin, rightPreorderEnd);
    return root;
  }

  void Print() {
    if (dummy) {
      dummy->Print();
    }
  }

  void MergeTwoTree(TreeNode *tree1, TreeNode *tree2) {
    dummy = MergeTwoTree(dummy, tree1, tree2);
  }

  TreeNode *MergeTwoTree(TreeNode *root, TreeNode *tree1, TreeNode *tree2) {
    if (tree1 == nullptr && tree2 == nullptr) {
      return nullptr;
    } else if (tree1 != nullptr && tree2 != nullptr) {
      root = new TreeNode(tree1->val + tree2->val);
      root->left = MergeTwoTree(root->left, tree1->left, tree2->left);
      root->right = MergeTwoTree(root->right, tree1->right, tree2->right);
    } else if (tree1) {
      root = new TreeNode(tree1->val);
      root->left = MergeTwoTree(root->left, tree1->left, nullptr);
      root->right = MergeTwoTree(root->right, tree1->right, nullptr);
    } else if (tree2) {
      root = new TreeNode(tree2->val);
      root->left = MergeTwoTree(root->left, nullptr, tree2->left);
      root->right = MergeTwoTree(root->right, nullptr, tree2->right);
    }

    return root;
  }

  TreeNode *GetDummy() { return dummy; }

  TreeNode *FindBstNode(int target) { return FindBstNode(dummy, target); }

  TreeNode *FindBstNode(TreeNode *root, int target) {
    if (root == nullptr) {
      return nullptr;
    }

    if (root->val == target) {
      return root;
    } else if (root->val > target) {
      return FindBstNode(root->left, target);
    } else {
      return FindBstNode(root->right, target);
    }
  }

  void LayerdPush(const vector<int> &tmp) {
    dummy = new TreeNode(tmp.front());
    vector<int> tt(tmp.begin() + 1, tmp.end());
    dummy->LayerdPush(tt);
  }

  bool IsBstTree() {
    TreeNode *prev = nullptr;
    return IsBstTree(dummy, &prev);
  }

  bool IsBstTree(TreeNode *root, TreeNode **prev) {
    if (root == nullptr) {
      return true;
    }

    bool left = IsBstTree(root->left, prev);
    if (*prev != nullptr && (*prev)->val >= root->val) {
      return false;
    }
    *prev = root;
    bool right = IsBstTree(root->right, prev);
    return left && right;
  }

  int MinAbsBstTree() {
    int min = INT32_MAX;
    TreeNode *prev = nullptr;
    MinAbsBstTree(dummy, &prev, min);
    return min;
  }

  void MinAbsBstTree(TreeNode *root, TreeNode **prev, int &min) {
    if (root == nullptr) {
      return;
    }

    MinAbsBstTree(root->left, prev, min);
    if (*prev != nullptr) {
      min = std::min(abs((*prev)->val - root->val), min);
    }
    *prev = root;
    MinAbsBstTree(root->right, prev, min);
  }

  vector<int> GetBstTreeCommanNum() {
    int cnt = 0;
    vector<int> common;
    TreeNode *prev = nullptr;
    int maxCnt = 0;

    GetBstTreeCommanNum(dummy, &prev, common, cnt, maxCnt);
    return common;
  }

  void GetBstTreeCommanNum(TreeNode *root, TreeNode **prev, vector<int> &common,
                           int &cnt, int &maxCnt) {
    if (root == nullptr) {
      return;
    }

    GetBstTreeCommanNum(root->left, prev, common, cnt, maxCnt);
    if (*prev == nullptr) {
      cnt = 1;
    } else if ((*prev)->val == root->val) {
      cnt++;
    } else {
      cnt = 1;
    }

    *prev = root;

    if (cnt == maxCnt) {
      common.push_back(root->val);
    } else if (cnt > maxCnt) {
      common.clear();
      maxCnt = cnt;
      common.push_back(root->val);
    }

    GetBstTreeCommanNum(root->right, prev, common, cnt, maxCnt);
  }

  TreeNode *GetCommanParent(TreeNode *p, TreeNode *q) {
    vector<TreeNode *> pparent;
    vector<TreeNode *> paths;

    GetCommanParent(dummy, paths, pparent, &p);

    vector<TreeNode *> qparent;

    GetCommanParent(dummy, paths, qparent, &p);

    reverse(pparent.begin(), pparent.end());
    reverse(qparent.begin(), qparent.end());

    // 然后找公共的
    size_t offset = abs((int)pparent.size() - (int)qparent.size() - 1);
    int i = 0;
    TreeNode *parent = nullptr;
    if (pparent.size() > qparent.size()) {
      for (; i < qparent.size(); i++) {
        if (pparent[i + offset] == qparent[i]) {
          parent = qparent[i];
          break;
        }
      }
    } else {
      for (; i < qparent.size(); i++) {
        if (pparent[i] == qparent[i + offset]) {
          parent = pparent[i];
          break;
        }
      }
    }
    return parent;
  }

  void GetCommanParent(TreeNode *root, vector<TreeNode *> &paths,
                       vector<TreeNode *> &parent, TreeNode **target) {
    if (root == nullptr) {
      return;
    }

    paths.push_back(root);
    if (*target == root) {
      parent = paths;
    }

    if (root->left) {
      GetCommanParent(root->left, paths, parent, target);
      paths.pop_back();
    }

    if (root->right) {
      GetCommanParent(root->right, paths, parent, target);
      paths.pop_back();
    }
  }

  TreeNode *GetBstCommanNode(TreeNode *p, TreeNode *q) {
    return GetBstCommanNode(dummy, p, q);
  }
  TreeNode *GetBstCommanNode(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == nullptr) {
      return root;
    }
    if (root->val < p->val && root->val < q->val) {
      return GetBstCommanNode(root->right, p, q);
    } else if (root->val > p->val && root->val > q->val) {
      return GetBstCommanNode(root->left, p, q);
    } else {
      return root;
    }
  }

private:
  TreeNode *dummy;
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

/*
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点
路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/path-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
TEST(tree, leetcode113) {
  TreeNode *root = new TreeNode(5);
  vector<int> arr = {4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, 5, 1};
  root->LayerdPush(arr);
  root->Print();
  vector<vector<int>> paths;
  int target = 22;
  root->AllTargetPath(target, paths);
  for (int i = 0; i < paths.size(); i++) {
    cout << "[";
    for (int j = 0; j < paths[i].size(); j++) {
      cout << paths[i][j] << ",";
    }
    cout << "]" << endl;
  }
}

/*
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历，
postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

 

示例 1:

输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]
示例 2:

输入：inorder = [-1], postorder = [-1]
输出：[-1]
 

提示:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder 和 postorder 都由 不同 的值组成
postorder 中每一个值都在 inorder 中
inorder 保证是树的中序遍历
postorder 保证是树的后序遍历

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode106) {
  // 中序遍历是左根右 后序遍历是左右根 后序遍历的最后一个节点是根结点
  vector<int> inorder = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};

  Tree *tree = new Tree();
  tree->InorderAndPostorder(inorder, postorder);
  tree->Print();

  vector<int> inorder2 = {5, 4, 1, 2, 6};
  vector<int> postorder2 = {1, 2, 4, 6, 5};

  Tree *tree2 = new Tree();
  tree2->InorderAndPostorder(inorder2, postorder2);
  tree2->Print();
}

/*
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历，
inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

 

示例 1:


输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
示例 2:

输入: preorder = [-1], inorder = [-1]
输出: [-1]
 

提示:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder 和 inorder 均 无重复 元素
inorder 均出现在 preorder
preorder 保证 为二叉树的前序遍历序列
inorder 保证 为二叉树的中序遍历序列

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode105) {
  // TODO
  vector<int> preorder{3, 9, 20, 15, 7};
  vector<int> inorder{9, 3, 15, 20, 7};

  Tree *tree = new Tree();
  tree->InorderAndPreorder(inorder, preorder);
  tree->Print();
}

/*
给你两棵二叉树： root1 和 root2 。

想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为
null 的节点将直接作为新二叉树的节点。

返回合并后的二叉树。

注意: 合并过程必须从两个树的根节点开始。

 

示例 1：


输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
输出：[3,4,5,5,4,null,7]
示例 2：

输入：root1 = [1], root2 = [1,2]
输出：[2,2]
 

提示：

两棵树中的节点数目在范围 [0, 2000] 内
-104 <= Node.val <= 104

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/merge-two-binary-trees
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode617) {
  vector<int> inorder = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};

  Tree *tree = new Tree();
  tree->InorderAndPostorder(inorder, postorder);
  tree->Print();

  vector<int> inorder2 = {5, 4, 1, 2, 6};
  vector<int> postorder2 = {1, 2, 4, 6, 5};

  Tree *tree2 = new Tree();
  tree2->InorderAndPostorder(inorder2, postorder2);
  tree2->Print();

  cout << "other" << endl;

  Tree *merge = new Tree();
  merge->MergeTwoTree(tree->GetDummy(), tree2->GetDummy());
  merge->Print();
}

/*
给定二叉搜索树（BST）的根节点 root 和一个整数值 val。

你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。
如果节点不存在，则返回 null 。

 

示例 1:



输入：root = [4,2,7,1,3], val = 2
输出：[2,1,3]
示例 2:


输入：root = [4,2,7,1,3], val = 5
输出：[]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/search-in-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode700) {
  Tree *root = new Tree();
  vector<int> arr = {4, 2, 7, 1, 3};
  root->LayerdPush(arr);
  root->Print();

  TreeNode *find = root->FindBstNode(2);
  find->Print();
}

/*
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
 

示例 1：


输入：root = [2,1,3]
输出：true
示例 2：


输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/validate-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode98) {
  Tree *root = new Tree();
  vector<int> arr = {2, 1, 3};
  root->LayerdPush(arr);
  root->Print();
  ASSERT_TRUE(root->IsBstTree());

  Tree *root2 = new Tree();
  vector<int> arr2 = {5, 1, 4, -1, -1, 3, 6};
  root2->LayerdPush(arr2);
  root2->Print();
  ASSERT_FALSE(root2->IsBstTree());
}

/*
给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。

差值是一个正数，其数值等于两值之差的绝对值。

 

示例 1：


输入：root = [4,2,6,1,3]
输出：1
示例 2：


输入：root = [1,0,48,null,null,12,49]
输出：1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-absolute-difference-in-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode530) {
  Tree *root = new Tree();
  vector<int> arr = {4, 2, 6, 1, 3};
  root->LayerdPush(arr);
  root->Print();
  cout << root->MinAbsBstTree() << endl;
}

/*
给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有
众数（即，出现频率最高的元素）。

如果树中有不止一个众数，可以按 任意顺序 返回。

假定 BST 满足如下定义：

结点左子树中所含节点的值 小于等于 当前节点的值
结点右子树中所含节点的值 大于等于 当前节点的值
左子树和右子树都是二叉搜索树
 

示例 1：


输入：root = [1,null,2,2]
输出：[2]
示例 2：

输入：root = [0]
输出：[0]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/find-mode-in-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode501) {
  Tree *root = new Tree();
  vector<int> arr = {1, -1, 2, -1, -1, 2, 2};
  root->LayerdPush(arr);
  root->Print();
  vector<int> common = root->GetBstTreeCommanNum();
  for (int i = 0; i < common.size(); i++) {
    cout << common[i] << endl;
  }
}

/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点
p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x
的深度尽可能大（一个节点也可以是它自己的祖先）。”

 

示例 1：


输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
示例 2：


输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5
。因为根据定义最近公共祖先节点可以为节点本身。 示例 3：

输入：root = [1,2], p = 1, q = 2
输出：1
 

提示：

树中节点数目在范围 [2, 105] 内。
-109 <= Node.val <= 109
所有 Node.val 互不相同 。
p != q
p 和 q 均存在于给定的二叉树中。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode236) {
  // TODO 目前算法使用的是转换为相交链表
}

/*
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点
p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x
的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]



 

示例 1:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6
解释: 节点 2 和节点 8 的最近公共祖先是 6。
示例 2:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2,
因为根据定义最近公共祖先节点可以为节点本身。  

说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
TEST(tree, leetcode235) {
  // TODO 未测试 即处于[p, q]时则为待寻找
}