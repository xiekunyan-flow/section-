#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <map>
#include <string>
#include "section_node.h"
#include <bitset>

using namespace::std;
using namespace::J;
using namespace::J::basic;

struct Testmachine {
    string head;
    int num;
} testmachine;

template<typename... Types>
void _t(bool, const Types&... args);


int main() {
    cout << "Start test section vessel" << endl;
    cout << "-------------------------" << endl;

    testmachine.head = "J.1.";
    testmachine.num = 0;

    _Section_node_base section_node_base;
    _t(nullptr == section_node_base._parent, "Define object _Section_node_base, with default constructor, get its parent: ", section_node_base._parent, "expected nullptr.");

    _t(true, "Call function of _Section_node_base declared in section_node.h but defined in range_node.cc, with its output: ", section_node_base.print());
    
    _Section_leaf_node_base section_leaf_node_base;
    _t(section_leaf_node_base._parent == nullptr, "Define object _Section_leaf_node_base, with default constructor, get its parent: ", section_leaf_node_base._parent, ", expected nullptr");

    _t(section_leaf_node_base._next == nullptr && section_leaf_node_base._prev == nullptr, "Checkout whether section_leaf_node_base._next is nullptr: ", section_leaf_node_base._next, " ,expected nullptr;", " Checkout whether section_leaf_node_base._prev is nullptr: ", section_leaf_node_base._prev, " ,expected nullptr;");

    section_node_base._parent = &section_leaf_node_base;
    _t(section_node_base._parent == &section_leaf_node_base, "Let section_node_base._parent -> section_leaf_node_base, see their memory address. section_node_base._parent: ", section_node_base._parent, ", &section_leaf_node_base: ", &section_leaf_node_base);

    _Section_node_base* section_node_base_ptr(&section_leaf_node_base);
    _t(section_node_base_ptr == &section_leaf_node_base, "Define _Section_node_base_ptr, point to section_leaf_node_base.");

    static_cast<_Section_leaf_node_base*>(section_node_base_ptr)->_next = &section_leaf_node_base;
    _t(section_node_base_ptr == section_leaf_node_base._next, "static_cast the father node to child, modify ._next variable which father not have.");

    cout << "-----------------------" << endl;
    cout << "End test section vessel" << endl;
    return 0;
}

void print() {} // 递归终止条件。这是必需的。
 
template<typename Type, typename... Types>
void print(const Type& arg, const Types&... args)
{
  cout << arg;
  print(args...);
}

template<typename... Types>
void _t(bool judge, const Types&... args) {
    cout << testmachine.head << testmachine.num << "=" << judge << " ";
    print(args...);
    cout << endl;
    testmachine.num++;
}