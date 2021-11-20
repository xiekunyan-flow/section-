# section

**线段树是一种利用分治思想处理对一段序列进行大量区间操作（修改、查询）的数据结构**。线段树的叶节点即为原序列，内部节点除了左右儿子之外，还保存着其分管的某段区间信息，如区间和、区间最值。显然，每个节点所分管的区间即为以其为根的子树中所有叶节点。

模版类容器是 C++ 中常用的数据结构，如标准库中的 `vector`, `list`, `map` 等。我们仿照标准库中的 `list`, `map`, 设计了 `section` 模版类来提供线段树功能

我们使用了大量测试样例来确保功能的正常使用，测试的源文件为 `test.cpp`, 测试结果保存在了 `testLog.txt` 中，但依旧有不严格的部分需要证明，或者找到会引起问题的实例

## 目录

- [section](#section)
  - [目录](#目录)
  - [核心功能](#核心功能)
  - [设计思路](#设计思路)
    - [线段树的插入](#线段树的插入)
  - [使用方式](#使用方式)
    - [例子](#例子)
    - [接口列表](#接口列表)
      - [section 构造函数](#section-构造函数)
      - [get](#get)
      - [query](#query)
      - [size](#size)
      - [traverse](#traverse)
      - [insert](#insert)
      - [add_range](#add_range)
  - [目标](#目标)

## 核心功能

提供一个c++模板类，高效的对连续节点的修改以及查询。  
支持的修改：加  
支持的查询：求和  

## 设计思路

数据结构基于动态开点线段树和B+树，key-value结构，支持单点插入，区间修改和区间查找。  

在我们的线段树结构中，叶子节点与非叶子节点是不同的数据结构。叶子节点包含着具体的 `(key, value)` 键值对，非叶子节点中包含着子树的信息。*事实上， 我们的叶子节点继承了非叶子节点，完全包含了非叶子节点的成员。*

![](fig/01.png)

我们设计的线段树有如下的特点：

1. 如上图所示，我们的线段树是一种偏右二叉树，一个非叶子节点要么有两个儿子，要么只有右儿子
2. 叶子节点的深度相同

### 线段树的插入

1. 新建插入的`_Section_leaf_node`节点a

2. 寻找到插入位置（节点a应该的父亲p），若无，则新建根节点
   1. p只有一个孩子，那么直接插入，并且遍历push_up上面所有的节点，并结束
   2. p有2个孩子，则swap，并更新push_up上一个节点p的维护信息

3. 如果p有右节点pr，则如果pr只有一个孩子，将a插入pr，并且遍历push_up上面所有节点，并结束

4. 如果 p 的后节点有左孩子，新建一个和 p 同级的的节点 b，连接 a 作为 b 的右孩子；如果 p 的后节点没有左孩子，则将 a 作为 p 的后节点的左孩子

5. 向上一层，找到pp，
   1. 如果不到头，重复3、4、5
   2. 到头，新建根节点

我们线段树的插入未必可以保证树的高度为 $O(\log N)$, 其中 $N$ 是树的叶子节点数。

## 使用方式

### 例子

```cpp
section<int, int> sectionA;  
sectionA.insert(1,1);  
sectionA.insert(3,5);  
sectionA.query(1,3) //查询[1,3)的和：1  
sectionA.add_range(1,4,2) //将[1,4)区间内的所有节点值+1  
sectionA.query(1,4) //查询[143)的和：8  
```

### 接口列表

#### section 构造函数

```cpp
section<key_type, mapped_type> your_sec;
```

#### get

```cpp
mapped_type get(_Key __key) const;
```

得到 `key` 对应的键

#### query

```cpp
mapped_type query(key_type __l, key_type __r);
```

返回键位于 [__l, __r) 内的值的和

#### size

```cpp
unsigned long size() const;
```

返回线段树的叶子节点数

#### traverse

```cpp
void traverse() const;
```

使用 `cout` 输出线段树的结构，先依次输出线段树每一个从根节点到叶节点的路径，再输出层次遍历线段树的结果

#### insert

```cpp
void insert(key_type, mapped_type);
```

插入 `(<key_type, mapped_type)` 键值对

#### add_range

```cpp
void add_range(key_type __l, key_type __r, mapped_type __d_add);
```

将键位于 [__l, __r) 的值都增加 `__d_add` 

## 目标

1. 证明我们线段树的插入可以保证树的高度为 $O(\log N)$, 其中 $N$ 是树的叶子节点数。
2. 支持自定义的修改以及查询规则，要求用户传入修改以及查询的仿函数  
3. 增添双向迭代器以及萃取机  
