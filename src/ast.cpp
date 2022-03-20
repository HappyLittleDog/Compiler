#include "ast.hpp"
using namespace std;

void CompUnit::Print(string indent) const
{
    cout<<indent<<"CompUnit {\n";
    string curindent=indent+"|\t";
    funcdef_->Print(curindent);
    cout<<indent<<"}\n";
}

void CompUnit::Dump(fstream& fs, string indent) const
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

void FuncDef::Dump(fstream& fs, string indent) const
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

void FuncType::Dump(fstream& fs, string indent) const
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

void Block::Dump(fstream& fs, string indent) const
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

void Stmt::Dump(fstream& fs, string indent) const
{
    fs<<indent<<"ret ";
    retv_->Dump(fs,"");
    fs<<endl;
}

void Number::Print(string indent) const
{
    cout<<indent<<int_const_;
}

void Number::Dump(fstream& fs, string indent) const
{
    fs<<indent<<int_const_;
}