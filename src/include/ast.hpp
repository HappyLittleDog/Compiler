#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <map>
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

class ConstSymTab
{
    map<string, int> nt;
public:
    ConstSymTab() = default;
    void insert(string symbol, int val)
    {
        auto it = nt.insert(make_pair(symbol,val));
        if (!it.second)
        {
            LOG_ERROR("@ConstSymTab::insert: Insert (%s, %d) failed!\n(%s, %d) already exists.", symbol.c_str(), val, symbol.c_str(), nt.find(symbol)->second);
        }
    }
    int get_val(string symbol)
    {
        auto it=nt.find(symbol);
        if (it==nt.end())
        {
            LOG_ERROR("@ConstSymTab::get_val: %s not found.",symbol.c_str());
        }
        return it->second;
    }
    bool exists(string symbol)
    {
        auto it=nt.find(symbol);
        return it!=nt.end();
    }
};
extern ConstSymTab CurConstSymTab;

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") const = 0;
    virtual void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const = 0;
    virtual bool IsConst() const {LOG_ERROR("@IsConst: unexpected function call!"); return false;} // used for expression ONLY!
    virtual int CalcVal() const {LOG_ERROR("@CalcVal: Unexpected function call!"); return 0;} // used for expression ONLY!
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
    bool isconst_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override {return subexp_->CalcVal();}
};

class LOrExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class LAndExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class EqExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class RelExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class AddExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class MulExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class UnaryExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class PrimaryExp : public BaseAst
{
public:
    bool isconst_;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override;
};

class Number : public BaseAst
{
public:
    string int_const_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return stoi(int_const_);};
};