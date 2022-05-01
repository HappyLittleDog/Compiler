#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "logger.hpp"
using namespace std;

class BaseAst;
class CompUnit;
class FuncDef;
class FuncType;
class Block;
class Stmt;
class Number;
enum class DataType { INT, VOID };
extern int temp_var_counter;

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") const = 0;
    virtual void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const = 0;
};

class CompUnit : public BaseAst
{
public:
    unique_ptr<BaseAst> funcdef_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class FuncDef : public BaseAst
{
public:
    unique_ptr<BaseAst> functype_;
    string ident_;
    unique_ptr<BaseAst> block_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class FuncType : public BaseAst
{
public:
    DataType rettype_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class Block : public BaseAst
{
public:
    unique_ptr<BaseAst> stmt_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class Stmt : public BaseAst
{
public:
    unique_ptr<BaseAst> retv_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class Exp : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class LOrExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class LAndExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class EqExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class RelExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class AddExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class MulExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class UnaryExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class PrimaryExp : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class Number : public BaseAst
{
public:
    string int_const_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};