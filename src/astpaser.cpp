#include "include/astparser.hpp"
using namespace std;

stringstream asms;
int RISCV_IMM_THRESHOLD=(1<<12);

class Register_Allocator
{
	bool T_[7] = {};
	// bool A_[8] = {};
	map<const void *, string> nt;

public:
	Register_Allocator(const koopa_raw_slice_t &params)
	{
		// int nparams=min(int(params.len), 8);
		// assert(params.len <= 8);
		// int n_param = params.len;
		for (int i = 0; i < 7; i++)
			T_[i] = true;
		// for (int i = n_param; i < 8; i++)
		// 	A_[i] = true;
		// for (int i = 0; i < n_param; i++)
		// {
		// 	string cur = "a" + to_string(i);
		// 	nt.insert(make_pair((const void *)(params.buffer[i]), cur));
		// }
	}
	string allocate_temp()
	{
		string reg;
		for (int i = 0; i < 7; i++)
		{
			if (T_[i])
			{
				T_[i] = false;
				reg = "t" + to_string(i);
				return reg;
			}
		}
		// for (int i = 0; i < 8; i++)
		// {
		// 	if (A_[i])
		// 	{
		// 		A_[i] = false;
		// 		reg = "a" + to_string(i);
		// 		return reg;
		// 	}
		// }
		LOG_ERROR("NO AVAILABLE REGISTERS!");
		return "";
	}
	// string allocate(const void *addr)
	// {
	// 	string reg;
	// 	for (int i = 0; i < 7; i++)
	// 	{
	// 		if (T_[i])
	// 		{
	// 			T_[i] = false;
	// 			reg = "t" + to_string(i);
	// 			nt.insert(make_pair(addr, reg));
	// 			return reg;
	// 		}
	// 	}
	// 	for (int i = 0; i < 8; i++)
	// 	{
	// 		if (A_[i])
	// 		{
	// 			A_[i] = false;
	// 			reg = "a" + to_string(i);
	// 			nt.insert(make_pair(addr, reg));
	// 			return reg;
	// 		}
	// 	}
	// 	LOG_ERROR("NO AVAILABLE REGISTERS!");
	// 	return "";
	// }
	// void free(const void *addr)
	// {
	// 	auto it = nt.find(addr);
	// 	if (it == nt.end())
	// 	{
	// 		LOG_ERROR("@get_pos: can NOT find pos w.r.t addr %p", addr);
	// 		return;
	// 	}
	// 	nt.erase(it);
	// }
	void free_temp(string &reg)
	{
		int cur = stoi(reg.substr(1));
		// if (reg[0] == 'a')
		// {
		// 	if (A_[cur])
		// 	{
		// 		LOG_ERROR("%s is currently available!", reg.c_str());
		// 	}
		// 	A_[cur] = true;
		// }
		if (reg[0] == 't')
		{
			if (T_[cur])
			{
				LOG_ERROR("%s is currently available!", reg.c_str());
			}
			T_[cur] = true;
		}
		else
		{
			LOG_ERROR("%s: unexpected register.", reg.c_str());
		}
	}
	// string get_pos(const void *addr)
	// {
	// 	auto it = nt.find(addr);
	// 	if (it == nt.end())
	// 	{
	// 		LOG_ERROR("@get_pos: can NOT find pos w.r.t addr %p", addr);
	// 		return "";
	// 	}
	// 	return it->second;
	// }
};

class Stack_Allocator
{
private:
	int size = 4;
	int offset = 0;  // used for function call: extra space for more than 8 params.
	map<const void*, int> nt;
public:
	Stack_Allocator() = default;
	void allocate(const void* addr)
	{
		size+=4;
		auto it=nt.insert(make_pair(addr, size));
		if (!it.second)
		{
			LOG_ERROR("@Stack_Allocator::insert: insert %p failed!", addr);
		}
	}
	void allocate_ptr(const void* addr)
	{
		auto val=reinterpret_cast<koopa_raw_value_t>(addr);
		int cursz=CalcSize(val->ty->data.pointer.base);
		LOG_DEBUG("@SA::allocate_ptr: cur size=%d",cursz);
		size+=cursz;
		size+=4; // used to store the ptr (i.e. addr)
		auto it=nt.insert(make_pair(addr, size));
		if (!it.second)
		{
			LOG_ERROR("@Stack_Allocator::insert: insert %p failed!", addr);
		}
	}

	/**
	 * @brief Return the position of the corresponding item
	 * 
	 * @param addr its corresponding koopa_raw_value_t
	 * @return the item is located at sp + [RETV]
	 */
	int get_pos(const void* addr)
	{
		auto it=nt.find(addr);
		if (it==nt.end())
		{
			LOG_ERROR("@Stack_Allocator::get_pos: %p not found!", addr);
			return 0;
		}
		return size - (it->second) + offset;
	}

	void more_space(int size)
	{
		offset+=size;
	}

	void less_space(int size)
	{
		offset-=size;
	}

	int total_size()
	{
		return size;
	}
};

// 访问 raw program
void Visit(const koopa_raw_program_t &program)
{
	// 执行一些其他的必要操作
	// ...
	// 访问所有全局变量
	if (program.values.len!=0)
	{
		asms << "\t.data\n";
		Visit(program.values);
		asms<<endl;
	}
	// 访问所有函数
	if (program.funcs.len!=0)
	{
		asms << "\t.text\n";
		Visit(program.funcs);
	}
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice, Register_Allocator *ra, Stack_Allocator *sa)
{
	for (size_t i = 0; i < slice.len; ++i)
	{
		auto ptr = slice.buffer[i];
		// 根据 slice 的 kind 决定将 ptr 视作何种元素
		switch (slice.kind)
		{
		case KOOPA_RSIK_FUNCTION:
			// 访问函数
			Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
			break;
		case KOOPA_RSIK_BASIC_BLOCK:
			// 访问基本块
			Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr), ra, sa);
			break;
		case KOOPA_RSIK_VALUE:
			// 访问指令
			Visit(reinterpret_cast<koopa_raw_value_t>(ptr), ra, sa);
			break;
		default:
			// 我们暂时不会遇到其他内容, 于是不对其做任何处理
			LOG_ERROR("@Visit_slice: Unimplemented slice.kind: %d", slice.kind);
		}
	}
}

// 访问函数
void Visit(const koopa_raw_function_t &func)
{
	if (func->bbs.len!=0)
	{
		// 执行一些其他的必要操作
		asms << "\t.globl " << &func->name[1] << endl;
		asms << &func->name[1] << ":\n";
		Register_Allocator ra(func->params);
		Stack_Allocator sa;

		Scan(func->bbs, &sa);
		asms<<"\tli t0, "<<sa.total_size()<<endl;
		asms<<"\tsub sp, sp, t0"<<endl;
		asms<<"\tli t0, "<<sa.total_size()-4<<endl;
		asms<<"\tadd t0, t0, sp"<<endl;
		asms<<"\tsw ra, 0(t0)"<<endl;
		// 访问所有基本块
		Visit(func->bbs, &ra, &sa);
		asms<<endl;
	}
	else
	{
		//
	}
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb, Register_Allocator *ra, Stack_Allocator *sa)
{
	// 执行一些其他的必要操作
	// ...
	// 访问所有指令
	asms<<&bb->name[1]<<":"<<endl;
	Visit(bb->insts, ra, sa);
}

void Visit(const koopa_raw_value_t &value, Register_Allocator *ra, Stack_Allocator *sa, string dest_register)
{
	// LOG_DEBUG("@Visit: dest_register=%s",dest_register.c_str());
	// 根据指令类型判断后续需要如何访问
	const auto &kind = value->kind;
	// asms<<"[debug] @visit(raw_value) tag="<<kind.tag<<endl;
	if (kind.tag!=KOOPA_RVT_INTEGER)
		assert(dest_register=="");
	switch (kind.tag)
	{
	case KOOPA_RVT_RETURN:
		// 访问 return 指令
		VisitRet(kind.data.ret, ra, sa);
		break;
	case KOOPA_RVT_INTEGER:
		// 访问 integer 指令
		Visit(kind.data.integer, dest_register);
		break;
	case KOOPA_RVT_BINARY:
		VisitBin(value, ra, sa);
		break;
	case KOOPA_RVT_ALLOC:
		// Nothing to do here
		VisitAlloc(value, ra, sa);
		break;
	case KOOPA_RVT_LOAD:
		VisitLoad(value, ra, sa);
		break;
	case KOOPA_RVT_STORE:
		VisitStore(value,ra,sa);
		break;
	case KOOPA_RVT_BRANCH:
		VisitBranch(value, ra, sa);
		break;
	case KOOPA_RVT_JUMP:
		VisitJump(value,ra,sa);
		break;
	case KOOPA_RVT_CALL:
		VisitCall(value,ra,sa);
		break;
	case KOOPA_RVT_GLOBAL_ALLOC:
		VisitGlobalVar(value,ra,sa);
		break;
	case KOOPA_RVT_GET_ELEM_PTR:
		VisitGetElemPtr(value,ra,sa);
		break;
	
	case KOOPA_RVT_GET_PTR:
		VisitGetPtr(value, ra, sa);
		break;

	default:
		// 其他类型暂时遇不到
		LOG_ERROR("@value: Unimplemented kind.tag: %d", kind.tag);
	}
}

// return
void VisitRet(const koopa_raw_return_t &ret, Register_Allocator *ra, Stack_Allocator *sa)
{
	const auto& retv=ret.value;
	string reg;
	if (retv!=NULL)
	{
		switch (retv->kind.tag)
		{
		case KOOPA_RVT_INTEGER:
			/* code */
			asms<<"\tli a0, "<<retv->kind.data.integer.value<<endl;
			break;
		
		case KOOPA_RVT_BINARY:
			reg=ImplicitLoad(retv,ra,sa);
			asms<<"\tmv a0, "<<reg<<endl;
			ra->free_temp(reg);
			break;

		case KOOPA_RVT_LOAD:
			reg=ImplicitLoad(retv,ra,sa);
			asms<<"\tmv a0, "<<reg<<endl;
			ra->free_temp(reg);
			break;
		
		case KOOPA_RVT_CALL:
			reg=ImplicitLoad(retv,ra,sa);
			asms<<"\tmv a0, "<<reg<<endl;
			ra->free_temp(reg);
			break;

		default:
			LOG_ERROR("@visit(return): unexpected retv type: %d",retv->kind.tag);
			break;
		}
	}
	string addr=ra->allocate_temp();
	asms<<"\tli "<<addr<<", "<<sa->total_size()-4<<endl;
	asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
	asms<<"\tlw ra"<<", 0("<<addr<<")"<<endl;
	asms<<"\tli "<<addr<<", "<<sa->total_size()<<endl;
	asms<<"\tadd sp, sp, "<<addr<<endl;
	asms << "\tret\n";
	ra->free_temp(addr);
}

// binary operation
void VisitBin(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string dest = ra->allocate_temp();
	const auto &bin = val->kind.data.binary;
	const auto &lhs = bin.lhs;
	const auto &rhs = bin.rhs;
	assert(dest != "");
	switch (bin.op)
	{
	case KOOPA_RBO_NOT_EQ:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value == rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<lr<<", "<<(-1)*ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tsub "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
			asms<<"\tsnez "<<dest<<", "<<dest<<endl;
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<rr<<", "<<(-1)*li<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tsub "<<dest<<", "<<rr<<", "<<dest<<endl;
			}
			ra->free_temp(rr);
			asms<<"\tsnez "<<dest<<", "<<dest<<endl;
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tsub "<<lr<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tsnez "<<dest<<", "<<lr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_EQ:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value == rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<lr<<", "<<(-1)*ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tsub "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<rr<<", "<<(-1)*li<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tsub "<<dest<<", "<<rr<<", "<<dest<<endl;
			}
			ra->free_temp(rr);
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tsub "<<dest<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;
	
	case KOOPA_RBO_GT:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value > rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tsgt "<<dest<<", "<<lr<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tsgt "<<dest<<", "<<dest<<", "<<rr<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tsgt "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_LT:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value < rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tslt "<<dest<<", "<<lr<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tslt "<<dest<<", "<<dest<<", "<<rr<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tslt "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_GE:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value >= rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tslt "<<dest<<", "<<lr<<", "<<dest<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tslt "<<dest<<", "<<dest<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tslt "<<dest<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_LE:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			if (lhs->kind.data.integer.value >= rhs->kind.data.integer.value)
			{
				asms << "\tli " << dest << ", 1" << endl;
			}
			else
			{
				asms << "\tli " << dest << ", 0" << endl;
			}
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tsgt "<<dest<<", "<<lr<<", "<<dest<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tsgt "<<dest<<", "<<dest<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tsgt "<<dest<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<dest<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_ADD:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<lhs->kind.data.integer.value + rhs->kind.data.integer.value<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<lr<<", "<<ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tadd "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<rr<<", "<<li<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tadd "<<dest<<", "<<rr<<", "<<dest<<endl;
			}
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tadd "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_SUB:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<lhs->kind.data.integer.value - rhs->kind.data.integer.value<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\taddi "<<dest<<", "<<lr<<", "<<(-1)*ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tsub "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
			{
				asms<<"\taddi "<<dest<<", "<<rr<<", "<<(-1)*li<<endl;
				asms<<"\tneg "<<dest<<", "<<dest<<endl;
			}
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tsub "<<dest<<", "<<dest<<", "<<rr<<endl;
			}
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tsub "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_MUL:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<lhs->kind.data.integer.value * rhs->kind.data.integer.value<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tmul "<<dest<<", "<<lr<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tmul "<<dest<<", "<<rr<<", "<<dest<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tmul "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	case KOOPA_RBO_DIV:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<lhs->kind.data.integer.value / rhs->kind.data.integer.value<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\tdiv "<<dest<<", "<<lr<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\tdiv "<<dest<<", "<<dest<<", "<<rr<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tdiv "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;
	
	case KOOPA_RBO_MOD:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<lhs->kind.data.integer.value % rhs->kind.data.integer.value<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<ri<<endl;
			asms<<"\trem "<<dest<<", "<<lr<<", "<<dest<<endl;
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			asms<<"\tli "<<dest<<", "<<li<<endl;
			asms<<"\trem "<<dest<<", "<<dest<<", "<<rr<<endl;
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\trem "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;
	
	case KOOPA_RBO_AND:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<(lhs->kind.data.integer.value & rhs->kind.data.integer.value)<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\tandi "<<dest<<", "<<lr<<", "<<ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tand "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
				asms<<"\tandi "<<dest<<", "<<rr<<", "<<li<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tand "<<dest<<", "<<rr<<", "<<dest<<endl;
			}
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tand "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;
	
	case KOOPA_RBO_OR:
		if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			// both are immediate
			asms << "\tli " << dest << ", " <<(lhs->kind.data.integer.value | rhs->kind.data.integer.value)<< endl;
		}
		else if (lhs->kind.tag != KOOPA_RVT_INTEGER && rhs->kind.tag == KOOPA_RVT_INTEGER)
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			if (ri<RISCV_IMM_THRESHOLD)
				asms<<"\tori "<<dest<<", "<<lr<<", "<<ri<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<ri<<endl;
				asms<<"\tor "<<dest<<", "<<lr<<", "<<dest<<endl;
			}
			ra->free_temp(lr);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			if (li<RISCV_IMM_THRESHOLD)
				asms<<"\tori "<<dest<<", "<<rr<<", "<<li<<endl;
			else
			{
				asms<<"\tli "<<dest<<", "<<li<<endl;
				asms<<"\tor "<<dest<<", "<<rr<<", "<<dest<<endl;
			}
			ra->free_temp(rr);
		}
		else
		{
			string lr=ImplicitLoad(lhs,ra,sa);
			assert(lr!="");
			string rr=ImplicitLoad(rhs,ra,sa);
			assert(rr!="");
			asms<<"\tor "<<dest<<", "<<lr<<", "<<rr<<endl;
			ra->free_temp(lr);
			ra->free_temp(rr);
		}
		break;

	default:
		LOG_ERROR("@VisitBin: Unsupported BinOP: %d", bin.op);
		break;
	}
	if (sa->get_pos((const void*)val)<2048)
		asms<<"\tsw "<<dest<<", "<<sa->get_pos((const void*)val)<<"(sp)"<<endl;
	else
	{
		string addr=ra->allocate_temp();
		asms<<"\tli "<<addr<<", "<<sa->get_pos((const void*)val)<<endl;
		asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
		asms<<"\tsw "<<dest<<", 0("<<addr<<")"<<endl;
		ra->free_temp(addr);
	}
	ra->free_temp(dest);
}

void VisitLoad(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string tpreg;

	// front end: load the value to tpreg
	switch (val->kind.data.load.src->kind.tag)
	{
	case KOOPA_RVT_GLOBAL_ALLOC:
		tpreg=ra->allocate_temp();
		asms<<"\tla "<<tpreg<<", "<<&(val->kind.data.load.src->name[1])<<endl;
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		break;

	case KOOPA_RVT_ALLOC:
		tpreg=ImplicitLoad(val->kind.data.load.src, ra, sa);
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		break;

	case KOOPA_RVT_GET_ELEM_PTR:
		tpreg=ImplicitLoad(val->kind.data.load.src, ra, sa);
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		break;

	case KOOPA_RVT_GET_PTR:
		tpreg=ImplicitLoad(val->kind.data.load.src, ra, sa);
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		break;

	default:
		LOG_ERROR("@VisitLoad::front end: unexpected src.kind.tag=%d",val->kind.data.load.src->kind.tag);
		break;
	}
	if (sa->get_pos((const void*)val)<2048)
		asms<<"\tsw "<<tpreg<<", "<<sa->get_pos((const void*)val)<<"(sp)"<<endl;
	else
	{
		string addr=ra->allocate_temp();
		asms<<"\tli "<<addr<<", "<<sa->get_pos((const void*)val)<<endl;
		asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
		asms<<"\tsw "<<tpreg<<", 0("<<addr<<")"<<endl;
		ra->free_temp(addr);
	}
	ra->free_temp(tpreg);
}

string ImplicitLoad(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string tpreg=ra->allocate_temp();
	assert(tpreg!="");
	if (sa->get_pos(val)<2048)
		asms<<"\tlw "<<tpreg<<", "<<sa->get_pos((const void*)val)<<"(sp)"<<endl;
	else
	{
		asms<<"\tli "<<tpreg<<", "<<sa->get_pos((const void*)val)<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpreg<<", sp"<<endl;
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
	}
	return tpreg;
}

void VisitStore(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string tpreg, tpaddr;

	// front end, put the value in register tpreg
	switch (val->kind.data.store.value->kind.tag)
	{
	case KOOPA_RVT_INTEGER:
		tpreg=ra->allocate_temp();
		asms<<"\tli "<<tpreg<<", "<<val->kind.data.store.value->kind.data.integer.value<<endl;
		break;

	case KOOPA_RVT_FUNC_ARG_REF:
		tpreg=ra->allocate_temp();
		if (val->kind.data.store.value->kind.data.func_arg_ref.index<8)
			asms<<"\tmv "<<tpreg<<", a"<<val->kind.data.store.value->kind.data.func_arg_ref.index<<endl;
		else
		{
			asms<<"\tli "<<tpreg<<", "<<4*(val->kind.data.store.value->kind.data.func_arg_ref.index-8)+sa->total_size()<<endl;
			asms<<"\tadd "<<tpreg<<", "<<tpreg<<", sp"<<endl;
			asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		}
		break;
	
	default:
		tpreg=ImplicitLoad(val->kind.data.store.value, ra, sa);
		break;
	}

	// back end, put the val in tpreg to dest
	switch (val->kind.data.store.dest->kind.tag)
	{
	case KOOPA_RVT_GLOBAL_ALLOC:
		tpaddr=ra->allocate_temp();
		asms<<"\tla "<<tpaddr<<", "<<&(val->kind.data.store.dest->name[1])<<endl;
		asms<<"\tsw "<<tpreg<<", 0("<<tpaddr<<")"<<endl;
		ra->free_temp(tpaddr);
		break;
	
	case KOOPA_RVT_ALLOC:
		tpaddr=ra->allocate_temp();
		asms<<"\tli "<<tpaddr<<", "<<sa->get_pos((const void*)val->kind.data.store.dest)<<endl;
		asms<<"\tadd "<<tpaddr<<", "<<tpaddr<<", sp"<<endl;
		asms<<"\tlw "<<tpaddr<<", 0("<<tpaddr<<")"<<endl;
		asms<<"\tsw "<<tpreg<<", 0("<<tpaddr<<")"<<endl;
		ra->free_temp(tpaddr);
		// asms<<"\tsw "<<tpreg<<", "<<sa->get_pos((const void*)val->kind.data.store.dest)<<"(sp)"<<endl;
		break;

	case KOOPA_RVT_GET_ELEM_PTR:
	case KOOPA_RVT_GET_PTR:
		tpaddr=ImplicitLoad(val->kind.data.store.dest,ra,sa);
		asms<<"\tsw "<<tpreg<<", 0("<<tpaddr<<")"<<endl;
		ra->free_temp(tpaddr);
		break;

	default:
		LOG_ERROR("@VisitStore::back end: unexpected dest.kind.tag=%d",int(val->kind.data.store.dest->kind.tag));
		break;
	}
	ra->free_temp(tpreg);
}

void VisitBranch(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	// asms<<"# if exp:"<<endl;
	string tpvar=ImplicitLoad(val->kind.data.branch.cond, ra, sa);
	asms<<"\tbnez "<<tpvar<<", "<<&(val->kind.data.branch.true_bb->name)[1]<<endl;
	asms<<"\tj "<<&(val->kind.data.branch.false_bb->name)[1]<<endl;
	ra->free_temp(tpvar);
}

void VisitJump(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	asms<<"\tj "<<&(val->kind.data.jump.target->name)[1]<<endl;
}

void VisitCall(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	// asms<<"[debug] tag="<<((const koopa_raw_value_t*(val->kind.data.call.args.buffer[0]))->kind.tag)<<endl;
	// asms<<"[debug] @VisitCall"<<endl;
	// Visit(val->kind.data.call.args,ra,sa);
	auto args=val->kind.data.call.args;
	if (args.len<=8)
	{
		for (int i=0;i<args.len;i++)
		{
			auto cur=reinterpret_cast<const koopa_raw_value_t>(args.buffer[i]);
			if (cur->kind.tag==KOOPA_RVT_INTEGER)
			{
				asms<<"\tli a"<<i<<", "<<cur->kind.data.integer.value<<endl;
			}
			else
			{
				if (sa->get_pos(cur)<2048)
					asms<<"\tlw a"<<i<<", "<<sa->get_pos(cur)<<"(sp)"<<endl;
				else
				{
					string addr=ra->allocate_temp();
					asms<<"\tli "<<addr<<", "<<sa->get_pos(cur)<<endl;
					asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
					asms<<"\tlw a"<<i<<", 0("<<addr<<")"<<endl;
					ra->free_temp(addr);
				}
			}
		}
	}
	else
	{
		for (int i=0;i<8;i++)
		{
			auto cur=reinterpret_cast<const koopa_raw_value_t>(args.buffer[i]);
			if (cur->kind.tag==KOOPA_RVT_INTEGER)
			{
				asms<<"\tli a"<<i<<", "<<cur->kind.data.integer.value<<endl;
			}
			else
			{
				if (sa->get_pos(cur)<2048)
					asms<<"\tlw a"<<i<<", "<<sa->get_pos(cur)<<"(sp)"<<endl;
				else
				{
					string addr=ra->allocate_temp();
					asms<<"\tli "<<addr<<", "<<sa->get_pos(cur)<<endl;
					asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
					asms<<"\tlw a"<<i<<", 0("<<addr<<")"<<endl;
					ra->free_temp(addr);
				}
			}
		}
		int extrasize=4*(args.len-8);
		asms<<"\taddi sp, sp, -"<<extrasize<<endl;
		sa->more_space(extrasize);
		string tpreg=ra->allocate_temp();
		for (int i=8;i<args.len;i++)
		{
			auto cur=reinterpret_cast<const koopa_raw_value_t>(args.buffer[i]);
			
			if (cur->kind.tag==KOOPA_RVT_INTEGER)
			{
				asms<<"\tli "<<tpreg<<", "<<cur->kind.data.integer.value<<endl;
				asms<<"\tsw "<<tpreg<<", "<<4*(i-8)<<"(sp)"<<endl;
			}
			else
			{
				if (sa->get_pos(cur)<2048)
					asms<<"\tlw "<<tpreg<<", "<<sa->get_pos(cur)<<"(sp)"<<endl;
				else
				{
					string addr=ra->allocate_temp();
					asms<<"\tli "<<addr<<", "<<sa->get_pos(cur)<<endl;
					asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
					asms<<"\tlw "<<tpreg<<", 0("<<addr<<")"<<endl;
					ra->free_temp(addr);
				}
				asms<<"\tsw "<<tpreg<<", "<<4*(i-8)<<"(sp)"<<endl;
			}
		}
		ra->free_temp(tpreg);
	}
	asms<<"\tcall "<<&(val->kind.data.call.callee->name[1])<<endl;
	if (args.len>8)
	{
		int extrasize=4*(args.len-8);
		asms<<"\taddi sp, sp, "<<extrasize<<endl;
		sa->less_space(extrasize);
	}
	switch (val->ty->tag)
	{
	case KOOPA_RTT_INT32:
		if (sa->get_pos(val)<2048)
			asms<<"\tsw a0, "<<sa->get_pos(val)<<"(sp)"<<endl;
		else
		{
			string addr=ra->allocate_temp();
			asms<<"\tli "<<addr<<", "<<sa->get_pos((const void*)val)<<endl;
			asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
			asms<<"\tsw a0, 0("<<addr<<")"<<endl;
			ra->free_temp(addr);
		}
		break;
	 case KOOPA_RTT_UNIT:
	 	break;
	
	default:
		break;
	}
}

deque<int> FlattenAggragate(const koopa_raw_value_t& val)
{
	deque<int> tp;
	int len=val->kind.data.aggregate.elems.len;
	for (int i=0;i<len;i++)
	{
		auto cur=reinterpret_cast<koopa_raw_value_t>(val->kind.data.aggregate.elems.buffer[i]);
		if (cur->kind.tag==KOOPA_RVT_INTEGER)
			tp.push_back(cur->kind.data.integer.value);
		else if (cur->kind.tag==KOOPA_RVT_AGGREGATE)
		{
			auto tpv=FlattenAggragate(cur);
			tp.insert(tp.end(),tpv.begin(),tpv.end());
		}
		else
		{
			LOG_ERROR("@FlattenAggragate: unexpected cur.kind.tag=%d",cur->kind.tag);
			break;
		}
	}
	return tp;
}

void VisitGlobalVar(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	asms<<"\t.globl "<<&(val->name[1])<<endl;
	asms<<&(val->name[1])<<":"<<endl;
	auto initval=val->kind.data.global_alloc.init;
	deque<int> items;
	switch (initval->kind.tag)
	{
	case KOOPA_RVT_ZERO_INIT:
		asms<<"\t.zero "<<CalcSize(initval->ty)<<endl;
		break;
	
	case KOOPA_RVT_INTEGER:
		asms<<"\t.word "<<initval->kind.data.integer.value<<endl;
		break;
	
	case KOOPA_RVT_AGGREGATE:
		items=FlattenAggragate(initval);
		for (int i=0;i<items.size();i++)
		{
			asms<<"\t.word "<<items[i]<<endl;
		}
		break;
	
	default:
		LOG_ERROR("@VisitGlobalVar: unexpected initval tag=%d",initval->kind.tag);
		break;
	}
}

void VisitGetElemPtr(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string tpreg;
	if (val->kind.data.get_elem_ptr.index->kind.tag==KOOPA_RVT_INTEGER)
	{
		tpreg=ra->allocate_temp();
		asms<<"\tli "<<tpreg<<", "<<val->kind.data.get_elem_ptr.index->kind.data.integer.value<<endl;
	}
	else
	{
		tpreg=ImplicitLoad(val->kind.data.get_elem_ptr.index,ra,sa);
	}
	int basesz=CalcSize(val->kind.data.get_elem_ptr.src->ty->data.pointer.base->data.array.base);
	LOG_DEBUG("@VisitGetELemPtr: base type=%d, size=%d",int(val->kind.data.get_elem_ptr.src->ty->data.pointer.base->data.array.base->tag),basesz);
	if (val->kind.data.get_elem_ptr.src->kind.tag==KOOPA_RVT_GLOBAL_ALLOC)
	{
		string tpsz=ra->allocate_temp();
		asms<<"\tli "<<tpsz<<", "<<basesz<<endl;
		asms<<"\tmul "<<tpreg<<", "<<tpsz<<", "<<tpreg<<endl;
		asms<<"\tla "<<tpsz<<", "<<&val->kind.data.get_elem_ptr.src->name[1]<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpsz<<", "<<tpreg<<endl;
		ra->free_temp(tpsz);
	}
	else
	{
		string tpsz=ra->allocate_temp();
		asms<<"\tli "<<tpsz<<", "<<basesz<<endl;
		asms<<"\tmul "<<tpsz<<", "<<tpsz<<", "<<tpreg<<endl;
		int offset=sa->get_pos(val->kind.data.get_elem_ptr.src);
		asms<<"\tli "<<tpreg<<", "<<offset<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpreg<<", sp"<<endl;
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpreg<<", "<<tpsz<<endl;
		ra->free_temp(tpsz);
	}

	if (sa->get_pos(val)<2048)
		asms<<"\tsw "<<tpreg<<", "<<sa->get_pos(val)<<"(sp)"<<endl;
	else
	{
		string addr=ra->allocate_temp();
		asms<<"\tli "<<addr<<", "<<sa->get_pos((const void*)val)<<endl;
		asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
		asms<<"\tsw "<<tpreg<<", 0("<<addr<<")"<<endl;
		ra->free_temp(addr);
	}
	ra->free_temp(tpreg);
}

void VisitGetPtr(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	string tpreg;
	if (val->kind.data.get_ptr.index->kind.tag==KOOPA_RVT_INTEGER)
	{
		tpreg=ra->allocate_temp();
		asms<<"\tli "<<tpreg<<", "<<val->kind.data.get_ptr.index->kind.data.integer.value<<endl;
	}
	else
	{
		tpreg=ImplicitLoad(val->kind.data.get_ptr.index,ra,sa);
	}
	int basesz=CalcSize(val->kind.data.get_ptr.src->ty->data.pointer.base);
	LOG_DEBUG("@VisitGetPtr: base type=%d, size=%d",int(val->kind.data.get_ptr.src->ty->data.pointer.base->tag),basesz);
	// if (val->kind.data.get_ptr.src->kind.tag==KOOPA_RVT_GLOBAL_ALLOC)
	// {
	// 	string tpsz=ra->allocate_temp();
	// 	asms<<"\tli "<<tpsz<<", "<<basesz<<endl;
	// 	asms<<"\tmul "<<tpreg<<", "<<tpsz<<", "<<tpreg<<endl;
	// 	asms<<"\tla "<<tpsz<<", "<<&val->kind.data.get_ptr.src->name[1]<<endl;
	// 	asms<<"\tadd "<<tpreg<<", "<<tpsz<<", "<<tpreg<<endl;
	// 	ra->free_temp(tpsz);
	// }
	// else
	// {
		string tpsz=ra->allocate_temp();
		asms<<"\tli "<<tpsz<<", "<<basesz<<endl;
		asms<<"\tmul "<<tpsz<<", "<<tpsz<<", "<<tpreg<<endl;
		int offset=sa->get_pos(val->kind.data.get_ptr.src);
		asms<<"\tli "<<tpreg<<", "<<offset<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpreg<<", sp"<<endl;
		asms<<"\tlw "<<tpreg<<", 0("<<tpreg<<")"<<endl;
		asms<<"\tadd "<<tpreg<<", "<<tpreg<<", "<<tpsz<<endl;
		ra->free_temp(tpsz);
	// }

	if (sa->get_pos(val)<2048)
		asms<<"\tsw "<<tpreg<<", "<<sa->get_pos(val)<<"(sp)"<<endl;
	else
	{
		string addr=ra->allocate_temp();
		asms<<"\tli "<<addr<<", "<<sa->get_pos((const void*)val)<<endl;
		asms<<"\tadd "<<addr<<", "<<addr<<", sp"<<endl;
		asms<<"\tsw "<<tpreg<<", 0("<<addr<<")"<<endl;
		ra->free_temp(addr);
	}
	ra->free_temp(tpreg);
}

void VisitAlloc(const koopa_raw_value_t &val, Register_Allocator *ra, Stack_Allocator *sa)
{
	int curpos=sa->get_pos(val);
	string tpreg=ra->allocate_temp();
	string addr=ra->allocate_temp();
	asms<<"\tli "<<tpreg<<", "<<curpos<<endl;
	asms<<"\tadd "<<tpreg<<", sp, "<<tpreg<<endl;
	asms<<"\taddi "<<addr<<", "<<tpreg<<", 4"<<endl;
	asms<<"\tsw "<<addr<<", 0("<<tpreg<<")"<<endl;
	ra->free_temp(addr);
	ra->free_temp(tpreg);
}

void Visit(const koopa_raw_integer_t &integer, string dest_register)
{
	asms << "\tli " << dest_register << ", " << integer.value << "\n";
}


///
/// [Scan] function group: scan the IR and figure out the stack memory needed for vars
///

void Scan(const koopa_raw_slice_t &slice, Stack_Allocator *sa)
{
	for (size_t i = 0; i < slice.len; ++i)
	{
		auto ptr = slice.buffer[i];
		// 根据 slice 的 kind 决定将 ptr 视作何种元素
		switch (slice.kind)
		{
		case KOOPA_RSIK_BASIC_BLOCK:
			// 访问基本块
			Scan(reinterpret_cast<koopa_raw_basic_block_t>(ptr), sa);
			break;
		case KOOPA_RSIK_VALUE:
			// 访问指令
			Scan(reinterpret_cast<koopa_raw_value_t>(ptr), sa);
			break;
		default:
			// 我们暂时不会遇到其他内容, 于是不对其做任何处理
			LOG_ERROR("@Scan_slice: Unexpected slice.kind: %d", slice.kind);
		}
	}
}

void Scan(const koopa_raw_basic_block_t &bb, Stack_Allocator *sa)
{
	Scan(bb->insts, sa);
}

void Scan(const koopa_raw_value_t &val, Stack_Allocator *sa)
{
	// if (val->kind.tag=KOOPA_RVT)
	// allocate space for new-generated temp var
	switch (val->ty->tag)
	{
	case KOOPA_RTT_INT32:
		sa->allocate(val);
		break;
	case KOOPA_RTT_UNIT:
		break;
	case KOOPA_RTT_POINTER:
		switch (val->kind.tag)
		{
		case KOOPA_RVT_ALLOC:
			sa->allocate_ptr(val);
			break;
		
		case KOOPA_RVT_GET_ELEM_PTR:
		case KOOPA_RVT_GET_PTR:
		case KOOPA_RVT_LOAD:
			sa->allocate(val);
			break;

		default:
			LOG_ERROR("@scan(value): unexpected val->kind.tag=%d",val->kind.tag);
			break;
		}
		break;
	
	default:
		LOG_ERROR("@Scan_value: Unexpected type: raw_type_tag_t=%d",val->ty->tag);
		break;
	}
}

int CalcSize(const koopa_raw_type_t &ty)
{
	switch (ty->tag)
	{
	case KOOPA_RTT_INT32:
		return 4;
	
	case KOOPA_RTT_ARRAY:
		return ty->data.array.len * CalcSize(ty->data.array.base);
	
	case KOOPA_RTT_POINTER:
		return 4;
	
	default:
		LOG_ERROR("@CalcSize: unexpected ty->tag=%d",ty->tag);
		break;
	}
	return 0;
}