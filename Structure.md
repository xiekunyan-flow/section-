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
4. `_Section_node_header`最后还是继承了`_Section_tree_node`，不过我还是打算用`_left`标记最大的节点，用`_right`标记最小的节点。
5. 代码规范，写在.h里还是.cpp里
6. `tree_node`有哪些成员？我打算整一个`_mid`, `_right`, `_has_mid`, `_Is_leaf`, (`_sum`)
   1. _sum 如何改进
7. F和J的空格多少貌似有歧义。
8. typedef只放在tree里就行了吧，除了`_Link_type`, however, seems that `Link_type` doesnot used at all.
9. 我的test工具
10. 目前只支持add和sum
11. 插入时若本来就有这个节点
12. 家福为啥执意tree节点只保留一个数据呢
13. 交换叶子节点和交换tree节点是不同的
14. throw，比如insert时

## Notes

1. &&不能处理const&, 处理&还需要move

## Rb_tree

1. `alloc_node`
2. `construct_node`, `create_node`
3. `insert_and_rebalance`目前找不到是怎么实现的，但我觉得能做
4. _M_get_insert_unique_pos

## Idea

1. 新建插入的`_Section_leaf_node`节点a
2. 寻找到插入位置（节点a应该的父亲p），若无，则新建根节点
3. 
   1. p只有一个孩子，那么直接插入，并且遍历push_up上面所有的节点，并结束
   2. p有2个孩子，则swap，并更新push_up上一个节点p的维护信息
4. 新建一个更上的节点b，连接a和b
5. 向上一层，找到pp，
   1. 如果不到头，重复3、4、5
   2. 到头，新建根节点

