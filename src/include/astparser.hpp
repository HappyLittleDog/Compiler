#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"
#include "logger.hpp"
#include "koopa.h"
#include <sstream>
#include <map>
using namespace std;

extern stringstream asms;

class Register_Allocator;

void Visit(const koopa_raw_program_t &program);

void Visit(const koopa_raw_slice_t &slice, Register_Allocator *ra = NULL);

void Visit(const koopa_raw_function_t &func);

void Visit(const koopa_raw_basic_block_t &bb, Register_Allocator *ra);

void Visit(const koopa_raw_value_t &value, Register_Allocator *ra, string dest_register=string(""));

void VisitBin(const koopa_raw_value_t &val, Register_Allocator *ra);

void Visit(const koopa_raw_return_t &ret, Register_Allocator *ra);

void Visit(const koopa_raw_integer_t &integer, string dest_register);