#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <iostream>
#include <sstream>

#include "Stack.hpp"
#include "Operand.hpp"
#include "error.hpp"

class IInstruction
{
public:
	virtual void execute(Stack &) = 0;
};

class ARichInstruction : public IInstruction
{
public:
	//constructors
	ARichInstruction();
	ARichInstruction(ARichInstruction const &);
	virtual ~ARichInstruction();

	//getters setters
	IOperand*	getValue()const;
	void		setValue(IOperand*);

	//other functions
	std::string	toString()const;

	ARichInstruction&	operator=(ARichInstruction const &);

protected:
	IOperand*	_value;
};

std::ostream	&operator<<(std::ostream &o, ARichInstruction const &i);

class InstrPush : public ARichInstruction
{
	void execute(Stack &s);
};

class InstrAssert : public ARichInstruction
{
	void execute(Stack &s);
};

class InstrPop  : public IInstruction
{
	void execute(Stack &s);
};

class InstrDump : public IInstruction
{
	void execute(Stack &s);
};

class InstrAdd : public IInstruction
{
	void execute(Stack &s);
};

class InstrSub : public IInstruction
{
	void execute(Stack &s);
};

class InstrMul : public IInstruction
{
	void execute(Stack &s);
};

class InstrDiv : public IInstruction
{
	void execute(Stack &s);
};

class InstrMod : public IInstruction
{
	void execute(Stack &s);
};

class InstrPrint : public IInstruction
{
	void execute(Stack &s);
};

class InstrExit : public IInstruction
{
	void execute(Stack &s);
};

#endif /*INSTRUCTION_HEADER*/
