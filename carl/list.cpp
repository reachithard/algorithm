#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int val) : val(val), next(nullptr) {}
  void Push(ListNode *other) {
    other->next = next;
    next = other;
  }

  void print() {
    ListNode *tt = next;
    while (tt) {
      cout << tt->val << " ";
      tt = tt->next;
    }
    cout << endl;
  }
};

/*
给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val ==
val 的节点，并返回 新的头节点 。
*/
TEST(list, leetcode203) {
  ListNode *head = new ListNode(1000);
  for (int i = 0; i < 30; i++) {
    ListNode *tmp = new ListNode(i);
    head->Push(tmp);
  }

  ListNode *tt = head;
  while (tt) {
    cout << tt->val << endl;
    tt = tt->next;
  }

  ListNode *cur = head;
  int val = 10;
  ListNode *dummy = new ListNode(0);
  dummy->next = head;
  ListNode *prev = dummy;
  while (cur != nullptr) {
    if (cur->val == val) {
      prev->next = cur->next;
      delete cur;
      cur = prev->next;
      continue;
    }
    prev = cur;
    cur = cur->next;
  }
  head = dummy->next;
  delete dummy;

  cout << "output" << endl;
  tt = head;
  while (tt) {
    cout << tt->val << endl;
    tt = tt->next;
  }
  // return head;
}

/*
设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是
0-index 的。

在链表类中实现这些功能：

get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val 
的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index
大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/design-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
namespace leetcode707 {
class LList {
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int val) : val(val), next(nullptr) {}
    void Push(ListNode *other) {
      other->next = next;
      next = other;
    }
  };

public:
  LList() {
    dummyNode = new ListNode(0);
    tail = dummyNode;
    size = 0;
  }

  ~LList() {
    if (dummyNode) {
      delete dummyNode;
      dummyNode = nullptr;
    }
  }

  int get(int idx) {
    if (idx > size || size == 0 || idx < 0) {
      return -1;
    }

    ListNode *tmp = dummyNode->next;
    while (tmp && idx--) {
      tmp = tmp->next;
    }
    return tmp->val;
  }

  void addAtHead(int val) {
    ListNode *tmp = new ListNode(val);
    if (size == 0) { // 这里需要改变tail值
      tail = tmp;
    }
    tmp->next = dummyNode->next;
    dummyNode->next = tmp;
    size++;
  }

  void addAtTail(int val) {
    ListNode *tmp = new ListNode(val);
    tail->next = tmp;
    tail = tmp;

    size++;
  }

  void addAtIndex(int idx, int val) {
    if (size == idx) {
      addAtTail(val);
    }

    if (idx < 0) {
      addAtHead(val);
    }

    if (idx > size) {
      return;
    }

    ListNode *prev = dummyNode;
    ListNode *cur = dummyNode->next;
    ListNode *node = new ListNode(val);

    while (cur && idx--) {
      prev = cur;
      cur = cur->next;
    }

    node->next = cur;
    prev->next = node;
    size++;
  }

  void deleteAtIndex(int idx) {
    if (size == 0 || idx < 0 || idx > size) {
      return;
    }

    ListNode *cur = dummyNode->next;
    ListNode *prev = dummyNode;
    while (cur && idx--) {
      prev = cur;
      cur = cur->next;
    }

    prev->next = cur->next;
    delete cur;
    size--;
  }

  void print() {
    ListNode *cur = dummyNode->next;
    while (cur) {
      cout << cur->val << " ";
      cur = cur->next;
    }
    cout << endl;
  }

private:
  ListNode *dummyNode = nullptr;
  ListNode *tail = nullptr;
  size_t size = 0;
};

} // namespace leetcode707
TEST(list, leetcode707) {
  using namespace leetcode707;
  unique_ptr<LList> li = make_unique<LList>();

  ASSERT_EQ(li->get(-1), -1);

  li->addAtIndex(100, 0);

  for (int i = 0; i < 5; i++) {
    li->addAtHead(i);
  }

  for (int i = 0; i < 5; i++) {
    li->addAtTail(i);
  }

  li->print();
  ASSERT_EQ(li->get(7), 2);

  li->deleteAtIndex(100);

  li->deleteAtIndex(3);
  li->print();

  for (int i = 0; i < 5; i++) {
    li->addAtHead(i);
  }

  for (int i = 0; i < 5; i++) {
    li->addAtTail(i);
  }

  li->print();
}

/*
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
*/
TEST(list, leetcode206) {
  ListNode *head = new ListNode(1000);
  for (int i = 0; i < 30; i++) {
    ListNode *tmp = new ListNode(i);
    head->Push(tmp);
  }

  head->print();

  ListNode *dummy = new ListNode(0);
  dummy->next = nullptr;
  ListNode *cur = head;
  while (cur) {
    /* code */
    ListNode *tmp = cur->next;
    cur->next = dummy->next;
    dummy->next = cur;

    cur = tmp;
  }
  dummy->print();
}