#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <map>
#include "range_node.h"

using namespace::std;
using namespace::J;
using namespace::J::basic;
int main() {
    cout << "Start test range vessel" << endl;
    _Section_node_base section_node_base;
    cout << "J.1.0 Define object _Section_node_base, with default constructor, get its parent: " << section_node_base._parent << endl;
    cout << "J.1.1 Call function of _Section_node_base declared in range_node.h but defined in range_node.cc, with its output: ";
    section_node_base.print();
    cout << endl;
    cout << "End test range vessel" << endl;
    return 0;
}