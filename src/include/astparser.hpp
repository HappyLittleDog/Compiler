#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"
#include "logger.hpp"
#include "koopa.h"
#include <sstream>
using namespace std;

extern stringstream asms;

void Visit(const koopa_raw_program_t &program);

void Visit(const koopa_raw_slice_t &slice);

void Visit(const koopa_raw_function_t &func);

void Visit(const koopa_raw_basic_block_t &bb);

void Visit(const koopa_raw_value_t &value);

void Visit(const koopa_raw_return_t &ret);

void Visit(const koopa_raw_integer_t &integer);