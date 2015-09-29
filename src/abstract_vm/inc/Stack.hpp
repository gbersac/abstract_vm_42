#ifndef STACK_HEADER
#define STACK_HEADER

#include <iostream>
#include <sstream>
#include <vector>

#include "Operand.hpp"
#include "error.hpp"

typedef IOperand const*		Oper;
typedef std::vector<Oper> 	VecOper;

class Stack
{
public:
	//constructors
	Stack();
	Stack(Stack const &);
	virtual ~Stack();

	//getters setters
	VecOper const&	getList()const;

	//other functions
	std::string		toString()const;
	Oper			pop();
	void			push(Oper);
	Oper			last();

	Stack&			operator=(Stack const &);

protected:
	VecOper	_list;
};

std::ostream		&operator<<(std::ostream &o, Stack const &i);

#endif /*STACK_HEADER*/
