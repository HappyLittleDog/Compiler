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

template <typename T>
deque<int> InitConstArray(deque<int> size, T* initval, int& cur)
{
    if (size.size()==1)
    {
        int len=size[0];
        if (cur==initval->exps_.size())
        {
            deque<int> tp;
            for (int i=0;i<len;i++)
                tp.push_back(0);
            return tp;
        }
        else if (initval->exps_[cur]->GetDerivation()==0)
        {
            // single val without braces
            deque<int> tp;
            for (int i=0;i<len;i++)
            {
                if (cur==initval->exps_.size())
                    break;
                tp.push_back(initval->exps_[cur]->CalcVal());
                cur++;
            }
            // assert(tp.size()==len);
            while (tp.size()<len)
                tp.push_back(0);
            return tp;
        }
        else
        {
            deque<int> tp=initval->exps_[cur]->GetConstInitVals();
            while (tp.size()<len)
                tp.push_back(0);
            cur++;
            return tp;
        }
    }
    else
    {
        int len=size[0];
        size.pop_front();
        deque<int> rst;
        for (int i=0;i<len;i++)
        {
            deque<int> tp=InitConstArray(size,initval,cur);
            rst.insert(rst.end(),tp.begin(),tp.end());
        }
        return rst;
    }
}

deque<int> InitVarArray(basic_ostream<char>& fs, deque<int> size, InitVals* initval, int& cur)
{
    if (size.size()==1)
    {
        int len=size[0];
        if (cur==initval->exps_.size())
        {
            deque<int> tp;
            for (int i=0;i<len;i++)
                tp.push_back(0);
            return tp;
        }
        else if (initval->exps_[cur]->GetDerivation()==0)
        {
            // single exp without braces
            deque<int> tp;
            for (int i=0;i<len;i++)
            {
                if (cur==initval->exps_.size())
                    break;
                tp.push_back(new_tempvar());
                initval->exps_[cur]->Dump(fs,"\t",tp[i]);
                cur++;
            }
            // assert(tp.size()==len);
            while (tp.size()<len)
                tp.push_back(0);
            return tp;
        }
        else
        {
            deque<int> tp=initval->exps_[cur]->DumpInitVals(fs, "\t");
            while (tp.size()<len)
                tp.push_back(0);
            cur++;
            return tp;
        }
    }
    else
    {
        int len=size[0];
        size.pop_front();
        deque<int> rst;
        for (int i=0;i<len;i++)
        {
            deque<int> tp=InitVarArray(fs,size,initval,cur);
            rst.insert(rst.end(),tp.begin(),tp.end());
        }
        return rst;
    }
}

void DumpGlobalArrayInitializer(basic_ostream<char>& fs, deque<int> size, deque<int> initval, int& cur)
{
    if (size.size()==1)
    {
        int len=size[0];
        fs<<"{"<<initval[cur];
        cur++;
        for (int i=1;i<len;i++)
        {
            fs<<", "<<initval[cur];
            cur++;
        }
        fs<<"}";
        return;
    }
    else
    {
        int len=size[0];
        size.pop_front();
        fs<<"{";
        DumpGlobalArrayInitializer(fs,size,initval,cur);
        for (int i=1;i<len;i++)
        {
            fs<<", ";
            DumpGlobalArrayInitializer(fs,size,initval,cur);
        }
        fs<<"}";
        return;
    }
}

void DumpLocalConstArrayInitializer(basic_ostream<char>& fs, deque<int> size, deque<int> initval, int& cur, string ptr)
{
    if (size.size()==1)
    {
        int len=size[0];
        for (int i=0;i<len;i++)
        {
            int curv=initval[cur];
            cur++;
            int tpvar=new_tempvar();
            fs<<"\t%"<<tpvar<<" = getelemptr "<<ptr<<", "<<i<<endl;
            fs<<"\tstore "<<curv<<", %"<<tpvar<<endl;
        }
        return;
    }
    else
    {
        int len=size[0];
        size.pop_front();
        for (int i=0;i<len;i++)
        {
            int tpvar=new_tempvar();
            fs<<"\t%"<<tpvar<<" = getelemptr "<<ptr<<", "<<i<<endl;
            string curp="%"+to_string(tpvar);
            DumpLocalConstArrayInitializer(fs,size,initval,cur,curp);
        }
        return;
    }
}

void DumpLocalVarArrayInitializer(basic_ostream<char>& fs, deque<int> size, deque<int> initval, int& cur, string ptr)
{
    if (size.size()==1)
    {
        int len=size[0];
        for (int i=0;i<len;i++)
        {
            int curv=initval[cur];
            cur++;
            int tpvar=new_tempvar();
            fs<<"\t%"<<tpvar<<" = getelemptr "<<ptr<<", "<<i<<endl;
            if (curv==0)
                fs<<"\tstore 0, %"<<tpvar<<endl;
            else
                fs<<"\tstore %"<<curv<<", %"<<tpvar<<endl;
        }
        return;
    }
    else
    {
        int len=size[0];
        size.pop_front();
        for (int i=0;i<len;i++)
        {
            int tpvar=new_tempvar();
            fs<<"\t%"<<tpvar<<" = getelemptr "<<ptr<<", "<<i<<endl;
            string curp="%"+to_string(tpvar);
            DumpLocalVarArrayInitializer(fs,size,initval,cur,curp);
        }
        return;
    }
}

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
    if (block_!=nullptr)
    {
        global_var=false;
        block_->FuncBlockDump(fs,indent,this);
        fs<<indent<<"}"<<endl;
    }
    else
    {
        fs<<indent<<"decl @"<<ident_<<"(";
        if (params_!=nullptr)
        {
            auto params=reinterpret_cast<FuncFParams*>(params_.get());
            if (params->params_.size()!=0)
            {
                if (params->params_.size()==1)
                    params->params_[0]->DumpParamDecl(fs);
                else
                {
                    params->params_[0]->DumpParamDecl(fs);
                    for (int i=1;i<params->params_.size();i++)
                    {
                        fs<<", ";
                        params->params_[i]->DumpParamDecl(fs);
                    }
                }
            }
        }
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
        fs<<endl;
    }
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
    if (cur_derivation_==0)
    {
        switch (type_)
        {
        case 1:
            fs<<"i32";
            break;
        
        default:
            LOG_ERROR("@FuncFParam::Dump: (cur_derivation_=0) unexpected type_=%d",type_);
            break;
        }
    }
    else if (cur_derivation_==1)
    {
        auto size=size_->GetArraySize();
        fs<<"*";
        for (int i=0;i<size.size();i++)
            fs<<"[";
        fs<<"i32";
        for (int i=size.size()-1;i>=0;i--)
            fs<<", "<<size[i]<<"]";
    }
    else
    {
        LOG_ERROR("@FuncFParam::Dump: unexpected cur_derivation_=%d",cur_derivation_);
    }
}

void FuncFParam::DumpParamDecl(basic_ostream<char>& fs)
{
    if (cur_derivation_==0)
    {
        switch (type_)
        {
        case 1:
            fs<<"i32";
            break;
        
        default:
            LOG_ERROR("@FuncFParam::Dump: (cur_derivation_=0) unexpected type_=%d",type_);
            break;
        }
    }
    else if (cur_derivation_==1)
    {
        auto size=size_->GetArraySize();
        fs<<"*";
        for (int i=0;i<size.size();i++)
            fs<<"[";
        fs<<"i32";
        for (int i=size.size()-1;i>=0;i--)
            fs<<", "<<size[i]<<"]";
    }
    else
    {
        LOG_ERROR("@FuncFParam::Dump: unexpected cur_derivation_=%d",cur_derivation_);
    }
}

void FuncFParam::FuncBlockDump(basic_ostream<char>& fs, string indent, BaseAst* pt)
{
    if (cur_derivation_==0)
        CurSymTab->insert_var(ident_);
    else
    {
        auto size=size_->GetArraySize();
        size.push_front(0);
        CurSymTab->insert_var(ident_,size);
    }
}

void FuncFParam::ReAllocateFParams(basic_ostream<char>& fs, string indent)
{
    auto rst=CurSymTab->find(ident_);
    int pos=rst.val_;
    auto size=rst.size_;
    // assert(size[0]==0);
    size.pop_front();
    if (cur_derivation_==0)
    {
        fs<<indent<<"@VAR_"<<pos<<" = alloc i32"<<endl;
        fs<<indent<<"store @PARAM_"<<pos<<", @VAR_"<<pos<<endl;
    }
    else if (cur_derivation_==1)
    {
        fs<<indent<<"@VAR_"<<pos<<" = alloc *";
        for (int i=0;i<size.size();i++)
            fs<<"[";
        fs<<"i32";
        for (int i=size.size()-1;i>=0;i--)
            fs<<", "<<size[i]<<"]";
        fs<<endl;
        fs<<indent<<"store @PARAM_"<<pos<<", @VAR_"<<pos<<endl;
    }
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
    auto size=size_->GetArraySize();
    if (size.empty())
    {
        cout<<indent<<ident_<<":="<<initval_->CalcVal()<<endl;
    }
    else
    {
        cout<<indent<<ident_;
        for (int i=0;i<size.size();i++)
            cout<<"["<<size[i]<<"]";
        cout<<":={";
        auto initvals=initval_->GetConstInitVals();
        while (initvals.size()<size[0])
            initvals.push_back(0);
        cout<<initvals[0];
        for (int i=1;i<initvals.size();i++)
            cout<<", "<<initvals[i];
        cout<<"}\n";
    }
}

void ConstDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    if (global_var)
    {
        auto size=size_->GetArraySize();
        if (size.empty())
        {
            CurSymTab->insert_const(ident_, initval_->CalcVal());
        }
        else
        {
            CurSymTab->insert_const(ident_, 0, size);
            int pos=CurSymTab->find(ident_).val_;
            fs<<"global @VAR_"<<pos<<" = alloc ";
            for (int i=0;i<size.size();i++)
                fs<<"[";
            fs<<"i32";
            for (int i=size.size()-1;i>=0;i--)
                fs<<", "<<size[i]<<"]";
            int _cur_=0;
            auto initvals=InitConstArray(size,reinterpret_cast<ConstInitVals*>(reinterpret_cast<ConstInitVal*>(initval_.get())->subexp_.get()),_cur_);
            fs<<", ";
            _cur_=0;
            DumpGlobalArrayInitializer(fs,size,initvals,_cur_);
            fs<<" //! w.r.t symbol "<<ident_<<endl;
        }
    }
    else
    {
        auto size=size_->GetArraySize();
        if (size.empty())
        {
            CurSymTab->insert_const(ident_, initval_->CalcVal());
        }
        else
        {
            CurSymTab->insert_const(ident_, 0, size);
            int pos=CurSymTab->find(ident_).val_;
            fs<<"\t@VAR_"<<pos<<" = alloc ";
            for (int i=0;i<size.size();i++)
                fs<<"[";
            fs<<"i32";
            for (int i=size.size()-1;i>=0;i--)
                fs<<", "<<size[i]<<"]";
            fs<<" //! w.r.t symbol "<<ident_<<endl;
            int _cur_=0;
            auto initvals=InitConstArray(size,reinterpret_cast<ConstInitVals*>(reinterpret_cast<ConstInitVal*>(initval_.get())->subexp_.get()),_cur_);
            _cur_=0;
            string curp="@VAR_"+to_string(pos);
            DumpLocalConstArrayInitializer(fs,size,initvals,_cur_,curp);
        }
    }
}

void ArraySize::Print(string indent)
{
    return;
}

void ArraySize::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    return;
}

void ConstInitVal::Print(string indent)
{
    return;
}

void ConstInitVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    return;
}

void ConstInitVals::Print(string indent)
{
    return;
}

void ConstInitVals::Dump(basic_ostream<char>& fs, string indent, int dest)
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
    auto size=size_->GetArraySize();
    if (size.empty())
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
    else
    {
        cout<<indent<<ident_;
        for (int i=0;i<size.size();i++)
            cout<<"["<<size[i]<<"]";
        cout<<" :=";
        if (cur_derivation_==0)
            cout<<" \n";
        else
        {
            cout<<" {\n";
            string curindent=indent+"|\t";
            initval_->Print(curindent);
            cout<<indent<<"}\n";
        }
    }
}

void VarDef::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    auto size=size_->GetArraySize();
    if (global_var)
    {
        if (size.empty())
        {
            CurSymTab->insert_var(ident_);
            int cur=CurSymTab->find(ident_).val_;
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
            CurSymTab->insert_var(ident_, size);
            int pos=CurSymTab->find(ident_).val_;
            fs<<"global @VAR_"<<pos<<" = alloc ";
            for (int i=0;i<size.size();i++)
                fs<<"[";
            fs<<"i32";
            for (int i=size.size()-1;i>=0;i--)
                fs<<", "<<size[i]<<"]";
            if (cur_derivation_==0)
            {
                fs<<", zeroinit //! w.r.t symbol "<<ident_<<endl;
            }
            else
            {
                int _cur_=0;
                auto initvals=InitConstArray(size,reinterpret_cast<ConstInitVals*>(reinterpret_cast<ConstInitVal*>(initval_.get())->subexp_.get()),_cur_);
                fs<<", ";
                _cur_=0;
                DumpGlobalArrayInitializer(fs,size,initvals,_cur_);
                fs<<" //! w.r.t symbol "<<ident_<<endl;
            }
        }
    }
    else
    {
        CurSymTab->insert_var(ident_, size);
        int cur=CurSymTab->find(ident_).val_;
        if (size.empty())
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
        else
        {
            fs<<indent<<"@VAR_"<<cur<<" = alloc ";
            for (int i=0;i<size.size();i++)
                fs<<"[";
            fs<<"i32";
            for (int i=size.size()-1;i>=0;i--)
                fs<<", "<<size[i]<<"]";
            fs<<" //! w.r.t symbol "<<ident_<<endl;
            if (cur_derivation_==1)
            {
                int _cur_=0;
                auto posinitvals=InitVarArray(fs,size,reinterpret_cast<InitVals*>(reinterpret_cast<InitVal*>(initval_.get())->subexp_.get()),_cur_);
                _cur_=0;
                string curp="@VAR_"+to_string(cur);
                DumpLocalVarArrayInitializer(fs,size,posinitvals,_cur_,curp);
                // for (int i=0;i<posinitvals.size();i++)
                // {
                //     int tpvar=new_tempvar();
                //     fs<<indent<<"%"<<tpvar<<" = getelemptr @VAR_"<<cur<<", "<<i<<endl;
                //     fs<<indent<<"store %"<<posinitvals[i]<<", %"<<tpvar<<endl;
                // }
                // for (int i=posinitvals.size();i<size[0];i++)
                // {
                //     int tpvar=new_tempvar();
                //     fs<<indent<<"%"<<tpvar<<" = getelemptr @VAR_"<<cur<<", "<<i<<endl;
                //     fs<<indent<<"store 0, %"<<tpvar<<endl;
                // }
            }
        }
    }
}

void InitVal::Print(string indent)
{
    if (cur_derivation_==0)
    {
        if (IsConst())
            cout<<indent<<CalcVal()<<endl;
        else
            subexp_->Print(indent);
    }
    else
    {
        subexp_->Print(indent);
    }
}

void InitVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    assert(cur_derivation_==0);
    subexp_->Dump(fs,indent,dest);
}

void InitVals::Print(string indent)
{
    for (int i=0;i<exps_.size();i++)
    {
        exps_[i]->Print(indent);
    }
}

void InitVals::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    LOG_ERROR("@Exps::Dump: unexpected function call!");
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
    deque<int> posindex, size;
    string curp;
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
        posindex=subexp1_->DumpArrayIndex(fs,indent);
        curp="@VAR_"+to_string(CurSymTab->find(subexp1_->GetIdent()).val_);
        size=CurSymTab->find(subexp1_->GetIdent()).size_;
        if (size.size()>0)
        {
            if (size[0]==0)
            {
                // pointer to array
                int tpvar1=new_tempvar();
                fs<<indent<<"%"<<tpvar1<<" = load "<<curp<<endl;
                int tpvar2=new_tempvar();
                fs<<indent<<"%"<<tpvar2<<" = getptr %"<<tpvar1<<", %"<<posindex[0]<<endl;
                posindex.pop_front();
                curp="%"+to_string(tpvar2);
            }
            for (int i=0;i<posindex.size();i++)
            {
                int tpvar=new_tempvar();
                fs<<indent<<"%"<<tpvar<<" = getelemptr "<<curp<<", %"<<posindex[i]<<endl;
                curp="%"+to_string(tpvar);
            }
        }
        // LVal is scaler
        if (subexp2_->IsConst())
            fs<<indent<<"store "<<subexp2_->CalcVal()<<", "<<curp<<endl;
        else
        {
            tpvar=new_tempvar();
            subexp2_->Dump(fs,indent,tpvar);
            fs<<indent<<"store %"<<tpvar<<", "<<curp<<endl;
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
    ndx_->Print(indent);
}

void LVal::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    // will only be called in [Exp] (i.e. as RVal)
    if (CurSymTab->find(ident_).isconst_)
    {
        fs<<indent<<"%"<<dest<<" = add 0, "<<CurSymTab->find(ident_).val_<<endl;
    }
    else
    {
        auto posindex=ndx_->DumpArrayIndex(fs,indent);

        string curp="@VAR_"+to_string(CurSymTab->find(ident_).val_);
        auto size=CurSymTab->find(ident_).size_;
        if (size.size()>0)
        {
            // LVal is a pointer
            int curpos=0;
            while (size[curpos]==0 && curpos<posindex.size())
            {
                // pointer to array
                int tpvar1=new_tempvar();
                fs<<indent<<"%"<<tpvar1<<" = load "<<curp<<endl;
                int tpvar2=new_tempvar();
                fs<<indent<<"%"<<tpvar2<<" = getptr %"<<tpvar1<<", %"<<posindex[curpos]<<endl;
                curp="%"+to_string(tpvar2);
                curpos++;
            }
            for (;curpos<posindex.size();curpos++)
            {
                int tpvar=new_tempvar();
                fs<<indent<<"%"<<tpvar<<" = getelemptr "<<curp<<", %"<<posindex[curpos]<<endl;
                curp="%"+to_string(tpvar);
            }

            if (size.size()>posindex.size())
            {
                // partially dereferenced
                if (size[posindex.size()]!=0)
                    fs<<indent<<"%"<<dest<<" = getelemptr "<<curp<<", 0"<<endl;
                else
                    fs<<indent<<"%"<<dest<<" = load "<<curp<<endl;
            }
            else
            {
                // fully dereferenced
                fs<<indent<<"%"<<dest<<" = load "<<curp<<endl;
            }
        }
        else
        {
            // LVal is a single value
            fs<<indent<<"%"<<dest<<" = load "<<curp<<endl;
        }


        // string addr="@VAR_"+to_string(CurSymTab->find(ident_).val_);
        // for (int i=0;i<posindex.size();i++)
        // {
        //     int tpvar=new_tempvar();
        //     fs<<indent<<"%"<<tpvar<<" = getelemptr "<<addr<<", %"<<posindex[i]<<endl;
        //     addr="%"+to_string(tpvar);
        // }
        // fs<<indent<<"%"<<dest<<" = load "<<addr<<endl;
    }
}

void ArrayIndex::Print(string indent)
{
    for (int i=0;i<ndx_.size();i++)
    {
        cout<<indent<<"["<<endl;
        ndx_[i]->Print(indent+"\t");
        cout<<indent<<"]"<<endl;
    }
}

void ArrayIndex::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    LOG_ERROR("@ArrayIndex::Dump: unexpected function call!");
}

void Number::Print(string indent)
{
    cout<<indent<<int_const_<<endl;
}

void Number::Dump(basic_ostream<char>& fs, string indent, int dest)
{
    fs<<indent<<"%"<<dest<<" = add 0, "<<int_const_<<endl;
}