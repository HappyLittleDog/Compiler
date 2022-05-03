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
        LOG_ERROR("@ConstSymTab::get_val: %s not found.",symbol.c_str());
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
        LOG_ERROR("@ConstSymTab::is_const: %s not found.",symbol.c_str());
        return false;
    }
};
extern SymTab* CurSymTab; 

class BaseAst
{
public:
    virtual ~BaseAst() = default;
    virtual void Print(string indent="") const = 0;
    virtual void Scan() = 0; // Scan the AST to build the symtab.
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
    void Scan() override; // TODO
};

class FuncDef : public BaseAst
{
public:
    unique_ptr<BaseAst> functype_;
    string ident_;
    unique_ptr<BaseAst> block_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {block_->Scan();}
};

class FuncType : public BaseAst
{
public:
    DataType rettype_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {return;}
};

class Block : public BaseAst
{
public:
    unique_ptr<BaseAst> items_;
    SymTab* SymTab_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override; // TODO
};

class BlockItems : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > items_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override
    {
        for (int i=0;i<items_.size();i++)
            items_[i]->Scan();
    }
};

class BlockItem : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {item_->Scan();}
};

class Decl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {item_->Scan();}
};

class ConstDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {item_->Scan();}
};

class VarDecl : public BaseAst
{
public:
    unique_ptr<BaseAst> item_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override {item_->Scan();}
};

class ConstDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override
    {
        for (int i=0;i<defs_.size();i++)
            defs_[i]->Scan();
    }
};

class ConstDef : public BaseAst
{
public:
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override; // TODO
};

class ConstInitVal : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return subexp_->CalcVal();}
    void Scan() override {subexp_->Scan();}
};

class ConstExp : public BaseAst
{
public:
    unique_ptr<BaseAst> subexp_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return subexp_->CalcVal();}
    void Scan() override {subexp_->Scan();}
};

class VarDefs : public BaseAst
{
public:
    vector<unique_ptr<BaseAst> > defs_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override
    {
        for (int i=0;i<defs_.size();i++)
            defs_[i]->Scan();
    }
};

class VarDef : public BaseAst
{
public:
    int cur_derivation_;
    string ident_;
    unique_ptr<BaseAst> initval_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override; // TODO
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
    void Scan() override 
    {
        subexp_->Scan();
        isconst_=subexp_->IsConst();
    }
};

class Stmt : public BaseAst
{
public:
    int cur_derivation_;
    unique_ptr<BaseAst> subexp1_;
    unique_ptr<BaseAst> subexp2_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    void Scan() override; // TODO
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
    void Scan() override 
    {
        subexp_->Scan();
        isconst_=subexp_->IsConst();
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
        case 2:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
        case 2:
        case 3:
        case 4:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
        case 2:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        switch (cur_derivation_)
        {
        case 0:
            subexp1_->Scan();
            isconst_=subexp1_->IsConst();
            break;
        
        case 1:
        case 2:
        case 3:
            subexp1_->Scan();
            subexp2_->Scan();
            isconst_=subexp1_->IsConst() && subexp2_->IsConst();
            break;
        
        default:
            LOG_ERROR("@**exp::scan: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
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
    void Scan() override
    {
        subexp_->Scan();
        isconst_=subexp_->IsConst();
    }
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
    void Scan() override
    {
        subexp_->Scan();
        isconst_=subexp_->IsConst();
    }
};

class LVal : public BaseAst
{
public:
    string ident_;
    bool isconst_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return isconst_;}
    int CalcVal() const override {return CurSymTab->find(ident_).val_;}
    string GetIdent() const override {return ident_;}
    void Scan() override; // TODO only look up in the symtab. do NOT insert!
};

class Number : public BaseAst
{
public:
    string int_const_;
    void Print(string indent="") const override;
    void Dump(basic_ostream<char>& fs, string indent="", int dest=-1) const override;
    bool IsConst() const override {return true;}
    int CalcVal() const override {return stoi(int_const_);};
    void Scan() override {return;}
};