#include "Operand.hpp"
#include "error.hpp"

const char* ParseError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());
}

char const * ExecutionError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());
}

/******************************************************************************/
/* Execution Error                                                            */
/******************************************************************************/

AssertError::AssertError(Oper expected, Oper real)
		: _expected(expected), _real(real)
{
}

std::string AssertError::msg() const
{
	std::stringstream ss;
	ss << "Assertion failed. Expected " << _expected->toString() <<
			" found " << _real->toString();
	return ss.str();
}

EmptyStackError::EmptyStackError()
{
}

std::string EmptyStackError::msg() const
{
	std::stringstream ss;
	ss << "Stack is empty";
	return ss.str();
}

Not8bitIntError::Not8bitIntError()
{
}

std::string Not8bitIntError::msg() const
{
	std::stringstream ss;
	ss << "The last value on the stack is not an 8bit int";
	return ss.str();
}

RvalueZeroError::RvalueZeroError()
{
}

std::string RvalueZeroError::msg() const
{
	std::stringstream ss;
	ss << "The rvalue is zeros, forbidden operation";
	return ss.str();
}

/******************************************************************************/
/* Execution Error                                                            */
/******************************************************************************/

InvalidInstructionError::InvalidInstructionError()
{}

InvalidInstructionError::~InvalidInstructionError() throw()
{}

std::string InvalidInstructionError::msg() const
{
	std::stringstream ss;
	ss << "Invalid instruction";
	return ss.str();
}

OverflowError::OverflowError()
{}

OverflowError::~OverflowError() throw()
{}

std::string OverflowError::msg() const
{
	std::stringstream ss;
	ss << "Value is out of bound (overflow or underflow)";
	return ss.str();
}

NoExitError::NoExitError()
{}

std::string NoExitError::msg() const
{
	std::stringstream ss;
	ss << "No exit instruction";
	return ss.str();
}
