#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"
#include "logger.hpp"

using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAst> &ast);

int main(int argc, const char *argv[]) {
    // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
    // compiler 模式 输入文件 -o 输出文件
    assert(argc == 5);
    auto mode = argv[1];
    auto input = argv[2];
    auto output = argv[4];

    // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
    yyin = fopen(input, "r");
    assert(yyin);

    // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
    unique_ptr<BaseAst> ast;
    auto ret = yyparse(ast);
    assert(!ret);

    if (string(mode)==string("-koopa"))
    {
        fstream fs;
        fs.open(output,fstream::out | fstream::trunc);
        if (!fs.is_open())
        {
            LOG_ERROR("can not open output file %s", output);
            exit(-1);
        }
        ast->Dump(fs);
        ast->Print();
        fs.close();
    }
    else
    {
        LOG_ERROR("TODO");
    }
    return 0;
}
