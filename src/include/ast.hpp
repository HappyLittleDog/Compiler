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

struct SymTabEntry
{
    bool isconst_;
    int val_; // val for const, @[pos] for var
    SymTabEntry(bool isconst, int val): isconst_(isconst), val_(val){};
};


class SymTab
{
    map<string, SymTabEntry> nt;
public:
    SymTab* pred_;
    SymTab() = default;
    void insert_const(string symbol, int val)
    {
        auto it = nt.insert(make_pair(symbol, SymTabEntry(true, val)));
        if (!it.second)
        {
            LOG_ERROR("@SymTab::insert_const: Insert (%s, %d) failed!\n(%s, <%d, %d>) already exists.", symbol.c_str(), val, symbol.c_str(), nt.find(symbol)->second.isconst_, nt.find(symbol)->second.val_);
        }
    }

    void insert_var(string symbol)
    {
        int pos=new_srcvar();
        auto it = nt.insert(make_pair(symbol, SymTabEntry(false, pos)));
        if (!it.second)
        {
            LOG_ERROR("@SymTab::insert_var: Insert %s failed!\n(%s, <%d, %d>) already exists.", symbol.c_str(), symbol.c_str(), nt.find(symbol)->second.isconst_, nt.find(symbol)->second.val_);
        }
    }

    SymTabEntry find(string symbol)
    {
        auto cur = this;
        while (cur!=NULL)
        {
            auto it=cur->nt.find(symbol);
            if (it!=cur->nt.end())
            {
                return it->second;
            }
            cur=cur->pred_;
        }
        LOG_ERROR("@SymTab::find: %s not found.",symbol.c_str());
        return SymTabEntry(0,0);
    }

    bool is_const(string symbol)
    {
        auto cur = this;
        while (cur!=NULL)
        {
            auto it=cur->nt.find(symbol);
            if (it!=cur->nt.end())
            {
                return it->second.isconst_;
            }
            cur=cur->pred_;
        }
        LOG_ERROR("@SymTab::is_const: %s not found.",symbol.c_str());
        return false;
    }
};
extern SymTab* CurSymTab; 

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") = 0;
    virtual void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) = 0;
    virtual int IsConst() {LOG_ERROR("@IsConst: unexpected function call!"); return -1;} // used for expression ONLY!
    virtual int CalcVal() {LOG_ERROR("@CalcVal: Unexpected function call!"); return 0;} // used for expression ONLY!
    virtual string GetIdent() {LOG_ERROR("@GetIdent: Unexpected function call!"); return "";} // used for LVal ONLY!
};

class CompUnit : public BaseAst
{
public:
    unique_ptr<BaseAst> funcdef_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class FuncDef : public BaseAst
{
public:
    unique_ptr<BaseAst> functype_;
    string ident_;
    unique_ptr<BaseAst> block_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class FuncType : public BaseAst
{
public:
    DataType rettype_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class Block : public BaseAst
{
public:
    unique_ptr<BaseAst> items_;
    SymTab* SymTab_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class BlockItems : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > items_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class BlockItem : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class Decl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class VarDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstDef : public BaseAst
{
public:
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstInitVal : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override {return 1;}
    int CalcVal() override {return subexp_->CalcVal();}
};

class ConstExp : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override {return 1;}
    int CalcVal() override {return subexp_->CalcVal();}
};

class VarDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class VarDef : public BaseAst
{
public:
    int cur_derivation_;
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class InitVal : public BaseAst
{
public:
    int isconst_=-1;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
            isconst_=subexp_->IsConst();
        return isconst_;
    }
    int CalcVal() override {return subexp_->CalcVal();}
};

class Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class Exp : public BaseAst
{
public:
    int isconst_=-1;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
            isconst_=subexp_->IsConst();
        return isconst_;
    }
    int CalcVal() override {return subexp_->CalcVal();}
};

class LOrExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class LAndExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class EqExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
            case 2:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class RelExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
            case 2:
            case 3:
            case 4:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class AddExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
            case 2:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class MulExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            switch (cur_derivation_)
            {
            case 0:
                isconst_=subexp1_->IsConst();
                break;
            
            case 1:
            case 2:
            case 3:
                isconst_=subexp1_->IsConst() && subexp2_->IsConst();
                break;
            }
        }
        return isconst_;
    }
    int CalcVal() override;
};

class UnaryExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            isconst_=subexp_->IsConst();
        }
        return isconst_;
    }
    int CalcVal() override;
};

class PrimaryExp : public BaseAst
{
public:
    int isconst_=-1;
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            isconst_=subexp_->IsConst();
        }
        return isconst_;
    }
    int CalcVal() override;
};

class LVal : public BaseAst
{
public:
    string ident_;
    int isconst_=-1;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override 
    {
        if (isconst_==-1)
        {
            isconst_=CurSymTab->is_const(ident_);
        }
        return isconst_;
    }
    int CalcVal() override {return CurSymTab->find(ident_).val_;}
    string GetIdent() override {return ident_;}
};

class Number : public BaseAst
{
public:
    string int_const_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override {return 1;}
    int CalcVal() override {return stoi(int_const_);};
};