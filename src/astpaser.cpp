#include "include/astparser.hpp"
using namespace std;

stringstream asms;

class Register_Allocator
{
	bool T_[7] = {};
	bool A_[8] = {};
	map<const void *, string> nt;

public:
	Register_Allocator(const koopa_raw_slice_t &params)
	{
		assert(params.len <= 8);
		int n_param = params.len;
		for (int i = 0; i < 7; i++)
			T_[i] = true;
		for (int i = n_param; i < 8; i++)
			A_[i] = true;
		for (int i = 0; i < n_param; i++)
		{
			string cur = "a" + to_string(i);
			nt.insert(make_pair((const void *)(params.buffer[i]), cur));
		}
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
		for (int i = 0; i < 8; i++)
		{
			if (A_[i])
			{
				A_[i] = false;
				reg = "a" + to_string(i);
				return reg;
			}
		}
		LOG_ERROR("NO AVAILABLE REGISTERS!");
		return "";
	}
	string allocate(const void *addr)
	{
		string reg;
		for (int i = 0; i < 7; i++)
		{
			if (T_[i])
			{
				T_[i] = false;
				reg = "t" + to_string(i);
				nt.insert(make_pair(addr, reg));
				return reg;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (A_[i])
			{
				A_[i] = false;
				reg = "a" + to_string(i);
				nt.insert(make_pair(addr, reg));
				return reg;
			}
		}
		LOG_ERROR("NO AVAILABLE REGISTERS!");
		return "";
	}
	void free(const void *addr)
	{
		auto it = nt.find(addr);
		if (it == nt.end())
		{
			LOG_ERROR("@get_pos: can NOT find pos w.r.t addr %p", addr);
			return;
		}
		nt.erase(it);
	}
	void free_temp(string &reg)
	{
		int cur = stoi(reg.substr(1));
		if (reg[0] == 'a')
		{
			if (A_[cur])
			{
				LOG_ERROR("%s is currently available!", reg.c_str());
			}
			A_[cur] = true;
		}
		else if (reg[0] == 't')
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
	string get_pos(const void *addr)
	{
		auto it = nt.find(addr);
		if (it == nt.end())
		{
			LOG_ERROR("@get_pos: can NOT find pos w.r.t addr %p", addr);
			return "";
		}
		return it->second;
	}
};

// 访问 raw program
void Visit(const koopa_raw_program_t &program)
{
	// 执行一些其他的必要操作
	// ...
	// 访问所有全局变量
	Visit(program.values);
	// 访问所有函数
	asms << "\t.text\n";
	Visit(program.funcs);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice, Register_Allocator *ra)
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
			Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr), ra);
			break;
		case KOOPA_RSIK_VALUE:
			// 访问指令
			Visit(reinterpret_cast<koopa_raw_value_t>(ptr), ra);
			break;
		default:
			// 我们暂时不会遇到其他内容, 于是不对其做任何处理
			LOG_ERROR("@slice: Unimplemented slice.kind: %d", slice.kind);
		}
	}
}

// 访问函数
void Visit(const koopa_raw_function_t &func)
{
	// 执行一些其他的必要操作
	asms << "\t.globl " << &func->name[1] << endl;
	asms << &func->name[1] << ":\n";
	Register_Allocator ra(func->params);
	// 访问所有基本块
	Visit(func->bbs, &ra);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb, Register_Allocator *ra)
{
	// 执行一些其他的必要操作
	// ...
	// 访问所有指令
	Visit(bb->insts, ra);
}

// 访问指令
void Visit(const koopa_raw_value_t &value, Register_Allocator *ra, string dest_register)
{
	// 根据指令类型判断后续需要如何访问
	const auto &kind = value->kind;
	switch (kind.tag)
	{
	case KOOPA_RVT_RETURN:
		// 访问 return 指令
		Visit(kind.data.ret, ra);
		break;
	case KOOPA_RVT_INTEGER:
		// 访问 integer 指令
		Visit(kind.data.integer, dest_register);
		break;
	case KOOPA_RVT_BINARY:
		VisitBin(value, ra);
		break;
	default:
		// 其他类型暂时遇不到
		LOG_ERROR("@value: Unimplemented kind.tag: %d", kind.tag);
	}
}

// binary operation
void VisitBin(const koopa_raw_value_t &val, Register_Allocator *ra)
{
	string dest = ra->allocate((const void *)val);
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
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string lr=ra->get_pos((const void*)lhs);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			assert(ri<(1<<12));
			asms<<"\taddi "<<tpreg<<", "<<lr<<", "<<(-1)*ri<<endl;
			asms<<"\tsnez "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string rr=ra->get_pos((const void*)rhs);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			assert(li<(1<<12));
			asms<<"\taddi "<<tpreg<<", "<<rr<<", "<<(-1)*li<<endl;
			asms<<"\tsnez "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
		}
		else
		{
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string lr=ra->get_pos(lhs);
			assert(lr!="");
			string rr=ra->get_pos(rhs);
			assert(rr!="");
			asms<<"\tsub "<<tpreg<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tsnez "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
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
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string lr=ra->get_pos((const void*)lhs);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			assert(ri<(1<<12));
			asms<<"\taddi "<<tpreg<<", "<<lr<<", "<<(-1)*ri<<endl;
			asms<<"\tseqz "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string rr=ra->get_pos((const void*)rhs);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			assert(li<(1<<12));
			asms<<"\taddi "<<tpreg<<", "<<rr<<", "<<(-1)*li<<endl;
			asms<<"\tseqz "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
		}
		else
		{
			string tpreg=ra->allocate_temp();
			assert(tpreg!="");
			string lr=ra->get_pos(lhs);
			assert(lr!="");
			string rr=ra->get_pos(rhs);
			assert(rr!="");
			asms<<"\tsub "<<tpreg<<", "<<lr<<", "<<rr<<endl;
			asms<<"\tseqz "<<dest<<", "<<tpreg<<endl;
			ra->free_temp(tpreg);
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
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string lr=ra->get_pos((const void*)lhs);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			assert(ri<(1<<12));
			asms<<"\taddi "<<dest<<", "<<lr<<", "<<ri<<endl;
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string rr=ra->get_pos((const void*)rhs);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			assert(li<(1<<12));
			asms<<"\taddi "<<dest<<", "<<rr<<", "<<li<<endl;
		}
		else
		{
			string lr=ra->get_pos(lhs);
			assert(lr!="");
			string rr=ra->get_pos(rhs);
			assert(rr!="");
			asms<<"\tadd "<<dest<<", "<<lr<<", "<<rr<<endl;
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
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string lr=ra->get_pos((const void*)lhs);
			assert(lr!="");
			int ri=rhs->kind.data.integer.value;
			assert(ri<(1<<12));
			asms<<"\taddi "<<dest<<", "<<lr<<", "<<(-1) * ri<<endl;
		}
		else if (lhs->kind.tag == KOOPA_RVT_INTEGER && rhs->kind.tag != KOOPA_RVT_INTEGER)
		{
			//===============================================================
			// WARNING: DISMISS THE UPPER 20 BITS OF IMMEDIATE NOW!
			//===============================================================
			string rr=ra->get_pos((const void*)rhs);
			assert(rr!="");
			int li=lhs->kind.data.integer.value;
			assert(li<(1<<12));
			asms<<"\taddi "<<dest<<", "<<rr<<", "<<(-1) * li<<endl;
			asms<<"\tneg "<<dest<<", "<<dest<<endl;
		}
		else
		{
			string lr=ra->get_pos(lhs);
			assert(lr!="");
			string rr=ra->get_pos(rhs);
			assert(rr!="");
			asms<<"\tsub "<<dest<<", "<<lr<<", "<<rr<<endl;
		}
		break;

	default:
		LOG_ERROR("@VisitBin: Unsupported BinOP: %d", bin.op);
		break;
	}
}

// return
void Visit(const koopa_raw_return_t &ret, Register_Allocator *ra)
{
	const auto& retv=ret.value;
	string reg;
	switch (retv->kind.tag)
	{
	case KOOPA_RVT_INTEGER:
		/* code */
		asms<<"\tli a0, "<<retv->kind.data.integer.value<<endl;
		break;
	
	case KOOPA_RVT_BINARY:
		reg=ra->get_pos(retv);
		asms<<"\tmv a0, "<<reg<<endl;
		break;

	default:
		LOG_ERROR("@visit(return): unexpected retv type: %d",retv->kind.tag);
		break;
	}
	asms << "\tret\n";
}

void Visit(const koopa_raw_integer_t &integer, string dest_register)
{
	asms << "\tli " << dest_register << ", " << integer.value << "\n";
}

// 访问对应类型指令的函数定义略
// 视需求自行实现
// ...