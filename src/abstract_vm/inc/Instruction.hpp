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
	virtual int		execute(Stack &) = 0;
	virtual std::string	toString()const = 0;
	virtual bool	isExit();
};

class ARichInstruction : public IInstruction
{
public:
	//constructors
	ARichInstruction(const IOperand* value);
	ARichInstruction(ARichInstruction const &);
	virtual ~ARichInstruction();

	//getters setters
	IOperand const*	getValue()const;
	void			setValue(IOperand*);

	//other functions
	std::string	toString()const;

	ARichInstruction&	operator=(ARichInstruction const &);

protected:
	ARichInstruction();
	const IOperand*	_value;
};

std::ostream	&operator<<(std::ostream &o, ARichInstruction const &i);

class InstrPush : public ARichInstruction
{
public:
	InstrPush(const IOperand*);
	std::string	toString()const;
	int execute(Stack &s);

protected:
	InstrPush();
};

class InstrAssert : public ARichInstruction
{
public:
	InstrAssert(const IOperand*);
	std::string	toString()const;
	int execute(Stack &s);

protected:
	InstrAssert();
};

class InstrPop  : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrDump : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrAdd : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrSub : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrMul : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrDiv : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrMod : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrPrint : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
};

class InstrExit : public IInstruction
{
public:
	std::string	toString()const;
	int execute(Stack &s);
	bool isExit();
};

#endif /*INSTRUCTION_HEADER*/
