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

void LOrExp::Print(string indent) const
{
    cout<<indent<<"LOrExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // LAndExp
        subexp1_->Print(curindent);
        break;

    case 1: // LOrExp OR LAndExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: ||\n";
        subexp2_->Print(curindent);
        break;
    
    default:
        LOG_ERROR("@LOrExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void LOrExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs, tpl, tpr;
    switch (cur_derivation_)
    {
    case 0: // LAndExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // LOrExp OR LAndExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        tpl=new_tempvar();
        tpr=new_tempvar();
        fs<<indent<<"%"<<tpl<<" = ne %"<<lhs<<", 0"<<endl;
        fs<<indent<<"%"<<tpr<<" = ne %"<<rhs<<", 0"<<endl;
        fs<<indent<<"%"<<dest<<" = or %"<<tpl<<", %"<<tpr<<endl;
        break;
    
    default:
        LOG_ERROR("@LOrExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void LAndExp::Print(string indent) const
{
    cout<<indent<<"LAndExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // EqExp
        subexp1_->Print(curindent);
        break;

    case 1: // LAndExp AND EqExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: &&\n";
        subexp2_->Print(curindent);
        break;
    
    default:
        LOG_ERROR("@LAndExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void LAndExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs, tpl, tpr;
    switch (cur_derivation_)
    {
    case 0: // EqExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // LAndExp AND EqExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        tpl=new_tempvar();
        tpr=new_tempvar();
        fs<<indent<<"%"<<tpl<<" = ne %"<<lhs<<", 0"<<endl;
        fs<<indent<<"%"<<tpr<<" = ne %"<<rhs<<", 0"<<endl;
        fs<<indent<<"%"<<dest<<" = and %"<<tpl<<", %"<<tpr<<endl;
        break;
    
    default:
        LOG_ERROR("@LAndExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void EqExp::Print(string indent) const
{
    cout<<indent<<"EqExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // RelExp
        subexp1_->Print(curindent);
        break;

    case 1: // EqExp EQQ RelExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: ==\n";
        subexp2_->Print(curindent);
        break;

    case 2: // EqExp NEQ RelExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: !=\n";
        subexp2_->Print(curindent);
        break;
    
    default:
        LOG_ERROR("@EqExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void EqExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs;
    switch (cur_derivation_)
    {
    case 0: // RelExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // EqExp EQQ RelExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = eq %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // EqExp NEQ RelExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = ne %"<<lhs<<", %"<<rhs<<endl;
        break;
    
    default:
        LOG_ERROR("@EqExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void RelExp::Print(string indent) const
{
    cout<<indent<<"RelExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // AddExp
        subexp1_->Print(curindent);
        break;

    case 1: // RelExp LT AddExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: <\n";
        subexp2_->Print(curindent);
        break;

    case 2: // RelExp GT AddExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: >\n";
        subexp2_->Print(curindent);
        break;
    
    case 3: // RelExp LEQ AddExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: <=\n";
        subexp2_->Print(curindent);
        break;

    case 4: // RelExp GEQ AddExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: >=\n";
        subexp2_->Print(curindent);
        break;
    
    default:
        LOG_ERROR("@RelExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void RelExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs;
    switch (cur_derivation_)
    {
    case 0: // AddExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // RelExp LT AddExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = lt %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // RelExp GT AddExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = gt %"<<lhs<<", %"<<rhs<<endl;
        break;
    
    case 3: // RelExp LEQ AddExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = le %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 4: // RelExp GEQ AddExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = ge %"<<lhs<<", %"<<rhs<<endl;
        break;
    
    default:
        LOG_ERROR("@RelExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void AddExp::Print(string indent) const
{
    cout<<indent<<"AddExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // MulExp
        subexp1_->Print(curindent);
        break;
    
    case 1: // AddExp PLUS MulExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: +\n";
        subexp2_->Print(curindent);
        break;

    case 2: // AddExp MINUS MulExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: -\n";
        subexp2_->Print(curindent);
        break;

    default:
        LOG_ERROR("@AddExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void AddExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs;
    switch (cur_derivation_)
    {
    case 0: // MulExp
        subexp1_->Dump(fs,indent,dest);
        break;
    
    case 1: // AddExp PLUS MulExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = add %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // AddExp MINUS MulExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = sub %"<<lhs<<", %"<<rhs<<endl;
        break;

    default:
        LOG_ERROR("@AddExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void MulExp::Print(string indent) const
{
    cout<<indent<<"MulExp {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // UnaryExp
        subexp1_->Print(curindent);
        break;
    
    case 1: // MulExp MULT UnaryExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: *\n";
        subexp2_->Print(curindent);
        break;

    case 2: // MulExp DIV UnaryExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: /\n";
        subexp2_->Print(curindent);
        break;

    case 3: // MulExp MOD UnaryExp
        subexp1_->Print(curindent);
        cout<<curindent<<"OP: %\n";
        subexp2_->Print(curindent);
        break;

    default:
        LOG_ERROR("@MulExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void MulExp::Dump(basic_ostream<char>& fs, string indent, int dest) const
{
    int lhs, rhs;
    switch (cur_derivation_)
    {
    case 0: // UnaryExp
        subexp1_->Dump(fs,indent,dest);
        break;
    
    case 1: // MulExp MULT UnaryExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = mul %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // MulExp DIV UnaryExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = div %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 3: // MulExp MOD UnaryExp
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = mod %"<<lhs<<", %"<<rhs<<endl;
        break;

    default:
        LOG_ERROR("@MulExp::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
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