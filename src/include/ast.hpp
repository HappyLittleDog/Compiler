#pragma once
#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <fstream>
#include <deque>
#include <deque>
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
int new_tempvar();

struct SymTabEntry
{
    bool isconst_;
    int val_; // val for const, @[pos] for var
    deque<int> size_;
    SymTabEntry(bool isconst, int val): isconst_(isconst), val_(val){};
    SymTabEntry(bool isconst, int val, const deque<int>& size): isconst_(isconst), val_(val), size_(size){};
};


class SymTab
{
    map<string, SymTabEntry> nt;
public:
    SymTab* pred_;
    SymTab() = default;
    void insert_const(string symbol, int val, const deque<int> size=deque<int>())
    {
        if (size.empty()) // const var
        {
            auto it = nt.insert(make_pair(symbol, SymTabEntry(true, val, size)));
            if (!it.second)
            {
                LOG_ERROR("@SymTab::insert_const: Insert (%s, %d) failed!\n(%s, <%d, %d>) already exists.", symbol.c_str(), val, symbol.c_str(), nt.find(symbol)->second.isconst_, nt.find(symbol)->second.val_);
            }
        }
        else // const array
        {
            int pos=new_srcvar();
            auto it = nt.insert(make_pair(symbol, SymTabEntry(false, pos, size))); // insert as "false" is intended to make IR gen easier.
            if (!it.second)
            {
                LOG_ERROR("@SymTab::insert_const: Insert (%s, %d) failed!\n(%s, <%d, %d>) already exists.", symbol.c_str(), val, symbol.c_str(), nt.find(symbol)->second.isconst_, nt.find(symbol)->second.val_);
            }
        }
    }

    void insert_var(string symbol, const deque<int> size=deque<int>())
    {
        int pos=new_srcvar();
        auto it = nt.insert(make_pair(symbol, SymTabEntry(false, pos, size)));
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
    virtual void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) {LOG_ERROR("@FuncBlockDump: Unexpected function call!");} // used for func block ONLY!
    virtual void ReAllocateFParams(basic_ostream<char>& fs, string indent) {LOG_ERROR("@ReAllocateFParams: Unexpected function call!");}
    virtual deque<int> GetArraySize() {LOG_ERROR("@GetArraySize: Unexpected function call!"); return deque<int>();} //used for ArraySize ONLY!
    virtual deque<int> DumpArrayIndex(basic_ostream<char>& fs, string indent="") {LOG_ERROR("@DumpArrayIndex: Unexpected function call!"); return deque<int>();} //used for ArrayIndex ONLY!
    virtual deque<int> GetConstInitVals() {LOG_ERROR("@GetConstInitVals: Unexpected function call!"); return deque<int>();} //used for ConstInitVal ONLY!
    virtual deque<int> DumpInitVals(basic_ostream<char>& fs, string indent="") {LOG_ERROR("@DumpInitVals: Unexpected function call!"); return deque<int>();} //used for InitVal ONLY!
    virtual int GetDerivation() {LOG_ERROR("@GetDerivation: Unexpected function call!"); return 0;}
    virtual void DumpParamDecl(basic_ostream<char>& fs) {}
};

class CompUnits : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > items_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class CompUnit : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

// class FuncDefs : public BaseAst
// {
// public:
//     deque<unique_ptr<BaseAst> > funcdefs_;
//     void Print(string indent="") override;
//     void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
// };

class FuncDef : public BaseAst
{
public:
    int functype_; // 0: void, 1: int
    string ident_;
    shared_ptr<BaseAst> params_=nullptr;
    unique_ptr<BaseAst> block_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) override;
};

class FuncFParams : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > params_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;       // output IR
    void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) override; // insert symbol into symtab
    void ReAllocateFParams(basic_ostream<char>& fs, string indent) override;
};

class FuncFParam : public BaseAst
{
public:
    int cur_derivation_;
    int type_;
    string ident_;
    unique_ptr<BaseAst> size_=nullptr;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) override;
    void ReAllocateFParams(basic_ostream<char>& fs, string indent) override;
    void DumpParamDecl(basic_ostream<char>& fs) override;
};

class FuncRParams : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > params_;
    deque<int> param_pos_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) override;
};

class Block : public BaseAst
{
public:
    unique_ptr<BaseAst> items_;
    shared_ptr<BaseAst> params_=nullptr;
    SymTab* SymTab_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    void FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt) override;
};

class BlockItems : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > items_;
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
    int type_;
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class VarDecl : public BaseAst
{
public:
    int type_;
    unique_ptr<BaseAst> item_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstDefs : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ConstDef : public BaseAst
{
public:
    string ident_;
    unique_ptr<BaseAst> size_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class ArraySize : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > size_; // Guaranteed not to be NULL
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    deque<int> GetArraySize() override
    {
        deque<int> tp;
        for (int i=0;i<size_.size();i++)
        {
            tp.push_back(size_[i]->CalcVal());
        }
        return tp;
    }
};

class ConstInitVal : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    int IsConst() override {return 1;}
    int GetDerivation() override {return cur_derivation_;}
    int CalcVal() override {assert(cur_derivation_==0); return subexp_->CalcVal();}
    deque<int> GetConstInitVals() override
    {
        assert(cur_derivation_==1);
        return subexp_->GetConstInitVals();
    }
};

class ConstInitVals : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > exps_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    deque<int> GetConstInitVals() override
    {
        deque<int> tp;
        for (int i=0;i<exps_.size();i++)
            tp.push_back(exps_[i]->CalcVal());
        return tp;
    }
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
    deque<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class VarDef : public BaseAst
{
public:
    int cur_derivation_;
    string ident_;
    unique_ptr<BaseAst> size_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class InitVal : public BaseAst
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
            isconst_=subexp_->IsConst();
        return isconst_;
    }
    int GetDerivation() override {return cur_derivation_;};
    int CalcVal() override {assert(cur_derivation_==0); return subexp_->CalcVal();}
    deque<int> GetConstInitVals() override
    {
        assert(cur_derivation_==1);
        return subexp_->GetConstInitVals();
    }
    deque<int> DumpInitVals(basic_ostream<char>& fs, string indent="") override
    {
        deque<int> tp;
        switch (cur_derivation_)
        {
        case 0:
            tp.push_back(new_tempvar());
            subexp_->Dump(fs,indent,tp[0]);
            break;

        case 1:
            return subexp_->DumpInitVals(fs,indent);
            break;
        
        default:
            LOG_ERROR("@InitVal::DumpInitVals: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
        return tp;
    }
};

class InitVals : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > exps_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    deque<int> GetConstInitVals() override
    {
        deque<int> tp;
        for (int i=0;i<exps_.size();i++)
            tp.push_back(exps_[i]->CalcVal());
        return tp;
    }
    deque<int> DumpInitVals(basic_ostream<char>& fs, string indent="") override
    {
        deque<int> tp;
        for (int i=0;i<exps_.size();i++)
        {
            tp.push_back(new_tempvar());
            exps_[i]->Dump(fs,indent,tp[i]);
        }
        return tp;
    }
};

class Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp_ = NULL;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class Closed_If_Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_ = NULL;
    unique_ptr<BaseAst> subexp2_ = NULL;
    unique_ptr<BaseAst> subexp3_ = NULL;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
};

class Open_If_Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_ = NULL;
    unique_ptr<BaseAst> subexp2_ = NULL;
    unique_ptr<BaseAst> subexp3_ = NULL;
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
    string ident_; // used for function call
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
    unique_ptr<BaseAst> ndx_;
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
    deque<int> DumpArrayIndex(basic_ostream<char>& fs, string indent="") override
    {
        return ndx_->DumpArrayIndex(fs,indent);
    }
};

class ArrayIndex : public BaseAst
{
public:
    deque<unique_ptr<BaseAst> > ndx_;
    void Print(string indent="") override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) override;
    deque<int> DumpArrayIndex(basic_ostream<char>& fs, string indent="") override
    {
        deque<int> tp;
        for (int i=0;i<ndx_.size();i++)
        {
            tp.push_back(new_tempvar());
            ndx_[i]->Dump(fs,indent,tp[i]);
        }
        return tp;
    }
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
