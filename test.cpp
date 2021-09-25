#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>

#include "pkg/dreamcompany/section.h"
#include "pkg/dreamcompany/section_node.h"
using namespace ::std;
using namespace ::J;
using namespace ::J::basic;

struct Testmachine {
  string head;
  int num;
  int success;
  int part;
} testmachine;
int parts, success_parts;
ofstream fout;

//  @brief  To test our section
//  @param  __judgement  判断语句，如果正确，则打印1，如果错误，则打印0
//  @param  __prints  接下来打印的注释内容
template <typename... Types>
void test(bool __judgement, const Types&... __prints);

// @brief Divide test to parts.
void testpart(string testpart);

int main() {
  fout.open("testLog.txt");
  cout << "Start test section vessel" << endl;
  cout << "-------------------------\n"
       << endl;
  fout << "Start test section vessel" << endl;
  fout << "-------------------------\n"
       << endl;

  testmachine.head = "J.";
  testmachine.num = 0;
  testmachine.part = 0;
  parts = 0;
  success_parts = 0;

  testpart("Checking _Section_leaf_node_base");
  {
    _Section_leaf_node_base section_leaf_node_base;
    auto& lb(section_leaf_node_base);
    test(true, "New _Section_leaf_node_base section_leaf_node_base = _Section_leaf_node_base()");

    test(section_leaf_node_base._next == nullptr && section_leaf_node_base._prev == nullptr, "Verifying default constructor. Checkout whether section_leaf_node_base._next is nullptr: ", section_leaf_node_base._next, " ,expected nullptr;", " Checkout whether section_leaf_node_base._prev is nullptr: ", section_leaf_node_base._prev, " ,expected nullptr;");

    _Section_leaf_node_base section_leaf_node_base2(&lb, &lb);
    auto& lb2(section_leaf_node_base2);
    test(true, "Construct Val by pointers to _Section_leaf_node_base: `_Section_leaf_node_base section_leaf_node_base2(&section_leaf_node_base, &section_leaf_node_base);`");

    test(lb2._next == &lb && lb2._prev == &lb, "Verifying constructor. section_leaf_node_base2._prev: ", lb2._prev, ", expected ", &lb, ". ._next: ", lb2._next, ", expected ", &lb);
  }
  testpart("Checking _Section_tree_node_base");
  {
    _Section_tree_node_base section_tree_node_base;
    auto& tb(section_tree_node_base);
    test(true, "New _Section_tree_node_base section_tree_node_base = _Section_tree_node_base()");

    test(tb._left == nullptr && nullptr == tb._right && nullptr == tb._parent, "Verifying default constructor. section_tree_node_base._left: ", tb._left, ", expected nullptr. section_tree_node_base._right:", tb._right, ", expected nullptr. section_tree_node_base._parent: ", tb._parent, ", expected nullptr.");

    _Section_tree_node_base section_tree_node_base2(&tb, &tb, &tb);
    auto& tb2(section_tree_node_base2);
    test(true, "Construct section_tree_node_base2 by pointers to ._Section_tree_node_base: `_Section_tree_node_base section_tree_node_base2(&tb, &tb, &tb);`");

    test(tb2._parent == &tb && tb2._left == &tb && tb2._right == &tb, "Verifying constructor. section_node_base2._parent: ", tb2._parent, ", expected ", &tb, ". ._left: ", tb2._left, ", expected ", &tb, ". ._right: ", tb2._right, ", expected: ", &tb);
  }
  testpart("Checking _Section_node_header");
  {
    _Section_node_header section_node_header;
    auto& h = section_node_header;
    test(h._parent == nullptr && h._right == &h && h._left == &h, "New _Section_node_header, show its ._parent: ", h._parent, ", ._right: ", h._right, ", ._left: ", h._left);

    test(h._node_count == 0 && h._size == 0, "Verify section_node_header's ._size: ", h._size, ", .node_count: ", h._node_count, ", both expected 0");

    _Section_node_header section_node_header2(std::move(section_node_header));
    auto& h2 = section_node_header2;
    test(true, "New _Section_node_header section_node_header2 constructed by section_node_header.");

    test(h2._left == &h2 && h2._right == &h2, "Checkout whether section_node_header2's ._left: ", h2._left, ", ._right: ", h2._right, ", this: ", &h2, ", expected equal.");

    // const _Section_node_header& section_node_header3 = _Section_node_header();
    // _Section_node_header section_node_header4(std::move(section_node_header3));
    test(true, "New _Section_node_header section_node_header4 cannot constructed by const section_node_header&.");

    _Section_node_header section_node_header5;
    auto& h5(section_node_header5);
    h5._right = h5._left = &h;
    h._right = h._left = &h5;
    test(true, "New _Section_node_header section_node_header5 connected section_node_header forming a circle.");

    _Section_node_header section_node_header6(move(h5));
    test(true, "New _Section_node_header section_node_header6 constructed by section_node_header5.");

    auto& h6(section_node_header6);
    test(h6._right == &h && h6._left == &h && h._right == &h6 && h._left == &h6, "Check whether section_node_header and section_node_header6 forms a circle, section_node_header's this: ", &h, ", ._left: ", h._left, ", ._right: ", h._right, ", section_node_header6's this: ", &h6, ", ._left: ", h6._left, ", ._right: ", h6._right);

    test(&h5 == h5._right && &h5 == h5._left, "Check whether section_node_header5 is reconstructed by default. section_node_header5' this: ", &h5, ", ._left: ", h5._left, ", ._right: ", h5._right);
  }
  testpart("Checking _Section_leaf_node:");
  {
    _Section_leaf_node<int, int> leaf_node;
    auto& ln(leaf_node);
    test(true, "Testing _Section_leaf_node, new _Section_leaf_node.");

    test(leaf_node._parent == nullptr && nullptr == leaf_node._left, nullptr == ln._right, "Test whether successfully default construct inherit from _Section_tree_node_base. leaf_node._parent: ", ln._parent, ", expected nullptr. leaf_node._left: ", ln._left, ", expected nullptr. .right: ", ln._right, ", expected nullptr.");

    test(nullptr == ln._prev && nullptr == leaf_node._next, "Test whether successfully default construct inherit from _Section_leaf_node_base. leaf_node._prev: ", ln._prev, ", expected nullptr. leaf_node._next: ", ln._next, ", expected nullptr.");

    auto& pr(leaf_node._pair);
    pr.first = 100;
    pr.second = 101;
    test(ln._pair.first == 100 && ln._pair.second == 101, "Test whether ._pair member works.");

    auto pr2(ln._valptr());
    test(pr2->first == 100 && 101 == pr2->second, "Construct pr2 by leaf_node._valptr(), expected *pair<int, int> type. pr2->first = ", pr2->first, ", pr2->second = ", pr2->second, ", expected (100, 101).");

    pr2->first = 200, pr2->second = 201;
    test(200 == pr2->first && 201 == pr2->second, "Test whether pr2 isn't const, modify it and now, pr2->first = ", pr2->first, ", pr2->second = ", pr2->second, ", expected (200, 201).");

    auto pr3(static_cast<const _Section_leaf_node<int, int> >(leaf_node)._valptr());
    test(pr3->first == 200 && 201 == pr3->second, "Construct pr3 by static_cast<const ...>(leaf_node)._valptr(), expected pr3 as const pair<int, int>. pr3->first = ", pr3->first, ", pr3->second = ", pr3->second, ", expected (200, 201).");

    // pr3->first = 300;
    test(true, "pr3 is const, verifying.");
  }
  testpart("Checking _Section_tree_node");
  {
    _Section_tree_node<int, int> section_tree_node;
    auto& tn(section_tree_node);
    test(true, "Testing default constructor: `_Section_tree_node<int, int> section_tree_node;`");

    test(0 == tn._right_key, "Testing section_tree_node's_right: ", tn._right, ", expected 0");

    test(false == tn._has_mid, "Testing section_tree_node's ._has_mid: ", tn._has_mid, ", expected false.");

    test(false == tn._Is_leaf, "Testing section_tree_node's ._Is_leaf: ", tn._Is_leaf, ", expected false");

    test(0 == tn._sum, "Testing section_tree_node's _sum: ", tn._sum, ", expected 0.");

    test(nullptr == tn._left && nullptr == tn._right && nullptr == tn._parent, "Testing section_tree_node successfully inherit from _Section_tree_node_base, show its _left: ", tn._left, ", expected nullptr. ._right: ", tn._right, ", expected nullptr. ._parent: ", tn._parent, ", expected nullptr.");
  }
  testpart("Checking section base");
  {
    section<int, int> sec;
    test(true, "New section<int, pair<int, int> > sec");

    auto& h(sec._M_header);
    test(nullptr == h._parent && &h == h._left && &h == h._right, "Checking sec's header.");

    sec.insert(1, 2);
    test(true, "Insert key and value, expected no error");

    sec.traverse();

    sec.insert(0, 3);
    test(sec.size() == 2, "Insert another, checking whether its size is right for 2");

    sec.traverse();

    _Section_leaf_node<int, int> l1(1, 20);
    _Section_leaf_node<int, int> l2(2, 30);

    (&l1)->swap(&l2);
    test(true, "Add new node l1 with value", l1.val(), ", and l2 with value", l2.val(), ". Then swap them.");
    test(l1.val() == 30 && l2.val() == 20, "Test swap, l1's value is ", l1.val(), ", expected 30. l2's value is ", l2.val(), ", expected 20");

    section<int, int> sec2;

    sec2.insert(0, 0);
    sec2.insert(1, 1);
    sec2.insert(2, 2);

    sec2.traverse();

    test(sec2.size() == 3, "insert 3, its size is ", sec2.size(), ", expected 3.");

    sec2.insert(3, 3);
    sec2.traverse();

    test(sec2.size() == 4, "insert 4, its size is ", sec2.size(), "expected 4.");

    test(sec2.get(0) == 0, "Insert (0, 0), then get value of key 0 is ", sec2.get(0), ", expected 0");
  }
  testpart("Checking section insert");
  {
    section<int, int> sec3;
    test(true, "Construct new section<int, int> sec3, we will insert 5 nodes( (0, 0), (4, 400), (1, 100), (2, 200), (10, 1000) ), and check that we can get values of keys by every insert step.");

    sec3.insert(0, 0);
    test(true, "sec3 insert (0, 0).");

    test(sec3.get(0) == 0, "sec3.get(0) = ", sec3.get(0), ", expected 0");

    sec3.insert(4, 400);
    test(true, "sec3 insert (4, 400).");

    test(sec3.get(4) == 400, "sec3.get(4) = ", sec3.get(4), ", expected 400");
    test(sec3.get(0) == 0, "sec3.get(0) = ", sec3.get(0), ", expected 0");

    sec3.insert(1, 100);
    test(true, "sec3 insert (1, 100).");

    test(sec3.get(0) == 0, "sec3.get(0) = ", sec3.get(0), ", expected 0");
    test(sec3.get(1) == 100, "sec3.get(1) = ", sec3.get(1), ", expected 100");
    test(sec3.get(4) == 400, "sec3.get(4) = ", sec3.get(4), ", expected 400");

    sec3.insert(2, 200);
    test(true, "sec3 insert (2, 200).");

    test(sec3.get(0) == 0, "sec3.get(0) = ", sec3.get(0), ", expected 0");
    test(sec3.get(1) == 100, "sec3.get(1) = ", sec3.get(1), ", expected 100");
    test(sec3.get(2) == 200, "sec3.get(2) = ", sec3.get(2), ", expected 200");
    test(sec3.get(4) == 400, "sec3.get(4) = ", sec3.get(4), ", expected 400");

    sec3.insert(10, 1000);
    test(true, "sec3 insert (10, 1000).");

    test(sec3.get(0) == 0, "sec3.get(0) = ", sec3.get(0), ", expected 0");
    test(sec3.get(1) == 100, "sec3.get(1) = ", sec3.get(1), ", expected 100");
    test(sec3.get(2) == 200, "sec3.get(2) = ", sec3.get(2), ", expected 200");
    test(sec3.get(4) == 400, "sec3.get(4) = ", sec3.get(4), ", expected 400");
    test(sec3.get(10) == 1000, "sec3.get(10) = ", sec3.get(10), ", expected 1000");

    section<int, int> sec4;
    test(true, "Construct sec4. Then insert 50 nodes, and check their values.");
    for (int i(10); i < 20; i++) sec4.insert(i, i + 50);
    for (int i(30); i < 40; i++) sec4.insert(i, i + 50);
    for (int i(0); i < 10; i++) sec4.insert(i, i + 50);
    for (int i(40); i < 50; i++) sec4.insert(i, i + 50);
    for (int i(20); i < 30; i++) sec4.insert(i, i + 50);

    for (int i(0); i < 50; i++) test(sec4.get(i) == i + 50, "check key is ", i, ", with value of ", sec4.get(i), ", expected ", i + 50);

    section<int, int> sec5;
    test(true, "Construct section sec5. Then insert 100 nodes with (0, 0), (1, 1), (2, 2), ..., (11, 11).");
    for (int i(0); i < 4; i++) {
      sec5.insert(i, i);
      sec5.traverse();
    }
    for (int i(8); i < 12; i++) {
      sec5.insert(i, i);
      sec5.traverse();
    }
    for (int i(4); i < 8; i++) {
      sec5.insert(i, i);
      sec5.traverse();
    }
    for (int i(0); i < 12; i++) {
      test(sec5.get(i) == i, "sec5.get(", i, ") = ", sec5.get(i));
    }

    section<int, int> sec6;
    test(true, "Construct section sec6. Then insert 100 nodes with (0, 0), (1, 1), (2, 2), ..., (99, 99).");
    for (int i(0); i < 100; i++) sec6.insert(i * 97 % 100, i * 97 % 100);

    for (int i(0); i < 100; i++) test(sec6.get(i) == i, "sec6.get(", i, ") = ", sec6.get(i));
    sec6.traverse();

    const int la{15};
    for (int i(la + 1); i < 100; i++)
      test(sec6.query(la, i) == (i - la) * (i + la - 1) / 2, "Query sum from ", la, " to ", i, ", the result is ", sec6.query(la, i), ", expected result ", (i - la) * (i + la - 1) / 2);

    const int ra{125};
    for (int i(0); i < 100; i++)
      test(sec6.query(i, ra) == (100 - i) * (i + 99) / 2, "Query sum from ", i, " to ", ra, "(The max key in tree is 99), get sum of ", sec6.query(i, ra), ", expected ", (100 - i) * (i + 99) / 2);

    const int lla{-10};
    for (int i(0); i < 100; i++) 
      test(sec6.query(lla, i) == i * (i - 1) / 2, "Query sum between ", lla, "(The min key in section tree is 0) and ", i, ", get sum of ", sec6.query(lla, i), ", expected i * (i - 1) / 2");
  }
  testpart("checking query and add range");
 {
    section<int, int> sec0;
    for (int i(0); i < 100; i++) 
      sec0.insert(i, 0);
    for (int i(1); i < 100; i++) 
      sec0.add_range(i, 100, 1);
    
    test(true, "Construct section sec0 with 100 node of key between 0 and 100, then add range 100 time to make it ascending.");
    const int la{15};
    for (int i(la + 1); i < 100; i++)
      test(sec0.query(la, i) == (i - la) * (i + la - 1) / 2, "Query sum from ", la, " to ", i, ", the result is ", sec0.query(la, i), ", expected result ", (i - la) * (i + la - 1) / 2);

    const int ra{125};
    for (int i(0); i < 100; i++)
      test(sec0.query(i, ra) == (100 - i) * (i + 99) / 2, "Query sum from ", i, " to ", ra, "(The max key in tree is 99), get sum of ", sec0.query(i, ra), ", expected ", (100 - i) * (i + 99) / 2);

    const int lla{-10};
    for (int i(0); i < 100; i++) 
      test(sec0.query(lla, i) == i * (i - 1) / 2, "Query sum between ", lla, "(The min key in section tree is 0) and ", i, ", get sum of ", sec0.query(lla, i), ", expected i * (i - 1) / 2");

    for (int i(1); i < 100; i++) 
      sec0.add_range(i, 100, 1);
    test(true, "sec0 add range from 0 to 100 1");

    for (int i(0); i < 100; i++)
      test(sec0.get(i) == i * 2, "get value of key", i, ", value: ", sec0.get(i), ", expected ", i * 2);
    sec0.traverse();
  }
  testpart("STOP TEST");  //mark stop test, essential.

  cout << "-----------------------" << endl;
  cout << "End test section vessel, succeeded part(" << success_parts << "/" << parts << ")" << endl;
  fout << "-----------------------" << endl;
  fout << "End test section vessel, succeeded part(" << success_parts << "/" << parts << ")" << endl;
  fout.close();
  return 0;
}

void print() {}

template <typename Type, typename... Types>
void print(const Type& arg, const Types&... args) {
  cout << arg;
  fout << arg;
  print(args...);
}

template <typename... Types>
void test(bool judge, const Types&... args) {
  cout << testmachine.head << testmachine.part << '.' << testmachine.num << "=" << judge << " ";
  fout << testmachine.head << testmachine.part << '.' << testmachine.num << "=" << judge << " ";
  print(args...);
  cout << endl;
  fout << endl;
  testmachine.num++;
  if (judge) testmachine.success++;
}

void testpart(string s) {
  if (testmachine.part != 0) {
    cout << "} succeeded(" << testmachine.success << '/' << testmachine.num << "). ";
    fout << "} succeeded(" << testmachine.success << '/' << testmachine.num << "). ";
    if (testmachine.success == testmachine.num) {
      success_parts += 1;
      cout << "Pass test " << testmachine.head << testmachine.part << '.';
      fout << "Pass test " << testmachine.head << testmachine.part << '.';
    } else
      cout << "\n ! Not Pass Test, have " << -testmachine.success + testmachine.num << " bug(s).";
    cout << endl;
    cout << endl;
    fout << endl;
    fout << endl;
  }
  if (s == "STOP TEST") return;
  cout << ">> Start Test " << testmachine.head << testmachine.part << " " << s << " {" << endl;
  fout << ">> Start Test " << testmachine.head << testmachine.part << " " << s << " {" << endl;
  testmachine.part += 1;
  testmachine.num = 0;
  testmachine.success = 0;
  parts += 1;
}