# 前置知识

本节介绍了进行编译原理课程实践所需的部分前置知识. 如果你对此并不了解, 建议你先花一些时间进行学习.

## 如何使用 Linux

一些你需要知道的基本内容:

* **运行当前目录下程序:** `./程序名`. 比如你在当前目录下编译得到了你的编译器, 文件名为 `compiler`, 你可以执行 `./compiler`.
* **查看上一条命令的返回值:** `echo $?`. 比如你可以在 Shell 中执行 `命令; echo $?` 来运行一个命令, 同时输出它的返回值.
* **重定向输出:** 你希望把某命令输出到标准输出 (`stdout`) 的内容重定向到文件里, 可以执行 `命令 > 输出文件`. 例如: `ls > output.txt`.
* **重定向输入:** 你希望把某个文件的内容作为某个命令的输入内容 (`stdin`), 可以执行 `命令 < 输入文件`. 例如: `wc -l < input.txt`.
* **管道:** 你希望运行多个命令, 将前一个命令的标准输出作为后一个命令的标准输入, 可以执行 `命令1 | 命令2 | ... | 命令n`. 例如: `cat hello.txt | grep "hello" | wc -l`.

一些常用命令:

* `cd 目录`: 切换到目录.
* `pwd`: 输出当前目录.
* `ls`: 输出当前目录下所有的文件.
* `mkdir 目录`: 新建目录.
* `cp 源文件 目标`: 把源文件复制到目标.
* `mv 源文件 目标`: 把源文件移动到目标.
* `rm 文件`: 删除文件.
* `man 命令`: 显示命令的使用方法.

推荐 [Linux 入门教程](https://nju-projectn.github.io/ics-pa-gitbook/ics2021/linux.html).

## 如何使用 Git

Git 是一个版本控制系统 (version control system, VCS). 什么是版本控制? 为什么需要做版本控制?

想象你正在开发你的编译器, 你决定给你的编译器实现一个新的功能, 但添加这个功能需要修改大量之前的代码. 你一咬牙一狠心, 熬了个大夜, 终于把这个功能加完了, 编译时遇到的问题也都修好了. 你信心满满地打开 OJ 交了一发:

*“tmd, 一个测试用例都没过.”*

你坐在宿舍的椅子上, 窗户灌进阵阵冷风, 看着 WA 声一片的提交界面, 你的心早就凉了.

“要是能回到加这个功能之前就好了.” 你想着. 但你没有粉色大猫猫, 也没有 SERN 的 LHC (和助手), 更没有时之盾牌, 那些过去的时间再也回不去了.

不过, 不幸中的万幸, 你用 Git 管理了你的代码.

你熟练地在命令行里敲下 `git reset xxx`, 瞬间, 一切回到了那天之前.

一些你需要知道的基本内容:

* **初始化 Git 仓库:** 在仓库目录中 `git init`.
* **忽略部分文件的更改:** 在对应目录中放置 `.gitignore` 文件, 并在该文件中添加需要忽略的文件的规则.
* **查看仓库状态:** `git status`.
* **暂存更改:** `git add 文件名`, 或 `git add -A` 暂存全部更改.
* **提交更改:** `git commit`, 此时会弹出默认编辑器并要求你输入提交信息. 也可以直接执行 `git commit -m "提交信息"`.
* **添加远程仓库:** `git remote add 名称 仓库URL`.
* **推送本地提交到远程:** `git push`.
* **查看所有提交记录:** `git log`, 你可以从中看到某个提交的哈希值.
* **把仓库复位到某个提交的状态:** `git reset 提交的哈希值`.
* **从当前提交新建分支并切换:** `git checkout -b 分支名`.
* **切换到分支:** `git checkout 分支名`.
* **删除分支:** `git branch -D 分支名`.

上面提到了 `.gitignore` 可以让 Git 忽略目录中某些文件, 且不让它们出现在 Git 仓库中. 这有什么用呢?

你在开发过程中难免会产生一些 **“只对你自己有用”** 且 **“不值得永久保留”** 的东西. 比如你在开发的过程中希望写几个简单的输入来测试你的程序, 或者验证你程序里的某处是否写对了, 于是你新建了个名字叫 `test.txt` 的文件, 里面写了一些测试的内容, 然后你在本地调试的时候会让你的程序读取这个文件.

`test.txt` 显然只是个用来存放写一些只对你自己有用的临时内容的文件, 你不希望让 Git 每次都记录这个文件的更改 (因为没意义), 所以你可以把它写进 `.gitignore` 中, 来让 Git 忽略它.

其他类似的情况还包括, 你使用 VS Code 或 IDEA 开发你的编译器, 这些代码编辑器/IDE 可能会在项目中生成一些配置文件 (`.vscode` 或 `.idea`), 这些文件通常也是不需要被 Git 记录的, 因为其中包含了你的一些个人配置.

此外, 你还可能会使用代码生成器, 生成器读取一个描述生成规则的输入文件, 据此生成对应的代码. 比如在编译实践中, 你很可能会使用 Flex/Bison, 它们会根据 `.l`/`.y` 文件的内容, 生成 lexer 和 parser 的 C/C++ 文件和头文件.

对于这种情况, 你应该**只在 Git 中保留喂给生成器的输入文件**, 而不应该保留生成器生成的代码. 因为只要你安装了代码生成器, 你总能根据这些输入文件重新生成代码, 在 Git 中记录生成的代码没什么意义, 有时还会出现问题. 比如你修改了生成器规则, 但你没更新生成后的代码, 导致提交评测后评测机拉到了错误的代码, 于是你的编译器过不了评测, 然后你看着规则描述百思不得其解, 一天就这么过去了.

推荐:

* [Learn Git Branching](https://learngitbranching.js.org).
* [Git 快速入门](https://nju-projectn.github.io/ics-pa-gitbook/ics2021/git.html).

## 如何使用 GDB/LLDB

调试程序有几种方法:

* **硬看:** 基本没啥用.
* **print 大法:** 对小问题有用, 但一旦问题复杂起来, 你将迷失在巨量的日志里, 大脑过载, 难以自拔.
* **使用 IDE 提供的调试功能:** 比较有用, 但也比较复杂. 而且有些情况你没法用 IDE 的调试器解决, 比如你的编译器生成的 RISC-V 程序在 QEMU 里运行的时候出现了段错误, 你需要调试 QEMU 里的那个程序.
* **使用 GDB/LLDB 等调试器:** 非常有用, 适用范围极广, 但相对较难上手.

一些你需要知道的基本内容:

* **编译带调试信息的 C/C++ 程序:** `gcc/g++ -g -O0 ...`.
* **用调试器载入程序:** `gdb/lldb 程序名`.
* **用调试器载入程序并指定启动参数:** `gdb --args 程序名 参数 ...`, `lldb 程序名 -- 参数 ...`, 此时会进入调试器的命令行. 后续命令均需要在调试器的命令行中执行.
* **添加断点:** `b 函数名`, `b 文件名:行号`.
* **删除断点:** GDB: `d 断点编号`, LLDB: `br del 断点编号`.
* **查看所有断点:** GDB: `info b`, LLDB: `br list`.
* **执行程序:** `r`.
* **单步执行, 跳过函数:** `n`.
* **单步执行, 进入函数:** `s`.
* **继续执行直到断点/出错:** `c`.
* **查看调用栈:** `bt`.
* **切换调用栈:** GDB: `frame 编号`, LLDB: `frame select 编号`.
* **暂停执行:** `Ctrl + C`.
* **退出:** `q` 或 `Ctrl + D`.

一个例子:

你写的编译器出现了段错误——这种问题使用 `print` 大法调试效率很低, 因为你很难知道你的编译器到底在何处出现了段错误, 进而无法得知应该在何处插入 `print`. 遇到这种情况, 不妨使用调试器载入程序并运行, 当程序出现段错误时, 调试器会停住并进入命令行供你操作. 此时你就可以使用 `bt` 查看调用栈, 定位出错的位置, 然后在合适的地方下断点, 并重新运行程序来进一步调试了.

推荐:

* [GDB cheat sheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf).
* [LLDB cheat sheet](https://www.nesono.com/sites/default/files/lldb%20cheat%20sheet.pdf).

## 如何编写简单的 Makefile

你可能很熟悉如何使用 IDE 来开发简单的 C/C++ 程序: 新建工程, 写代码, 按下运行按钮, BOOM, 程序就跑了起来 ~(当然也可能跑不起来)~. 但当使用命令行环境时, 你可能就完全不懂该如何编译/运行你写的 C/C++ 程序了.

当然, 聪明的你可能知道如何使用 `gcc`/`g++`:

```
gcc hello.c -o hello
```

太好了, 我们可以直接通过调用编译器来编译我们的代码, 然后再直接运行生成的程序即可. 手敲命令行, 完全可以满足需求, 每次也不会很麻烦, 听起来还很酷.

然而在编译实践课中, 你写的程序通常不会由简单的一个 C/C++ 源文件构成. 甚至里面还可能包括非 C/C++ 的文件, 例如 `.l`/`.y` 文件. 这个时候, 你就无法用一条命令来编译你的编译器了:

```
flex -o lexer.c lexer.l
bison -d -o parser.c parser.y
gcc lexer.c parser.c ast.c ... -o compiler
```

想象一下, 如果你每次都手敲上面的一大堆命令, 才能得到一个自己的编译器的话, 那烦都得烦死了. 当然, 更聪明的你会想到写一个 Shell 脚本:

```bash
#!/bin/bash

flex -o lexer.c lexer.l
bison -d -o parser.c parser.y
gcc lexer.c parser.c ast.c ... -o compiler
```

这么做当然可以解决问题, 但也带来了别的问题: 你每次都必须重新编译所有的 C/C++ 源文件. 你可能觉得: 这也算问题? 如果你开发的的编译器代码量不是特别小, 你就会明显感觉到相比编译那些只有单个源文件的程序, 编译你的整个编译器的时间会更长. 而如果你写的程序的规模进一步增大 (比如你写了一个操作系统或者浏览器内核), 进行一次完整编译的时间也会大大增长.

有没有一种办法缩短编译的时间呢? 其实是有的. 大家都知道, C/C++ 源文件会经过编译, 链接的步骤才能变成可执行文件, 所以 `gcc` 在编译你的编译器的时候实际上执行了如下操作:

```
gcc lexer.c -c -o lexer.o
gcc parser.c -c -o parser.o
gcc ast.c -c -o ast.o
...
gcc lexer.o parser.o ast.o ... -o compiler
```

最后一步是链接, 此前所有的步骤都是编译. 我们不难发现, 在我们之前已经进行过一次编译/链接的情况下, 如果一个 `.c` 文件 (及其 `include` 的头文件) 的内容没有发生变化, 我们就没必要再把它编译成 `.o` 文件——反正之前已经编译过了, 再编译一次结果也不会变的. 如果我们不再重复编译没发生变化的源文件, 那编译的时间就可以大大减少了.

更进一步, 我们可以写一个脚本, 检查自己编译器的源文件是否发生过变化. 如果没有, 就不重新编译这个文件. 实际上, 这就是 `Makefile` 的作用. 我们可以把之前的那个 Shell 脚本写成 `Makefile` 的形式:

!> 注意 Docsify 渲染代码块的时候会把里面的 tab 缩进[全部替换成空格](https://github.com/markedjs/marked/issues/1668), 但 `Makefile` 里只能使用 tab 缩进, 所以不要直接在网页上复制下面的代码.

```makefile
compiler: lexer.o parser.o ast.o
	gcc lexer.o parser.o ast.o -o compiler

lexer.o: lexer.c
	gcc lexer.c -c -o lexer.o

parser.o: parser.c
	gcc parser.c -c -o parser.o

ast.o: ast.c
	gcc ast.c -c -o ast.o

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.c: parser.y
	bison -d -o parser.c parser.y
```

在命令行中执行:

```
make compiler
```

然后, `make` 就会根据 `Makefile` 的内容, 自动帮我们生成 `compiler` 这个文件.

`Makefile` 的基本语法其实很简单. 你可以注意到上面的例子中出现了很多 `file1: file2 file3 ...` 的写法, 它的含义是: 要生成 `file1`, 必须确保 `file2`, `file3`, ... 是存在的, 如果他们不存在, 就去生成相应的文件. 在这行之后带有缩进的内容描述了应该如何生成冒号之前的那个文件.

所以, 例子中的 `Makefile` 描述了这样的事情: 要想生成 `compiler`, 就必须保证 `lexer.o`, `parser.o` 和 `ast.o` 是存在的. 如果这些文件存在, 就使用 `gcc lexer.o parser.o ast.o -o compiler` 这条命令来生成 `compiler` 这个文件; 如果这些文件不存在, 就尝试用文件里写明的其他规则生成这些文件. 之后的规则与之类似, 不再赘述.

当然, 我们其实可以直接在命令行执行:

```
make
```

这和 `make compiler` 是等价的, 因为在不指定 `make` 什么文件的时候, `make` 会查找 `Makefile` 里出现的第一个规则, 然后去生成这个规则对应的文件.

`make` 不仅会检查文件是否存在, 还会检查文件是否是最新的. 在 `compiler: lexer.o parser.o ast.o` 规则中, 如果 `lexer.o`, `parser.o` 和 `ast.o` 都存在, 但其中某个文件 “不是最新的”, 那 `Makefile` 也会重新生成这些文件, 再用更新后的文件生成 `compiler`.

`make` 如何判断文件是最新的呢? 假设我们已经执行过一次 `make`, 然后修改了 `lexer.l`, 再执行一次 `make`. `make` 会做以下操作:

* 检查 `compiler` 是否需要更新, 如果一个文件不存在, 或者它依赖的其他文件中, 有文件不存在或需要更新, 这个文件就需要更新.
  * `compiler` 存在, 依赖 `lexer.o`, `parser.o` 和 `ast.o`, 检查这三个文件是否需要更新.
    * `lexer.o` 存在, 依赖 `lexer.c`, 检查这个文件是否需要更新.
      * `lexer.c` 存在, 依赖 `lexer.l`, 检查这个文件是否需要更新.
        * `lexer.l` 存在, 被修改过. 这个文件没有对应的更新规则, 所以 `make` 不会去管它. 你可以理解为 `make` 认为这个文件已经被用户更新了.
      * `lexer.c` 需要更新, 执行 `flex -o lexer.c lexer.l` 来更新文件.
    * `lexer.o` 需要更新, 执行 `gcc lexer.c -c -o lexer.o` 来更新文件.
    * 检查 `parser.o` 和 `ast.o` 是否需要更新. 它们都不需要更新.
  * `compiler` 需要更新, 执行 `gcc lexer.o parser.o ast.o -o compiler` 来更新文件.
* 所有需要更新的文件都被更新过了, `make` 的任务完成了, 退出.

`make` 通过上述方式, 实现了 “只重新编译我们修改过的文件” 的功能, 节省了编译的时间.

当然, 你可能会觉得我们给出的这个示例 `Makefile` 写的太啰嗦了. 比如, 所有的 `.o` 文件其实都依赖于对应文件名的 `.c` 文件, 而且他们的构建方式也完全相同, 那我们为什么要把类似的规则重复写三遍呢? `make` 提供了一些语法来帮助我们简化 `Makefile` 的写法:

```makefile
compiler: lexer.o parser.o ast.o
	gcc $^ -o $@

%.o: %.c
	gcc $^ -c -o $@

lexer.c: lexer.l
	flex -o $@ $^

parser.c: parser.y
	bison -d -o $@ $^
```

至于上面这些语法都是什么含义, 此处就不再赘述了, 你可以自行查看 `make` 手册中的相关部分 ([Pattern Rules](https://www.gnu.org/software/make/manual/make.html#Pattern-Rules) 和 [Automatic Variables](https://www.gnu.org/software/make/manual/make.html#Automatic-Variables)).

推荐:

* [GNU make](https://www.gnu.org/software/make/manual/make.html).

## 为什么要设置这一节

据 MaxXing 观察, 有些同学确实完全不了解某些工具的基础使用方法. 甚至在往年的课程实践中出现过这些情况:

* 一些同学不清楚在 Linux 的 Shell 中执行当前目录下的文件时, 需要在文件名前添加 `./`.
* 一些同学不清楚为什么自己写的代码 (`xxx.c`) 无法 `#include <iostream>`.
* 一些同学不理解 `.gitignore` 文件的作用, 每次都向平台提交巨量的文件 (OJ 服务器心里苦).
* 一些同学完全不懂如何调试自己的程序, 只能每次都随便改改自己的代码, 凭运气过测试点.

考虑到大学中可能并不会专门讲授这些常识性的内容 (但显然**这不合理**), 这些现象的出现也情有可原. 但在开始实验之前, 你必须对此有一个最基本的认识, 否则在你面前的, 将会是一条通往地狱的路.

我强烈推荐大家抽一些时间, 学习一下 MIT 的 [The Missing Semester of Your CS Education](https://missing.csail.mit.edu/), 这会对你的日常开发起到相当大的帮助.
