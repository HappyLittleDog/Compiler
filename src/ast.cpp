#include "include/ast.hpp"
using namespace std;

SymTab* CurSymTab = NULL;
int temp_var_counter=0;
int new_tempvar()
{
    temp_var_counter++;
    return temp_var_counter;
}

int src_var_counter=0;
int new_srcvar()
{
    src_var_counter++;
    return src_var_counter;
}

int entry_counter=0;
int new_entry()
{
    entry_counter++;
    return entry_counter;
}

void CompUnit::Print(string indent)
{
    cout<<indent<<"CompUnit {\n";
    string curindent=indent+"|\t";
    funcdef_->Print(curindent);
    cout<<indent<<"}\n";
}

void CompUnit::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    funcdef_->Dump(fs,indent);
}

void FuncDef::Print(string indent)
{
    cout<<indent<<"FuncDef {\n";
    string curindent=indent+"|\t";
    functype_->Print(curindent);
    cout<<curindent<<"name: "<<ident_<<";\n";
    block_->Print(curindent);
    cout<<indent<<"}\n";
}

void FuncDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<indent<<"fun @"<<ident_<<"()";
    functype_->Dump(fs,"");
    fs<<indent<<" {"<<endl;
    fs<<indent<<"\%entry_"<<new_entry()<<":"<<endl;
    block_->Dump(fs,indent);
    fs<<indent<<"}"<<endl;
}

void FuncType::Print(string indent)
{
    if (rettype_==DataType::INT)
        cout<<indent<<"FuncType: int;\n";
    else if (rettype_==DataType::VOID)
        cout<<indent<<"FuncType: void\n";
    else
        cout<<indent<<"FuncType: ???\n";
}

void FuncType::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (rettype_==DataType::INT)
        fs<<indent<<": i32";
    else
        fs<<indent<<"";
}

void Block::Print(string indent)
{
    cout<<indent<<"Block {\n";
    string curindent=indent+"|\t";
    items_->Print(curindent);
    cout<<indent<<"}\n";
}

void Block::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    SymTab_=new SymTab();
    SymTab_->pred_=CurSymTab;
    CurSymTab=SymTab_;
    items_->Dump(fs,indent);
    CurSymTab=SymTab_->pred_;
}

void BlockItems::Print(string indent)
{
    for (int i=0; i<items_.size(); i++)
    {
        items_[i]->Print(indent);
    }
}

void BlockItems::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    for (int i=0; i<items_.size(); i++)
    {
        items_[i]->Dump(fs,indent);
    }
}

void BlockItem::Print(string indent)
{
    item_->Print(indent);
}

void BlockItem::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    item_->Dump(fs,indent);
}

void Decl::Print(string indent)
{
    item_->Print(indent);
}

void Decl::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    item_->Dump(fs,indent);
}

void ConstDecl::Print(string indent)
{
    cout<<indent<<"ConstDecl {\n";
    string curindent=indent+"|\t";
    cout<<curindent<<"CONST INT\n";
    item_->Print(curindent);
    cout<<indent<<"}\n";
}

void ConstDecl::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    item_->Dump(fs,indent);
}

void VarDecl::Print(string indent)
{
    cout<<indent<<"VarDecl {\n";
    string curindent=indent+"|\t";
    cout<<curindent<<"INT\n";
    item_->Print(curindent);
    cout<<indent<<"}\n";
}

void VarDecl::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    item_->Dump(fs,indent);
}

void ConstDefs::Print(string indent)
{
    for (int i=0; i<defs_.size(); i++)
    {
        defs_[i]->Print(indent);
    }
}

void ConstDefs::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    for (int i=0; i<defs_.size(); i++)
    {
        defs_[i]->Dump(fs,indent);
    }
}

void ConstDef::Print(string indent)
{
    cout<<indent<<ident_<<" := "<<initval_->CalcVal()<<endl;
}

void ConstDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    CurSymTab->insert_const(ident_, initval_->CalcVal());
}

void ConstInitVal::Print(string indent)
{
    return;
}

void ConstInitVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    return;
}

void ConstExp::Print(string indent)
{
    return;
}

void ConstExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    return;
}

void VarDefs::Print(string indent)
{
    for (int i=0; i<defs_.size(); i++)
    {
        defs_[i]->Print(indent);
    }
}

void VarDefs::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    for (int i=0; i<defs_.size(); i++)
    {
        defs_[i]->Dump(fs,indent);
    }
}

void VarDef::Print(string indent)
{
    if (cur_derivation_==0)
        cout<<indent<<ident_<<" := \n";
    else
    {
        cout<<indent<<ident_<<" := {\n";
        string curindent=indent+"|\t";
        initval_->Print(curindent);
        cout<<indent<<"}\n";
    }
}

void VarDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    CurSymTab->insert_var(ident_);
    int cur=CurSymTab->find(ident_).val_;
    fs<<indent<<"@VAR_"<<cur<<" = alloc i32 //! w.r.t. symbol "<<ident_<<endl;
    if (cur_derivation_==1)
    {
        if (initval_->IsConst())
        {
            int val=initval_->CalcVal();
            fs<<indent<<"store "<<val<<", @VAR_"<<cur<<endl;
        }
        else
        {
            int temp=new_tempvar();
            initval_->Dump(fs,indent,temp);
            fs<<indent<<"store %"<<temp<<", @VAR_"<<cur<<endl;
        }
    }
}

void InitVal::Print(string indent)
{
    if (IsConst())
        cout<<indent<<CalcVal()<<endl;
    else
        subexp_->Print(indent);
}

void InitVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    subexp_->Dump(fs,indent,dest);
}

void Stmt::Print(string indent)
{
    cout<<indent<<"Stmt {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // RETURN Exp ';'
        cout<<curindent<<"Return {\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<"}\n";
        break;
    
    case 1: // LVal EQ Exp ';'
        cout<<curindent<<subexp1_->GetIdent()<<" = {\n";
        subexp2_->Print(curindent+"|\t");
        cout<<curindent<<"}\n";
        break;
    
    case 2: // ';'
        cout<<curindent<<";\n";
        break;

    case 3: // Exp ';'
    case 4: // Block
        subexp1_->Print(curindent);
        break;

    default:
        LOG_ERROR("@Stmt::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void Stmt::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    int tpvar;
    switch (cur_derivation_)
    {
    case 0: // RETURN Exp ';'
        tpvar=new_tempvar();
        subexp1_->Dump(fs,indent,tpvar);
        fs<<indent<<"ret %"<<tpvar<<endl;
        break;
    
    case 1: // LVal EQ Exp ';'
        if (subexp2_->IsConst())
            fs<<indent<<"store "<<subexp2_->CalcVal()<<", @VAR_"<<CurSymTab->find(subexp1_->GetIdent()).val_<<endl;
        else
        {
            tpvar=new_tempvar();
            subexp2_->Dump(fs,indent,tpvar);
            fs<<indent<<"store %"<<tpvar<<", @VAR_"<<CurSymTab->find(subexp1_->GetIdent()).val_<<endl;
        }
        break;
    
    case 2: // ';'
        break;
    
    case 3: // Exp ';'
        tpvar=new_tempvar();
        subexp1_->Dump(fs,indent,tpvar);
        break;
    
    case 4: // Block
        subexp1_->Dump(fs,indent,dest);
        break;

    default:
        LOG_ERROR("@Stmt::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void Exp::Print(string indent)
{
    cout<<indent<<"Exp {\n";
    string curindent=indent+"|\t";
    subexp_->Print(curindent);
    cout<<indent<<"}\n";
}

void Exp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
    subexp_->Dump(fs,indent,dest);
}

void LOrExp::Print(string indent)
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

void LOrExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int LOrExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // LAndExp
        return subexp1_->CalcVal();

    case 1: // LOrExp OR LAndExp
        return subexp1_->CalcVal() || subexp2_->CalcVal();
    
    default:
        LOG_ERROR("@LOrExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void LAndExp::Print(string indent)
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

void LAndExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int LAndExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // EqExp
        return subexp1_->CalcVal();

    case 1: // LAndExp AND EqExp
        return subexp1_->CalcVal() && subexp2_->CalcVal();
    
    default:
        LOG_ERROR("@LAndExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void EqExp::Print(string indent)
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

void EqExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int EqExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // RelExp
        return subexp1_->CalcVal();

    case 1: // EqExp EQQ RelExp
        return subexp1_->CalcVal() == subexp2_->CalcVal();

    case 2: // EqExp NEQ RelExp
        return subexp1_->CalcVal() != subexp2_->CalcVal();
    
    default:
        LOG_ERROR("@EqExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void RelExp::Print(string indent)
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

void RelExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int RelExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // AddExp
        return subexp1_->CalcVal();

    case 1: // RelExp LT AddExp
        return subexp1_->CalcVal() < subexp2_->CalcVal();

    case 2: // RelExp GT AddExp
        return subexp1_->CalcVal() > subexp2_->CalcVal();
    
    case 3: // RelExp LEQ AddExp
        return subexp1_->CalcVal() <= subexp2_->CalcVal();

    case 4: // RelExp GEQ AddExp
        return subexp1_->CalcVal() >= subexp2_->CalcVal();
    
    default:
        LOG_ERROR("@RelExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void AddExp::Print(string indent)
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

void AddExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int AddExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // MulExp
        return subexp1_->CalcVal();
    
    case 1: // AddExp PLUS MulExp
        return subexp1_->CalcVal() + subexp2_->CalcVal();

    case 2: // AddExp MINUS MulExp
        return subexp1_->CalcVal() - subexp2_->CalcVal();

    default:
        LOG_ERROR("@AddExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void MulExp::Print(string indent)
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

void MulExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int MulExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // UnaryExp
        return subexp1_->CalcVal();
    
    case 1: // MulExp MULT UnaryExp
        return subexp1_->CalcVal() * subexp2_->CalcVal();

    case 2: // MulExp DIV UnaryExp
        return subexp1_->CalcVal() / subexp2_->CalcVal();

    case 3: // MulExp MOD UnaryExp
        return subexp1_->CalcVal() % subexp2_->CalcVal();

    default:
        LOG_ERROR("@MulExp::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void UnaryExp::Print(string indent)
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

void UnaryExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
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

int UnaryExp::CalcVal()
{
    switch (cur_derivation_)
    {
    case 0: // PLUS UnaryExp
        return subexp_->CalcVal();
    
    case 1: // MINUS UnaryExp
        return (-1)*subexp_->CalcVal();

    case 2: // NOT UnaryExp
        return !subexp_->CalcVal();
    
    case 3: // PrimaryExp
        return subexp_->CalcVal();

    default:
        LOG_ERROR("@UnaryExp::calcval: Unrecognized cur_derivation_=%d",cur_derivation_);
        return 0;
    }
}

void PrimaryExp::Print(string indent)
{
    cout<<indent<<"PrimaryExp: {\n";
    string curindent=indent+"|\t";
    subexp_->Print(curindent);
    cout<<indent<<"}\n";
}

void PrimaryExp::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (IsConst())
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
    subexp_->Dump(fs,indent,dest);
}

int PrimaryExp::CalcVal()
{
    return subexp_->CalcVal();
}

void LVal::Print(string indent)
{
    cout<<indent<<ident_<<endl;
}

void LVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<indent<<"%"<<dest<<" = load @VAR_"<<CurSymTab->find(ident_).val_<<endl;
}

void Number::Print(string indent)
{
    cout<<indent<<int_const_<<endl;
}

void Number::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<indent<<"%"<<dest<<" = add 0, "<<int_const_<<endl;
}