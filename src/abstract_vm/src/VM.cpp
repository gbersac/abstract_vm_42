#include "VM.hpp"

/******************************************************************************/
/* Constructors                                                               */
/******************************************************************************/

VM::VM()
{

}

VM::VM(std::vector<IInstruction*> instrs)
		: _instrs(instrs)
{

}

VM::VM(VM const &model)
{
	*this = model;
}

VM::~VM()
{

}

/******************************************************************************/
/* Getters Setters                                                            */
/******************************************************************************/

std::vector<IInstruction*> const& VM::getInstrs()const
{
	return _instrs;
}

void VM::setInstrs(std::vector<IInstruction*> const& val)
{
	_instrs = val;
}

Stack const& VM::getStack()const
{
	return _stack;
}

void VM::setStack(Stack const& val)
{
	_stack = val;
}

/******************************************************************************/
/* Other Functions                                                            */
/******************************************************************************/

std::string	VM::toString() const
{
	std::stringstream ss;
	ss << "VM {" <<
			"instrs[" <<  _instrs << "] " <<
			"stack[" <<  _stack << "] " <<
			"}";
	return ss.str();
}

VM& VM::operator=(VM const &model)
{
	_instrs = model._instrs;
	_stack = model._stack;
	return *this;
}

std::ostream &operator<<(std::ostream &o, VM const &i)
{
	o << i.toString();
	return o;
}

void VM::execute()
{
	std::vector<IInstruction*>::iterator i;
	int numInstr = 1;
	for (i = _instrs.begin(); i != _instrs.end(); ++i) {
		try {
			int ret = (*i)->execute(_stack);
			if (ret == 0)
				return ;
		} catch (VMError &e) {
			std::cout << "\033[1;31mExecutionError instruction num " << numInstr << ": \033[0m"
					<< e.msg() << std::endl << (*i)->toString() << std::endl;
			return ;
		} catch (std::exception &e) {
			std::cout << "\033[1;31mExecutionError instruction num " << numInstr << ": \033[0m"
					<< e.what() << std::endl << (*i)->toString() << std::endl;
			return ;
		}
		++numInstr;
	}
}
