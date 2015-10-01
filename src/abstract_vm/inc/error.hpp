#ifndef ERROR_H
# define ERROR_H

#include <exception>
#include <sstream>
#include <string>


class IOperand;
typedef IOperand const*	Oper;

/******************************************************************************/
/* Base Class                                                                 */
/******************************************************************************/

class VMError: public std::exception
{
public:
	virtual std::string	msg() const = 0;
	virtual char const * what() const throw() = 0;
};

class ParseError: public VMError
{
	virtual std::string	msg() const = 0;
	char const * what() const throw();
};

class ExecutionError: public VMError
{
	virtual std::string	msg() const = 0;
	char const * what() const throw();
};

/******************************************************************************/
/* Execution Error                                                            */
/******************************************************************************/

class AssertError: public ExecutionError
{
public:
	AssertError(Oper expected, Oper real);
	std::string msg() const;

private:
	Oper _expected;
	Oper _real;
};

class EmptyStackError: public ExecutionError
{
public:
	EmptyStackError();
	std::string msg() const;
};

class Not8bitIntError: public ExecutionError
{
public:
	Not8bitIntError();
	std::string msg() const;
};

class RvalueZeroError: public ExecutionError
{
public:
	RvalueZeroError();
	std::string msg() const;
};

/******************************************************************************/
/* Parsing Error                                                              */
/******************************************************************************/

class InvalidInstructionError: public ParseError
{
public:
	InvalidInstructionError();
	~InvalidInstructionError() throw();
	std::string msg() const;
};

class OverflowError: public ParseError
{
public:
	OverflowError();
	~OverflowError() throw();
	std::string msg() const;
};

#endif
