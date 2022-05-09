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

class Stack_Allocator;

///
/// [Visit] function group: Generate the RISC-V asm code
///

void Visit(const koopa_raw_program_t &program);

void Visit(const koopa_raw_slice_t &slice, Register_Allocator *ra = NULL, Stack_Allocator *sa=NULL);

void Visit(const koopa_raw_function_t &func);

void Visit(const koopa_raw_basic_block_t &bb, Register_Allocator *ra, Stack_Allocator *sa);

/**
 * @brief Visit raw value: Important central function
 * 
 * @param value koopa_raw_value_t of the val
 * @param ra 
 * @param sa 
 * @param dest_register used for visit INTEGER ONLY! It will move the integer to the dest_register.
 */
void Visit(const koopa_raw_value_t &value, Register_Allocator *ra, Stack_Allocator *sa, string dest_register=string(""));

void VisitBin(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitRet(const koopa_raw_return_t &ret, Register_Allocator *ra, Stack_Allocator *sa);

void VisitLoad(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

/**
 * @brief load var from mem to reg
 * 
 * @param val koopa_raw_value_t of the var.
 * @param ra register_allocator
 * @param sa stack_allocator
 * @return the dest register. NEED TO BE FREED AFTER USE!
 */
string ImplicitLoad(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitStore(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitBranch(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitJump(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitCall(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitGlobalVar(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitGetElemPtr(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitAlloc(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void VisitGetPtr(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa);

void Visit(const koopa_raw_integer_t &integer, string dest_register);

///
/// [Scan] function group: scan the IR and figure out the stack memory needed for vars
///

void Scan(const koopa_raw_slice_t &slice, Stack_Allocator *sa);

void Scan(const koopa_raw_basic_block_t &bb, Stack_Allocator *sa);

void Scan(const koopa_raw_value_t &val, Stack_Allocator *sa);

int CalcSize(const koopa_raw_type_t &ty); // calculate the total size of a given type