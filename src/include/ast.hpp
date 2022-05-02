#pragma once
#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
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
int new_srcvar();

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

class VarSymTab
{
    map<string, int> nt;
public:
    VarSymTab() = default;
    int insert(string symbol)
    {
        int pos=new_srcvar();
        auto it = nt.insert(make_pair(symbol, pos));
        if (!it.second)
        {
            LOG_ERROR("@ConstSymTab::insert: Insert (%s, %d) failed!\n(%s, %d) already exists.", symbol.c_str(), pos, symbol.c_str(), nt.find(symbol)->second);
        }
        return pos;
    }
    int get_pos(string symbol)
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
extern VarSymTab CurVarSymTab;

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") const = 0;
    virtual void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const = 0;
    virtual bool IsConst() const {LOG_ERROR("@IsConst: unexpected function call!"); return false;} // used for expression ONLY!
    virtual int CalcVal() const {LOG_ERROR("@CalcVal: Unexpected function call!"); return 0;} // used for expression ONLY!
    virtual string GetIdent() const {LOG_ERROR("@GetIdent: Unexpected function call!"); return "";} // used for LVal ONLY!
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
    unique_ptr<BaseAst> items_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class BlockItems : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > items_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class BlockItem : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class Decl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class ConstDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class VarDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class ConstDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class ConstDef : public BaseAst
{
public:
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class ConstInitVal : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return subexp_->CalcVal();}
};

class ConstExp : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return subexp_->CalcVal();}
};

class VarDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class VarDef : public BaseAst
{
public:
    int cur_derivation_;
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
};

class InitVal : public BaseAst
{
public:
    bool isconst_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override {return subexp_->CalcVal();}
};

class Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
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

class LVal : public BaseAst
{
public:
    string ident_;
    bool isconst_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override {return CurConstSymTab.get_val(ident_);}
    string GetIdent() const override {return ident_;}
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