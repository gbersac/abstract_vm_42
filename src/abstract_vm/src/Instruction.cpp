#include "Instruction.hpp"

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

void InstrPush::execute(Stack &s)
{
	s.push(_value);
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

void InstrAssert::execute(Stack &s)
{
	Oper last = s.last();
	if (_value != last)
		throw AssertError(_value, last);
}

std::string InstrPop::toString()const
{
	std::stringstream ss;
	ss << "pop";
	return ss.str();
}

void InstrPop::execute(Stack &s)
{
	s.pop();
}

std::string InstrDump::toString()const
{
	std::stringstream ss;
	ss << "dump";
	return ss.str();
}

void InstrDump::execute(Stack &s)
{
	VecOper opers = s.getList();
	VecOper::iterator it;
	for(it = opers.begin(); it != opers.end(); ++it) {
		std::cout << *it << std::endl;
	};
}

std::string InstrAdd::toString()const
{
	std::stringstream ss;
	ss << "add";
	return ss.str();
}

void InstrAdd::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper + *roper;
	s.push(result);
}

std::string InstrSub::toString()const
{
	std::stringstream ss;
	ss << "sub";
	return ss.str();
}

void InstrSub::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper - *roper;
	s.push(result);
}

std::string InstrMul::toString()const
{
	std::stringstream ss;
	ss << "mul";
	return ss.str();
}

void InstrMul::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper * *roper;
	s.push(result);
}

std::string InstrDiv::toString()const
{
	std::stringstream ss;
	ss << "div";
	return ss.str();
}

void InstrDiv::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper / *roper;
	s.push(result);
}

std::string InstrMod::toString()const
{
	std::stringstream ss;
	ss << "mod";
	return ss.str();
}

void InstrMod::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper % *roper;
	s.push(result);
}

std::string InstrPrint::toString()const
{
	std::stringstream ss;
	ss << "print";
	return ss.str();
}

void InstrPrint::execute(Stack &s)
{
	Oper last = s.last();
	if (last->getType() != INT8)
		throw Not8bitIntError();
	std::cout << last << std::endl;
}

std::string InstrExit::toString()const
{
	std::stringstream ss;
	ss << "exit";
	return ss.str();
}

void InstrExit::execute(Stack &s)
{
	s.pop();
}
