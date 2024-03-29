# Lv9+. 新的开始

?> 本章为可选内容, **不做不扣分**, 选做可加分.

在前几章中, 你已经完成了一个可以将 SysY 程序编译到 RISC-V 汇编的编译器, 并且通过了所有的功能测试. 本章中, 你将在这个编译器的基础上, 实现更多更丰富的功能.

本章的内容包括:

* [**你的编译器超强的:**](/lv9p-reincarnation/awesome-compiler) 不要小瞧你的编译器, 它已经可以编译很多很了不起的程序了! 本节中就提供了一些示例程序. 如果你愿意的话, 可以在编译器的基础上扩展更多语法, 并且尝试用它编译更多更厉害的程序.
* [**寄存器分配:**](/lv9p-reincarnation/reg-alloc) 在之前的章节中, 你的编译器只实现了很简单 (简陋) 的寄存器分配算法. 你可以尝试在你的编译器中实现更复杂的寄存器分配算法, 来改善目标代码生成的质量.
* [**优化:**](/lv9p-reincarnation/opt) Koopa IR 的设计目标之一, 就是让 IR 层面的优化更易进行. 你可以在你的编译器上实现很多或简或繁的优化, 来改善 IR 生成/目标代码生成的质量, 提升编译得到的程序的性能.
* [**SSA 形式:**](/lv9p-reincarnation/ssa-form) Koopa IR 支持 SSA 形式——这是一种业界广泛使用的 IR 形式, 基于此可以简化很多分析/优化的实现. 你可以选择把编译器生成的 IR 提升至 SSA 形式, 来完成更多进阶的优化.
* [**性能测试:**](/lv9p-reincarnation/perf-testing) 在完成寄存器分配和各类优化后, 你可以对你的程序进行性能测试, 来直观感受这些改进带来的效果.
* [**向着更远处进发:**](/lv9p-reincarnation/go-further) 编译器可谓世界上最精巧的软件, 课程实践已经带你踏入了编译的大门, 而在这个领域, 还有更多有价值的课题等待你的研究. 路漫漫其修远兮, 吾将上下而求索.

本章不同于之前的章节:

1. **本章的内容并不是必选的**, 但完成本章的内容可以获得加分.
2. 本章将不会采取类似之前章节的 “手把手指导” 的模式, 而只会对其中必要的内容给出简要指导, 或者相关参考文献. 你需要自行探索对应内容的实现方法.

本章内的所有小节并无顺序关系, 你可以从任意一节开始阅读. 各小节的难度基本按照出现顺序递增.

最后, 即便你决定不完成本章中的可选内容, **我们依然推荐你阅读本章**, 尤其是 [Lv9+.1](/lv9p-reincarnation/awesome-compiler).
