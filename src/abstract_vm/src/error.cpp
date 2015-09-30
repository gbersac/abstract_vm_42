#include "error.hpp"

const char* ParseError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());
}

char const * ExecutionError::what() const throw()
{
	std::string s = "ExecutionError: " + msg();
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
	ss << "Assertion failed. Expected: " << _expected << " found: " << _real;
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
