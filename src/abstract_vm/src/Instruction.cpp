#include "Instruction.hpp"

/******************************************************************************/
/* ARichInstruction                                                            */
/******************************************************************************/

ARichInstruction::ARichInstruction()
{

}

ARichInstruction::ARichInstruction(ARichInstruction const &model)
{
	*this = model;
}

ARichInstruction::~ARichInstruction()
{

}

IOperand* ARichInstruction::getValue()const
{
	return _value;
}

void ARichInstruction::setValue(IOperand* val)
{
	_value = val;
}

std::string	ARichInstruction::toString() const
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

void InstrPush::execute(Stack &s)
{
	s.push(_value);
}

void InstrAssert::execute(Stack &s)
{
	Oper last = s.last();
	if (_value != last)
		throw AssertError(_value, last);
}

void InstrPop::execute(Stack &s)
{
	s.pop();
}

void InstrDump::execute(Stack &s)
{
	VecOper opers = s.getList();
	VecOper::iterator it;
	for(it = opers.begin(); it != opers.end(); ++it) {
		std::cout << *it << std::endl;
	};
}

void InstrAdd::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper + *roper;
	s.push(result);
}

void InstrSub::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper - *roper;
	s.push(result);
}

void InstrMul::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper * *roper;
	s.push(result);
}

void InstrDiv::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper / *roper;
	s.push(result);
}

void InstrMod::execute(Stack &s)
{
	Oper loper = s.pop();
	Oper roper = s.pop();
	Oper result = *loper % *roper;
	s.push(result);
}

void InstrPrint::execute(Stack &s)
{
	Oper last = s.last();
	if (last->getType() != INT8)
		throw Not8bitIntError();
	std::cout << last << std::endl;
}

void InstrExit::execute(Stack &s)
{
	s.pop();
}
