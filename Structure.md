# Structure

1. 指向父节点，指向子节点，叶子节点不同
2. 叶子节点和非叶子节点、end()
3. `_Section_node_base`->`_Section_leaf_node_base`和`Section_tree_node_base`
4. `_Section_leaf_node_base`->`_Section_node_header`和`_Section_leaf_node`
5. `_Section_tree_node_base`->`_Section_tree_header`和`_Section_nonleaf_node`和`_Section_leaf_node`

1. 

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

