# section-

## 目录

- [核心功能](#核心功能)
- [设计思路](#设计思路)
- [使用方式](#使用方式)
  - [例子](#例子)
- [接口列表](#接口列表)
- [目标](#目标)

## 核心功能

提供一个c++模板类，高效的对连续节点的修改以及查询。  
支持的修改：加  
支持的查询：求和  

## 设计思路

数据结构基于动态开点线段树和B+树，key-value结构，支持单点插入，区间修改和区间查找。  

## 使用方式

### 例子
section sectionA;  
sectionA.insert(1,1);  
sectionA.insert(3,5);  
sectionA.query(1,3) //查询[1,3)的和：1  
sectionA.add_range(1,4,2) //将[1,4)区间内的所有节点值+1  
sectionA.query(1,4) //查询[143)的和：8  

## 接口列表

void insert(key_type __key, mapped_type __value) 插入  
mapped_type query(key_type __l, key_type __r) 查询  
void add_range(key_type __l, key_type __r, mapped_type __d_add) 区间修改  

## 目标
1.支持自定义的修改以及查询规则，要求用户传入修改以及查询的仿函数  
2.增添双向迭代器以及萃取机  
