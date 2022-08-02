# Lv9+.5. 性能测试

在 Lv9+.2, Lv9+.3 和 Lv9+.4 中, 你已经为你的编译器添加了很多新的实现, 来生成性能更高的代码. 编译实践的本地实验环境/在线评测系统均支持性能测试, 在完成各类优化后, 你可以进行性能测试, 来直观感受这些改进带来的性能提升.

## 本地测试

```
docker run -it --rm -v 项目目录:/root/compiler maxxing/compiler-dev \
  autotest -perf -s perf /root/compiler
```

在运行测试前, 你需要确保你的编译器 (假设名称为 `compiler`) 能处理如下的命令行参数:

```
compiler -perf 输入文件 -o 输出文件
```

其中, `-perf` 代表此时正在进行性能测试, 你的编译器需要输出 RISC-V 汇编文件, 并且可在此基础上启用一些优化. `输入文件` 代表输入的 SysY 源文件的路径, `输出文件` 代表 RISC-V 汇编的输出文件路径. 你的编译器应该解析 `输入文件`, 并把生成的 RISC-V 汇编输出到 `输出文件` 中.

## 在线评测

?> **TODO:** 待补充.