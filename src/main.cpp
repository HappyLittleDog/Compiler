#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "include/ast.hpp"
#include "include/logger.hpp"
#include "include/koopa.h"
#include "include/astparser.hpp"
#include <ios>
#include <sstream>
using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAst> &ast);

int main(int argc, const char *argv[]) {
    /* ============================================================================
     *
     *             Formal main function, used for testing and handin
     * 
     * ============================================================================
    */

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
    else if (string(mode)==string("-riscv"))
    {
        fstream fs;
        fs.open(output,fstream::out | fstream::trunc);
        if (!fs.is_open())
        {
            LOG_ERROR("can not open output file %s", output);
            exit(-1);
        }
        stringstream koopas;
        ast->Dump(koopas);
        auto koopastr=koopas.str();
        auto koopacstr=koopastr.c_str();

        koopa_program_t program;
        koopa_error_code_t retv = koopa_parse_from_string(koopacstr, &program);
        assert(retv == KOOPA_EC_SUCCESS);  // 确保解析时没有出错
        // 创建一个 raw program builder, 用来构建 raw program
        koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
        // 将 Koopa IR 程序转换为 raw program
        koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
        // 释放 Koopa IR 程序占用的内存
        koopa_delete_program(program);
        // 处理 raw program
        Visit(raw);
        // 处理完成, 释放 raw program builder 占用的内存
        // 注意, raw program 中所有的指针指向的内存均为 raw program builder 的内存
        // 所以不要在 raw program builder 处理完毕之前释放 builder
        koopa_delete_raw_program_builder(builder);

        fs<<asms.str();
        fs.close();
    }
    else
    {
        LOG_ERROR("TODO");
    }
    return 0;

    /* ============================================================================
     * 
     *                Playground, used for development and have fun!
     * 
     * ============================================================================
     */
    // char input[]="test/hello.c";
    // yyin = fopen(input, "r");
    // assert(yyin);
    // unique_ptr<BaseAst> ast;
    // auto ret = yyparse(ast);
    // assert(!ret);

    // stringstream koopas;
    // ast->Dump(koopas);
    // auto koopastr=koopas.str();
    // auto koopacstr=koopastr.c_str();

    // koopa_program_t program;
    // koopa_error_code_t retv = koopa_parse_from_string(koopacstr, &program);
    // assert(retv == KOOPA_EC_SUCCESS);  // 确保解析时没有出错
    // // 创建一个 raw program builder, 用来构建 raw program
    // koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    // // 将 Koopa IR 程序转换为 raw program
    // koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    // // 释放 Koopa IR 程序占用的内存
    // koopa_delete_program(program);
    // // 处理 raw program
    // LOG_INFO("src koopa: %s",koopacstr);
    // LOG_INFO("convertion done");
    // LOG_INFO("func num: %d",raw.funcs.len);
    // for (size_t i = 0; i < raw.funcs.len; ++i) 
    // {
    //     // 正常情况下, 列表中的元素就是函数, 我们只不过是在确认这个事实
    //     // 当然, 你也可以基于 raw slice 的 kind, 实现一个通用的处理函数
    //     assert(raw.funcs.kind == KOOPA_RSIK_FUNCTION);
    //     // 获取当前函数
    //     koopa_raw_function_t func = (koopa_raw_function_t) raw.funcs.buffer[i];
    //     // 进一步处理当前函数
    //     for (size_t j = 0; j < func->bbs.len; ++j) 
    //     {
    //         assert(func->bbs.kind == KOOPA_RSIK_BASIC_BLOCK);
    //         koopa_raw_basic_block_t bb = (koopa_raw_basic_block_t) func->bbs.buffer[j];
    //         // 进一步处理当前基本块
    //         // ...
    //         LOG_INFO("name:%s",bb->name);
    //         LOG_INFO("used by type: %d",bb->used_by.kind);
    //         LOG_INFO("used by len: %d",bb->used_by.len);
    //         LOG_INFO("num: %d",bb->insts.len);
    //         LOG_INFO("kind: %d",bb->insts.kind);
    //         for (size_t k=0;k<bb->insts.len;k++)
    //         {
    //             koopa_raw_value_t value=(koopa_raw_value_t) bb->insts.buffer[k];
    //             // 示例程序中, 你得到的 value 一定是一条 return 指令
    //             assert(value->kind.tag == KOOPA_RVT_RETURN);
    //             // 于是我们可以按照处理 return 指令的方式处理这个 value
    //             // return 指令中, value 代表返回值
    //             koopa_raw_value_t ret_value = value->kind.data.ret.value;
    //             // 示例程序中, ret_value 一定是一个 integer
    //             assert(ret_value->kind.tag == KOOPA_RVT_INTEGER);
    //             // 于是我们可以按照处理 integer 的方式处理 ret_value
    //             // integer 中, value 代表整数的数值
    //             int32_t int_val = ret_value->kind.data.integer.value;
    //             // 示例程序中, 这个数值一定是 0
    //             assert(int_val == 0);
    //         }
    //     }
    // }


    // // 处理完成, 释放 raw program builder 占用的内存
    // // 注意, raw program 中所有的指针指向的内存均为 raw program builder 的内存
    // // 所以不要在 raw program builder 处理完毕之前释放 builder
    // koopa_delete_raw_program_builder(builder);
}
