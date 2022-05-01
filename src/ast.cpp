#include "include/ast.hpp"
using namespace std;

int temp_var_counter=0;
int new_tempvar()
{
    temp_var_counter++;
    return temp_var_counter;
}

void CompUnit::Print(string indent) const
{
    cout<<indent<<"CompUnit {\n";
    string curindent=indent+"|\t";
    funcdef_->Print(curindent);
    cout<<indent<<"}\n";
}

void CompUnit::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    funcdef_->Dump(fs,indent);
}

void FuncDef::Print(string indent) const
{
    cout<<indent<<"FuncDef {\n";
    string curindent=indent+"|\t";
    functype_->Print(curindent);
    cout<<curindent<<"name: "<<ident_<<";\n";
    block_->Print(curindent);
    cout<<indent<<"}\n";
}

void FuncDef::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    fs<<indent<<"fun @"<<ident_<<"()";
    functype_->Dump(fs,"");
    fs<<indent<<" {"<<endl;
    block_->Dump(fs,indent);
    fs<<indent<<"}"<<endl;
}

void FuncType::Print(string indent) const
{
    if (rettype_==DataType::INT)
        cout<<indent<<"FuncType: int;\n";
    else if (rettype_==DataType::VOID)
        cout<<indent<<"FuncType: void\n";
    else
        cout<<indent<<"FuncType: ???\n";
}

void FuncType::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    if (rettype_==DataType::INT)
        fs<<indent<<": i32";
    else
        fs<<indent<<"";
}

void Block::Print(string indent) const
{
    cout<<indent<<"Block {\n";
    string curindent=indent+"|\t";
    stmt_->Print(curindent);
    cout<<indent<<"}\n";
}

void Block::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    fs<<indent<<"\%entry:"<<endl;
    auto curindent=indent+"\t";
    stmt_->Dump(fs,curindent);
}

void Stmt::Print(string indent) const
{
    cout<<indent<<"Stmt {\n";
    string curindent=indent+"|\t";
    cout<<curindent<<"Return {\n";
    retv_->Print(curindent+"|\t");
    cout<<endl;
    cout<<curindent<<"}\n";
    cout<<indent<<"}\n";
}

void Stmt::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    // RETURN Exp ';'
    int tpvar=new_tempvar();
    retv_->Dump(fs,indent,tpvar);
    fs<<indent<<"ret %"<<tpvar<<endl;
}

void Exp::Print(string indent) const
{
    cout<<indent<<"Exp {\n";
    string curindent=indent+"|\t";
    subexp_->Print(curindent);
    cout<<indent<<"}\n";
}

void Exp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    subexp_->Dump(fs,indent,dest);
}

void UnaryExp::Print(string indent) const
{
    cout<<indent<<"UnaryExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // PLUS UnaryExp
        cout<<curindent<<"OP: +\n";
        break;
    
    case 1: // MINUS UnaryExp
        cout<<curindent<<"OP: -\n";
        break;

    case 2: // NOT UnaryExp
        cout<<curindent<<"OP: !\n";
        break;
    
    case 3: // PrimaryExp
        break;

    default:
        LOG_ERROR("@UnaryExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    subexp_->Print(curindent);
    cout<<indent<<"}\n";
}

void UnaryExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int tpvar;
    switch (cur_derivation_)
    {
    case 0: // PLUS UnaryExp
        subexp_->Dump(fs,indent,dest);
        break;
    
    case 1: // MINUS UnaryExp
        tpvar=new_tempvar();
        subexp_->Dump(fs,indent,tpvar);
        fs<<indent<<"%"<<dest<<" = sub 0, %"<<tpvar<<endl;
        break;

    case 2: // NOT UnaryExp
        tpvar=new_tempvar();
        subexp_->Dump(fs,indent,tpvar);
        fs<<indent<<"%"<<dest<<" = eq 0, %"<<tpvar<<endl;
        break;
    
    case 3: // PrimaryExp
        subexp_->Dump(fs,indent,dest);
        break;

    default:
        LOG_ERROR("@UnaryExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void PrimaryExp::Print(string indent) const
{
    cout<<indent<<"PrimaryExp: {\n";
    string curindent=indent+"|\t";
    subexp_->Print(curindent);
    cout<<indent<<"}\n";
}

void PrimaryExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    subexp_->Dump(fs,indent,dest);
}

void Number::Print(string indent) const
{
    cout<<indent<<"Number: {\n";
    cout<<indent<<"|\t"<<int_const_<<endl;
    cout<<indent<<"}\n";
}

void Number::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    fs<<indent<<"%"<<dest<<" = add 0, "<<int_const_<<endl;
}