# 数学库 —— CasYYY

![License](https://img.shields.io/badge/license-MIT-blue.svg)

## 介绍：
- 在这个文件夹内，写了主要由自己实现的数学库。囊括了分数，浮点数，线性代数，大数，全为C++实现。

## 环境要求：
- C++ 17 以上 （linear_algebra）（GCC 8+, Clang 6+, VS2017 15.7+）
- C++ 20 以上 （除了linear_algebra）（GCC 11+, Clang 14+, VS2022 17.4+）

## 内容：
|项目名称|C++标准|核心内容|详细文档|状态|
|:---:|:---:|:---:|:---:|:---:|
|[线性代数](/my_math/linear_algebra/)|C++ 17|基本线性代数的数据结构，以及一些算法实现|[README](/my_math/linear_algebra/README.md)|持续更新中|
|[高精度数](/my_math/big_number/)|C++ 20|基本的高精度整数和浮点数，以及运算|[README](//my_math/big_number/README.md)|持续更新中|
|[几何](/my_math/geometry/)|C++ 20|基本的几何运算|[README](/my_math/geometry/README.md)|持续更新中|
|[分数](/my_math/fract/)|C++ 20|基本的分数定义和计算|[README](/my_math/fract/README.md)|持续更新中|
|...|...|...|...|...|

*可点击项目名称查看项目文件夹，README查看文档（不过有许多README没写完，只有个空的占位符）*

## 使用
1. **克隆仓库**
```bash
git clone https://github.com/mir12lyy-cloud/my_things.git
cd my_things/my_math
```
2. **阅读README** 
   项目内的README会介绍安装和使用的方法，以及内置函数，根据指引即可。
3. **环境要求**
    请根据项目内的README检查C++的编译器和标准是否符合要求。
4. **注意命名空间**
    里面所有的文件囊括在mymath命名空间中，使用时注意包括这个命名空间。
5. **一些其他事项**
    在这里，有一些项目类一并存放了旧实现（前面加了old_前缀），old版通常不太成熟，请建议不要使用。

## 贡献
虽然本文件夹主要是我个人学习的集合，但是如果你有任何的改进建议，欢迎提交Issue和Pull Request!

## 许可
本项目统一使用 [MIT许可证](/LICENSE)，任何人可以自由使用，保留原作者信息即可。

## 联系我
- 邮箱：huangjinyangyang@hotmail.com
- QQ：671489684
- Github：@mir12lyy-cloud


## 更新记录
- 2026-04-06 创建了这个文件。