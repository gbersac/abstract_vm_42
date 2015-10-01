#include "Instruction.hpp"

bool	IInstruction::isExit()
{
	return false;
}

/******************************************************************************/
/* ARichInstruction                                                            */
/******************************************************************************/

ARichInstruction::ARichInstruction()
{

}

ARichInstruction::ARichInstruction(const IOperand* value)
		: _value(value)
{

}

ARichInstruction::ARichInstruction(ARichInstruction const &model)
{
	*this = model;
}

ARichInstruction::~ARichInstruction()
{

}

const IOperand* ARichInstruction::getValue()const
{
	return _value;
}

void ARichInstruction::setValue(IOperand* val)
{
	_value = val;
}

std::string	ARichInstruction::toString()const
{
	std::stringstream ss;
	ss << "ARichInstruction {" <<
			"value[" <<  _value << "] " <<
			"}";
	return ss.str();
}

ARichInstruction& ARichInstruction::operator=(ARichInstruction const &model)
{
	_value = model._value;
	return *this;
}

std::ostream &operator<<(std::ostream &o, ARichInstruction const &i)
{
	o << i.toString();
	return o;
}

/******************************************************************************/
/* Other instructions                                                         */
/******************************************************************************/

InstrPush::InstrPush(const IOperand*op)
		: ARichInstruction(op)
{}

std::string InstrPush::toString()const
{
	std::stringstream ss;
	if (_value == NULL)
		ss << "push(NULL)";
	else
		ss << "push(" << _value->toString() << ")";
	return ss.str();
}

int InstrPush::execute(Stack &s)
{
	s.push(_value);
	return 1;
}

InstrAssert::InstrAssert(const IOperand*op)
		: ARichInstruction(op)
{}

std::string InstrAssert::toString()const
{
	std::stringstream ss;
	if (_value == NULL)
		ss << "assert(NULL)";
	else
		ss << "assert(" << _value->toString() << ")";
	return ss.str();
}

int InstrAssert::execute(Stack &s)
{
	Oper last = s.last();
	if (!(*_value == *last))
		throw AssertError(_value, last);
	return 1;
}

std::string InstrPop::toString()const
{
	std::stringstream ss;
	ss << "pop";
	return ss.str();
}

int InstrPop::execute(Stack &s)
{
	s.pop();
	return 1;
}

std::string InstrDump::toString()const
{
	std::stringstream ss;
	ss << "dump";
	return ss.str();
}

int InstrDump::execute(Stack &s)
{
	VecOper opers = s.getList();
	VecOper::iterator it;
	int stackNb = 1;
	for(it = opers.begin(); it != opers.end(); ++it) {
		std::cout << stackNb << ": " << (*it)->toString() << std::endl;
		++stackNb;
	};
	return 1;
}

std::string InstrAdd::toString()const
{
	std::stringstream ss;
	ss << "add";
	return ss.str();
}

int InstrAdd::execute(Stack &s)
{
	Oper roper = s.pop();
	Oper loper = s.pop();
	Oper result = *loper + *roper;
	s.push(result);
	return 1;
}

std::string InstrSub::toString()const
{
	std::stringstream ss;
	ss << "sub";
	return ss.str();
}

int InstrSub::execute(Stack &s)
{
	Oper roper = s.pop();
	Oper loper = s.pop();
	Oper result = *loper - *roper;
	s.push(result);
	return 1;
}

std::string InstrMul::toString()const
{
	std::stringstream ss;
	ss << "mul";
	return ss.str();
}

int InstrMul::execute(Stack &s)
{
	Oper roper = s.pop();
	Oper loper = s.pop();
	Oper result = *loper * *roper;
	s.push(result);
	return 1;
}

std::string InstrDiv::toString()const
{
	std::stringstream ss;
	ss << "div";
	return ss.str();
}

int InstrDiv::execute(Stack &s)
{
	Oper roper = s.pop();
	Oper loper = s.pop();
	Oper result = *loper / *roper;
	s.push(result);
	return 1;
}

std::string InstrMod::toString()const
{
	std::stringstream ss;
	ss << "mod";
	return ss.str();
}

int InstrMod::execute(Stack &s)
{
	Oper roper = s.pop();
	Oper loper = s.pop();
	Oper result = *loper % *roper;
	s.push(result);
	return 1;
}

std::string InstrPrint::toString()const
{
	std::stringstream ss;
	ss << "print";
	return ss.str();
}

int InstrPrint::execute(Stack &s)
{
	Oper last = s.last();
	if (last->getType() != INT8)
		throw Not8bitIntError();
	std::cout << static_cast<char>(std::stoi((*last).toString())) << std::endl;
	return 1;
}

std::string InstrExit::toString()const
{
	std::stringstream ss;
	ss << "exit";
	return ss.str();
}

int InstrExit::execute(Stack &)
{
	return 0;
}

bool	InstrExit::isExit()
{
	return true;
}
