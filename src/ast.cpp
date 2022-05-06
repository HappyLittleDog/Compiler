#include "include/ast.hpp"
using namespace std;

SymTab* CurSymTab = new SymTab();
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

bool return_flag=false;
int cur_while_exp=-1;
int cur_while_end=-1;
bool global_var=false;

string libsysy="decl @getint(): i32\ndecl @getch(): i32\ndecl @getarray(*i32): i32\ndecl @putint(i32)\ndecl @putch(i32)\ndecl @putarray(i32, *i32)\ndecl @starttime()\ndecl @stoptime()\n";

void CompUnits::Print(string indent)
{
    for (int i=0;i<items_.size();i++)
        items_[i]->Print(indent);
}

void CompUnits::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<libsysy<<endl;
    for (int i=0;i<items_.size();i++)
        items_[i]->Dump(fs,indent);
}

void CompUnit::Print(string indent)
{
    cout<<indent<<"CompUnit {\n";
    string curindent=indent+"|\t";
    item_->Print(curindent);
    cout<<indent<<"}\n";
}

void CompUnit::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    global_var=true;
    item_->Dump(fs,indent);
}

// void FuncDefs::Print(string indent)
// {
//     for (int i=0;i<funcdefs_.size();i++)
//         funcdefs_[i]->Print(indent);
// }

// void FuncDefs::Dump(basic_ostream<char>& fs, string indent, int dest)
// {
//     global_var=false;
//     for (int i=0;i<funcdefs_.size();i++)
//     {
//         funcdefs_[i]->Dump(fs,indent);
//         fs<<endl;
//     }
// }

void FuncDef::Print(string indent)
{
    cout<<indent<<"FuncDef {\n";
    string curindent=indent+"|\t";
    switch (functype_)
    {
    case 0: // void
        cout<<curindent<<"VOID"<<endl;
        break;
    case 1: // int
        cout<<curindent<<"INT"<<endl;
        break;
    default:
        break;
    }
    cout<<curindent<<"name: "<<ident_<<";\n";
    block_->Print(curindent);
    cout<<indent<<"}\n";
}

void FuncDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    global_var=false;
    block_->FuncBlockDump(fs,indent,this);
    fs<<indent<<"}"<<endl;
}

void FuncDef::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    fs<<indent<<"fun @"<<ident_<<"(";
    if (params_!=nullptr)
        params_->Dump(fs,indent);
    fs<<")";
    switch (functype_)
    {
    case 0: // void
        fs<<"";
        break;
    case 1: // int
        fs<<indent<<": i32";
        break;
    default:
        break;
    }
    fs<<indent<<" {"<<endl;
    fs<<indent<<"\%entry_"<<new_entry()<<":"<<endl;
}

void FuncFParams::Print(string indent)
{
    cout<<indent<<"PARAMS: ("<<endl;
    string curindent=indent+"|\t";
    for (int i=0;i<params_.size();i++)
        params_[i]->Print(curindent);
    cout<<indent<<")"<<endl;
}

void FuncFParams::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (params_.size()==0)
        return;
    else if (params_.size()==1)
        params_[0]->Dump(fs,"");
    else
    {
        params_[0]->Dump(fs,"");
        for (int i=1;i<params_.size();i++)
        {
            params_[i]->Dump(fs,", ");
        }
    }
}

void FuncFParams::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    for (int i=0;i<params_.size();i++)
    {
        params_[i]->FuncBlockDump(fs,indent,NULL);
    }
}

void FuncFParams::ReAllocateFParams(basic_ostream<char>& fs, string indent)
{
    for (int i=0;i<params_.size();i++)
    {
        params_[i]->ReAllocateFParams(fs,indent);
    }
}

void FuncFParam::Print(string indent)
{
    cout<<indent;
    switch (type_)
    {
    case 1:
        cout<<"INT\t";
        break;
    
    default:
        break;
    }
    cout<<ident_<<endl;
}

void FuncFParam::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<indent<<"@PARAM_"<<CurSymTab->find(ident_).val_<<": ";
    switch (type_)
    {
    case 1:
        fs<<"i32";
        break;
    
    default:
        LOG_ERROR("@FuncFParam::Dump: unexpected type_=%d",type_);
        break;
    }
}

void FuncFParam::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    CurSymTab->insert_var(ident_);
}

void FuncFParam::ReAllocateFParams(basic_ostream<char>& fs, string indent)
{
    int pos=CurSymTab->find(ident_).val_;
    fs<<indent<<"@VAR_"<<pos<<" = alloc i32"<<endl;
    fs<<indent<<"store @PARAM_"<<pos<<", @VAR_"<<pos<<endl;
}

void FuncRParams::Print(string indent)
{
    for (int i=0;i<params_.size();i++)
        params_[i]->Print(indent);
}

void FuncRParams::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (param_pos_.size()==0)
        return;
    else if (param_pos_.size()==1)
    {
        fs<<"%"<<param_pos_[0];
    }
    else
    {
        fs<<"%"<<param_pos_[0];
        for (int i=1;i<param_pos_.size();i++)
        {
            fs<<", %"<<param_pos_[i];
        }
    }
}

void FuncRParams::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    for (int i=0;i<params_.size();i++)
    {
        int tpvar=new_tempvar();
        param_pos_.push_back(tpvar);
        params_[i]->Dump(fs,indent,tpvar);
    }
}

void Block::Print(string indent)
{
    if (params_!=nullptr)
        params_->Print(indent);
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

    // if (params_!=nullptr)
    // {
    //     params_->Dump(fs,indent);
    // }
    items_->Dump(fs,indent);
    CurSymTab=SymTab_->pred_;
}

void Block::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    SymTab_=new SymTab();
    SymTab_->pred_=CurSymTab;
    CurSymTab=SymTab_;

    if (params_!=nullptr)
    {
        params_->FuncBlockDump(fs,indent,NULL);
    }
    pt->FuncBlockDump(fs,indent,NULL);
    if (params_!=nullptr)
    {
        params_->ReAllocateFParams(fs,indent+"\t");
    }
    return_flag=false;
    items_->Dump(fs,indent+"\t");
    if (return_flag==false)
        fs<<indent<<"\tret"<<endl;
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
    return_flag=false;
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
    if (global_var)
    {
        switch (cur_derivation_)
        {
        case 0:
            fs<<indent<<"global @VAR_"<<cur<<" = alloc i32, zeroinit //! w.r.t. symbol "<<ident_<<endl;
            break;
        
        case 1:
            fs<<indent<<"global @VAR_"<<cur<<" = alloc i32, "<<initval_->CalcVal()<<" //! w.r.t. symbol "<<ident_<<endl;
            break;

        default:
            LOG_ERROR("@Vardef::Dump::global_var: unexpected cur_derivation=%d",cur_derivation_);
            break;
        }
    }
    else
    {
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
    subexp_->Print(indent);
}

void Stmt::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (!return_flag)
        subexp_->Dump(fs,indent);
}

void Closed_If_Stmt::Print(string indent)
{
    cout<<indent<<"Closed_If_Stmt {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // RETURN Exp ';'
        if (subexp1_!=nullptr)
        {
            cout<<curindent<<"Return {\n";
            subexp1_->Print(curindent+"|\t");
            cout<<curindent<<"}\n";
        }
        else
            cout<<curindent<<"Return\n";
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

    case 5: // IF '(' Exp ')' Closed_If_Stmt ELSE Closed_If_Stmt
        cout<<curindent<<"IF (\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<")\n";
        subexp2_->Print(curindent+"|\t");
        cout<<curindent<<"ELSE\n";
        subexp3_->Print(curindent+"|\t");
        break;
    
    case 6: // WHILE '(' Exp ')' Stmt
        cout<<curindent<<"WHILE (\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<")\n";
        cout<<curindent<<"DO\n";
        subexp2_->Print(curindent+"|\t");
        break;

    case 7: // BREAK ';'
        cout<<curindent<<"BREAK\n";
        break;
    
    case 8: // CONTINUE ';'
        cout<<curindent<<"CONTINUE\n";
        break;

    default:
        LOG_ERROR("@Closed_If_Stmt::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void Closed_If_Stmt::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    int tpvar, entry1, entry2, entry3;
    int prev_cur_while_exp, prev_cur_while_end;
    switch (cur_derivation_)
    {
    case 0: // RETURN Exp ';'
        if (subexp1_!=nullptr)
        {
            tpvar=new_tempvar();
            subexp1_->Dump(fs,indent,tpvar);
            fs<<indent<<"ret %"<<tpvar<<endl;
        }
        else
            fs<<indent<<"ret"<<endl;
        return_flag=true;
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
        subexp1_->Dump(fs,indent); // i.e a stmt only contains an expression
        break;
    
    case 4: // Block
        subexp1_->Dump(fs,indent,dest);
        break;

    case 5: // IF '(' Exp ')' Closed_If_Stmt ELSE Closed_If_Stmt
        tpvar=new_tempvar();
        entry1=new_entry();
        entry2=new_entry();
        entry3=new_entry();
        subexp1_->Dump(fs,indent,tpvar);
        fs<<"\tbr %"<<tpvar<<", \%then_"<<entry1<<", \%else_"<<entry2<<endl;
        fs<<endl<<"//! IF branch of the if stmt"<<endl;
        fs<<"\%then_"<<entry1<<":"<<endl;
        return_flag=false;
        subexp2_->Dump(fs,indent);
        if (return_flag==false)
            fs<<"\tjump \%end_"<<entry3<<endl;
        return_flag=false;

        fs<<endl<<"//! ELSE branch of the if stmt"<<endl;
        fs<<"\%else_"<<entry2<<":"<<endl;
        return_flag=false;
        subexp3_->Dump(fs,indent);
        if (return_flag==false)
            fs<<"\tjump \%end_"<<entry3<<endl;
        return_flag=false;

        fs<<endl<<"//! end of the if stmt"<<endl;
        fs<<"\%end_"<<entry3<<":"<<endl;
        break;
    
    case 6: // WHILE '(' Exp ')' Stmt
        tpvar=new_tempvar();
        entry1=new_entry();
        entry2=new_entry();
        entry3=new_entry();
        prev_cur_while_exp=cur_while_exp;
        prev_cur_while_end=cur_while_end;
        cur_while_exp=entry1;
        cur_while_end=entry3;
        fs<<indent<<"jump \%while_exp_"<<entry1<<endl;

        fs<<endl<<"\%while_exp_"<<entry1<<":"<<endl;
        subexp1_->Dump(fs,indent,tpvar);
        fs<<indent<<"br %"<<tpvar<<", \%while_loop_"<<entry2<<", \%while_end_"<<entry3<<endl;

        fs<<endl<<"\%while_loop_"<<entry2<<":"<<endl;
        return_flag=false;
        subexp2_->Dump(fs,indent,tpvar);
        if (return_flag==false)
            fs<<indent<<"jump \%while_exp_"<<entry1<<endl;
        return_flag=false;

        fs<<endl<<"\%while_end_"<<entry3<<":"<<endl;

        cur_while_exp=prev_cur_while_exp;
        cur_while_end=prev_cur_while_end;
        break;
    
    case 7: // BREAK ';'
        return_flag=true;
        fs<<indent<<"jump \%while_end_"<<cur_while_end<<endl;
        break;
    
    case 8: // CONTINUE ';'
        return_flag=true;
        fs<<indent<<"jump \%while_exp_"<<cur_while_exp<<endl;
        break;

    default:
        LOG_ERROR("@Closed_If_Stmt::dump: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
}

void Open_If_Stmt::Print(string indent)
{
    cout<<indent<<"Closed_If_Stmt {\n";
    string curindent=indent+"|\t";
    switch (cur_derivation_)
    {
    case 0: // IF '(' Exp ')' Stmt
        cout<<curindent<<"IF (\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<")\n";
        subexp2_->Print(curindent+"|\t");
        break;
    
    case 1: // IF '(' Exp ')' Closed_If_Stmt ELSE Open_If_Stmt
        cout<<curindent<<"IF (\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<")\n";
        subexp2_->Print(curindent+"|\t");
        cout<<curindent<<"ELSE\n";
        subexp3_->Print(curindent+"|\t");
        break;
    
    case 2: // WHILE '(' Exp ')' Stmt
        cout<<curindent<<"WHILE (\n";
        subexp1_->Print(curindent+"|\t");
        cout<<curindent<<")\n";
        cout<<curindent<<"DO\n";
        subexp2_->Print(curindent+"|\t");
        break;

    default:
        LOG_ERROR("@Open_If_Stmt::print: Unrecognized cur_derivation_=%d",cur_derivation_);
        break;
    }
    cout<<indent<<"}\n";
}

void Open_If_Stmt::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    int tpvar, entry1, entry2, entry3;
    int prev_cur_while_exp, prev_cur_while_end;
    switch (cur_derivation_)
    {
    case 0: // IF '(' Exp ')' Stmt
        tpvar=new_tempvar();
        entry1=new_entry();
        entry2=new_entry();
        subexp1_->Dump(fs,indent,tpvar);
        fs<<"\tbr %"<<tpvar<<", \%then_"<<entry1<<", \%end_"<<entry2<<endl;
        fs<<endl<<"//! IF branch of the if stmt"<<endl;
        fs<<"\%then_"<<entry1<<":"<<endl;
        return_flag=false;
        subexp2_->Dump(fs,indent);
        if (return_flag==false)
            fs<<"\tjump \%end_"<<entry2<<endl;
        return_flag=false;

        fs<<endl<<"//! end of the if stmt"<<endl;
        fs<<"\%end_"<<entry2<<":"<<endl;
        break;
    
    case 1: // IF '(' Exp ')' Closed_If_Stmt ELSE Open_If_Stmt
        tpvar=new_tempvar();
        entry1=new_entry();
        entry2=new_entry();
        entry3=new_entry();
        subexp1_->Dump(fs,indent,tpvar);
        fs<<"\tbr %"<<tpvar<<", \%then_"<<entry1<<", \%else_"<<entry2<<endl;
        fs<<endl<<"//! IF branch of the if stmt"<<endl;
        fs<<"\%then_"<<entry1<<":"<<endl;
        return_flag=false;
        subexp2_->Dump(fs,indent);
        if (return_flag==false)
            fs<<"\tjump \%end_"<<entry3<<endl;
        return_flag=false;

        fs<<endl<<"//! ELSE branch of the if stmt"<<endl;
        fs<<"\%else_"<<entry2<<":"<<endl;
        return_flag=false;
        subexp3_->Dump(fs,indent);
        if (return_flag==false)
            fs<<"\tjump \%end_"<<entry3<<endl;
        return_flag=false;

        fs<<endl<<"//! end of the if stmt"<<endl;
        fs<<"\%end_"<<entry3<<":"<<endl;
        break;
    
    case 2: // WHILE '(' Exp ')' Stmt
        tpvar=new_tempvar();
        entry1=new_entry();
        entry2=new_entry();
        entry3=new_entry();
        prev_cur_while_exp=cur_while_exp;
        prev_cur_while_end=cur_while_end;
        cur_while_exp=entry1;
        cur_while_end=entry3;
        fs<<indent<<"jump \%while_exp_"<<entry1<<endl;

        fs<<endl<<"\%while_exp_"<<entry1<<":"<<endl;
        subexp1_->Dump(fs,indent,tpvar);
        fs<<indent<<"br %"<<tpvar<<", \%while_loop_"<<entry2<<", \%while_end_"<<entry3<<endl;

        fs<<endl<<"\%while_loop_"<<entry2<<":"<<endl;
        return_flag=false;
        subexp2_->Dump(fs,indent,tpvar);
        if (return_flag==false)
            fs<<indent<<"jump \%while_exp_"<<entry1<<endl;
        return_flag=false;

        fs<<endl<<"\%while_end_"<<entry3<<":"<<endl;

        cur_while_exp=prev_cur_while_exp;
        cur_while_end=prev_cur_while_end;
        break;

    default:
        LOG_ERROR("@Open_If_Stmt::print: Unrecognized cur_derivation_=%d",cur_derivation_);
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
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
    int lhs, rhs, tpl, tpr, entry2, entry3, tpalloc, tpdest;
    switch (cur_derivation_)
    {
    case 0: // LAndExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // LOrExp OR LAndExp
        if (dest==-1)
            dest=new_tempvar();
        tpalloc=new_tempvar();
        lhs=new_tempvar();
        tpl=new_tempvar();
        entry2=new_entry();
        entry3=new_entry();
        fs<<indent<<"\%ALC_"<<tpalloc<<" = alloc i32 //! used for or exp"<<endl;
        subexp1_->Dump(fs,indent,lhs);
        fs<<indent<<"%"<<tpl<<" = ne %"<<lhs<<", 0"<<endl;
        fs<<indent<<"store %"<<tpl<<", \%ALC_"<<tpalloc<<endl;
        fs<<indent<<"br %"<<tpl<<", \%endor_"<<entry3<<", \%or_"<<entry2<<endl;

        tpdest=new_tempvar();
        rhs=new_tempvar();
        tpr=new_tempvar();
        fs<<endl<<"\%or_"<<entry2<<":"<<endl;
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<tpr<<" = ne %"<<rhs<<", 0"<<endl;
        fs<<indent<<"%"<<tpdest<<" = or %"<<tpl<<", %"<<tpr<<endl;
        fs<<indent<<"store %"<<tpdest<<", \%ALC_"<<tpalloc<<endl;
        fs<<indent<<"jump \%endor_"<<entry3<<endl;

        fs<<endl<<"\%endor_"<<entry3<<":"<<endl;
        fs<<indent<<"%"<<dest<<" = load \%ALC_"<<tpalloc<<endl;
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
        if (dest==-1)
            dest=new_tempvar();
        fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
    int lhs, rhs, tpl, tpr, entry2, entry3, tpalloc, tpdest;
    switch (cur_derivation_)
    {
    case 0: // EqExp
        subexp1_->Dump(fs,indent,dest);
        break;

    case 1: // LAndExp AND EqExp
        if (dest==-1)
            dest=new_tempvar();
        tpalloc=new_tempvar();
        lhs=new_tempvar();
        tpl=new_tempvar();
        entry2=new_entry();
        entry3=new_entry();
        fs<<indent<<"\%ALC_"<<tpalloc<<" = alloc i32 //! used for and exp"<<endl;
        subexp1_->Dump(fs,indent,lhs);
        fs<<indent<<"%"<<tpl<<" = ne %"<<lhs<<", 0"<<endl;
        fs<<indent<<"store %"<<tpl<<", \%ALC_"<<tpalloc<<endl;
        fs<<indent<<"br %"<<tpl<<", \%and_"<<entry2<<", \%endand_"<<entry3<<endl;

        tpdest=new_tempvar();
        rhs=new_tempvar();
        tpr=new_tempvar();
        fs<<endl<<"\%and_"<<entry2<<":"<<endl;
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<tpr<<" = ne %"<<rhs<<", 0"<<endl;
        fs<<indent<<"%"<<tpdest<<" = and %"<<tpl<<", %"<<tpr<<endl;
        fs<<indent<<"store %"<<tpdest<<", \%ALC_"<<tpalloc<<endl;
        fs<<indent<<"jump \%endand_"<<entry3<<endl;

        fs<<endl<<"\%endand_"<<entry3<<":"<<endl;
        fs<<indent<<"%"<<dest<<" = load \%ALC_"<<tpalloc<<endl;
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
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = eq %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // EqExp NEQ RelExp
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = lt %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // RelExp GT AddExp
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = gt %"<<lhs<<", %"<<rhs<<endl;
        break;
    
    case 3: // RelExp LEQ AddExp
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = le %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 4: // RelExp GEQ AddExp
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = add %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // AddExp MINUS MulExp
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
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
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = mul %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 2: // MulExp DIV UnaryExp
        if (dest==-1)
            dest=new_tempvar();
        lhs=new_tempvar();
        rhs=new_tempvar();
        subexp1_->Dump(fs,indent,lhs);
        subexp2_->Dump(fs,indent,rhs);
        fs<<indent<<"%"<<dest<<" = div %"<<lhs<<", %"<<rhs<<endl;
        break;

    case 3: // MulExp MOD UnaryExp
        if (dest==-1)
            dest=new_tempvar();
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

    case 4: // IDENT '(' FuncRParams ')'
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
        if (dest!=-1)
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
        if (dest!=-1)
            fs<<indent<<"%"<<dest<<" = sub 0, %"<<tpvar<<endl;
        break;

    case 2: // NOT UnaryExp
        tpvar=new_tempvar();
        subexp_->Dump(fs,indent,tpvar);
        if (dest!=-1)
            fs<<indent<<"%"<<dest<<" = eq 0, %"<<tpvar<<endl;
        break;
    
    case 3: // PrimaryExp
        subexp_->Dump(fs,indent,dest);
        break;

    case 4: // IDENT '(' FuncRParams ')'
        subexp_->FuncBlockDump(fs,indent,NULL);
        if (dest!=-1)
            fs<<indent<<"%"<<dest<<" = call @"<<ident_<<"(";
        else
            fs<<indent<<"call @"<<ident_<<"(";
        subexp_->Dump(fs,"");
        fs<<")"<<endl;
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
        if (dest!=-1)
            fs<<indent<<"%"<<dest<<" = add 0, "<<CalcVal()<<endl;
        return;
    }
    switch (cur_derivation_)
    {
    case 0: // '(' Exp ')'
        subexp_->Dump(fs,indent,dest);
        break;
    
    case 1: // Number
    case 2: // LVal
        if (dest!=-1)
            subexp_->Dump(fs,indent,dest);
        break;
    
    default:
        break;
    }
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