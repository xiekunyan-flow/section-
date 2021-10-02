# section-
线段树是一种利用分治思想处理对一段序列进行大量区间操作（修改、查询）的数据结构。线段树的叶节点即为原序列，内部节点除了左右儿子之外，还保存着其分管的某段区间信息，如区间和、区间最值。显然，每个节点所分管的区间即为以其为根的子树中所有叶节点。

模版类容器是 C++ 中常用的数据结构，如标准库中的 `vector`, `list`, `map` 等。我们仿照标准库中的 `list`, `map`, 设计了 `section` 模版类来提供线段树功能

我们使用了大量测试样例来确保功能的正常使用，测试的源文件为 `test.cpp`, 测试结果保存在了 `testLog.txt` 中，但依旧有不严格的部分需要证明，或者找到会引起问题的实例

## 目录

- [section-](#section-)
  - [目录](#目录)
  - [核心功能](#核心功能)
  - [设计思路](#设计思路)
  - [使用方式](#使用方式)
    - [例子](#例子)
    - [接口列表](#接口列表)
      - [section](#section)
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

#### section

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

返回键位于 $[__l, __r)$ 内的值的和

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

将键位于 $[__l, __r)$ 的值都增加 `__d_add` 

mapped_type query(key_type __l, key_type __r) 查询  
void add_range(key_type __l, key_type __r, mapped_type __d_add) 区间修改  

## 目标
1.支持自定义的修改以及查询规则，要求用户传入修改以及查询的仿函数  
2.增添双向迭代器以及萃取机  
