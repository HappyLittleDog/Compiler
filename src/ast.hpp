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

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") const = 0;
    virtual void Dump(fstream& fs, string indent="") const = 0;
};

class CompUnit : public BaseAst
{
public:
    unique_ptr<BaseAst> funcdef_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};

class FuncDef : public BaseAst
{
public:
    unique_ptr<BaseAst> functype_;
    string ident_;
    unique_ptr<BaseAst> block_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};

class FuncType : public BaseAst
{
public:
    DataType rettype_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};

class Block : public BaseAst
{
public:
    unique_ptr<BaseAst> stmt_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};

class Stmt : public BaseAst
{
public:
    unique_ptr<BaseAst> retv_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};

class Number : public BaseAst
{
public:
    string int_const_;
    void Print(string indent="") const override;
    void Dump(fstream& fs, string indent="") const override;
};