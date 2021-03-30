# Structure

1. 指向父节点，指向子节点，叶子节点不同
2. 叶子节点和非叶子节点、end()
3. `_Section_node_base`->`_Section_leaf_node_base`和`_Section_tree_node_base`
4. `_Section_leaf_node_base`->`_Section_node_header`和`_Section_leaf_node`
5. `_Section_tree_node_base`->`_Section_tree_node`和`_Section_leaf_node`(F.0.1 don't do that)

```c++
*iterator += 2;

operator +=(int x) {
    //先执行父节点的操作
	_val += x;
	_parent->_val += x;
}

///[it1, it2)
section.add(it1, it2);

_Val _M_storage; //231行，可替换为
```

## Iterator

1. 关于`iterator`，能否同时支持`int a = iterator->second;`或者`int a = *iterator` `cout << iterator->second << endl;` 和 `*iterator += 3;`其实应该很简单，就是重载`=`，`++`，`+=`这些运算符就行。
2. `*iterator`是`pair`类型，当返回const时

## Questions

1. `_Rb_tree_key_compare`
2. 好像多重继承有些问题，还是杜绝多重继承比较好，一种合理的做法是，认为最后一层没有孩子节点，所以leaf_node不再继承_Section_tree_node_base，这样标记下一层是leaf节点就成为必须的了
3. 另一种我更建议的做法是去掉_Section_node_base，并且把._parent属性转交给_Section_leaf_node,
4. _Section_node_header中定名为`_parent`还是`_root`，我打算用`_root`了
5. 代码规范，写在.h里还是.cpp里

## Notes

1. &&不能处理const&, 处理&还需要move
