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

## Notes

1. &&不能处理const&, 处理&还需要move
