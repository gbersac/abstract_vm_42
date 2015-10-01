#ifndef VM_HEADER
#define VM_HEADER

#include <vector>
#include <iostream>
#include <sstream>

#include "Instruction.hpp"

class VM
{
public:
	//constructors
	VM(std::vector<IInstruction*> instrs);
	VM(VM const &);
	virtual ~VM();

	//getters setters
	std::vector<IInstruction*> const&	getInstrs()const;
	void			setInstrs(std::vector<IInstruction*> const&);
	Stack const&	getStack()const;
	void			setStack(Stack const&);

	//other functions
	std::string		toString()const;
	void			execute();
	VM&				operator=(VM const &);

protected:
	VM();
	std::vector<IInstruction*>	_instrs;
	Stack						_stack;
};

std::ostream	&operator<<(std::ostream &o, VM const &i);

#endif /*VM_HEADER*/
